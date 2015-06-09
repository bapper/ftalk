/*
 * Copyright (C) 2015 Yoshi Kanamiya
 * Copyright (C) 2015 Brian Pomerantz
 */

#define FTALK_NUM_SENSORS     3
#define FTALK_EVENT_MIN_TIME  20 //number of milliseconds a press must last
#define FTALK_EVENT_TASK_TIME (FTALK_EVENT_MIN_TIME + FTALK_EVENT_MIN_TIME/2)
#define FTALK_LOOP_DELAY      5  //Delay between sensor reads, without delay it gets false zeros

#define EVENT_TYPE_S1   1
#define EVENT_TYPE_S2   2
#define EVENT_TYPE_S3   3
#define EVENT_TYPE_S4   4
#define EVENT_TYPE_S5   5
#define EVENT_TYPE_S6   6
#define EVENT_TYPE_S7   7
#define EVENT_TYPE_S8   8
#define EVENT_TYPE_S9   9
#define EVENT_TYPE_S10  10

//#define DEBUG

/*
 * XXX: I found the sensors started reading high without pressing them, I had to set a
 * threshold for when a press occured. There should probably be a calibration on boot.
 */
int sensor_thresholds[FTALK_NUM_SENSORS] = {
  130, 250, 5
};

/*
 * This structure tracks each sensor input prior to event creation.
 */
struct sensor_input {
  unsigned int  value;
  unsigned long start;
  unsigned int  threshold;
};

/*
 * Current input values for each sensor, value of 0 means no press.
 */
struct sensor_input sensor_values[FTALK_NUM_SENSORS];

/*
 * A simple input event (button press). These events need to be used to heuristically
 * prune the list of gestures.
 */
struct input_event {
  struct input_event  *next;
  unsigned long       duration;
  unsigned long       start;
  unsigned int        value;
  int                 type;
};

/*
 * Map of sensors to analog input ports.
 */
int sensor_input_map[FTALK_NUM_SENSORS] = {
  A2, A3, A8
};

/*
 * The list of unprocessed events.
 */
struct event_list {
  struct input_event *first;
  struct input_event *last;
} event_list = { NULL, NULL };

/*
 * Task id for processing events.
 */
int process_events_id;

/*
 * Event processing task.
 *
 * XXX: should start pruning the gesture list here. There also needs to be timeout between
 * events to determine that a new guesture is to start.
 */
void process_events(int id, void *var)
{
  while (event_list.first != NULL) {
    struct input_event *cur;

    cur = event_list.first;
    event_list.first = cur->next;
    if (event_list.last == cur) {
      event_list.last = NULL;
    }

    if (cur->duration > FTALK_EVENT_MIN_TIME) {
      Serial.print("Value=");
      Serial.print(cur->value);
      Serial.print("   Type=");
      Serial.print(cur->type);
      Serial.print("   Duration=");
      Serial.println(cur->duration);
    }
#ifdef DEBUG
    else {
      Serial.print("Too Short -- Value=");
      Serial.print(cur->value);
      Serial.print("   Type=");
      Serial.print(cur->type);
      Serial.print("   Duration=");
      Serial.println(cur->duration);
    }
#endif
    free(cur);
  }
}

/*
 * Adds a touch event in chronological order based on start time.
 */
void add_input_event(struct input_event *new_event)
{
  if (event_list.last == NULL) {
    event_list.first = new_event;
    event_list.last = new_event;
  } else {
    struct input_event *cur, *prev;
    cur = event_list.first;
    prev = NULL;
    while (cur) {
      if (new_event->start < cur->start) {
        new_event->next = cur;
        if (event_list.first == cur) {
          event_list.first = new_event;
        } else if (prev) {
          prev->next = new_event;
        }
        break;
      }
      prev = cur;
      cur = cur->next;
    }

    if (!cur) {
      event_list.last->next = new_event;
      event_list.last = new_event;
    }
  }
}


/* To check throttle of printing debug statements. */
unsigned long last_time = 0;

/*
 * Read from each sensor, store values in sensor_values, create new events when a sensor
 * was pressed then released.
 */
void read_sensors(void)
{
  unsigned long now;
  int i;
  int printit = 0;

  now = millis();
  if (now > last_time+1000) {
    last_time = now;
#ifdef DEBUG
    printit++;
#endif
  }

  /* Spin through the sensors and read their values */
  for (i=0; i < FTALK_NUM_SENSORS; i++) {
    unsigned int value;
    unsigned int now;

    now = millis();
    value = analogRead(sensor_input_map[i]);
    if (sensor_values[i].value == 0 && value >= sensor_values[i].threshold) {
      /* start of a press event */
      if (printit) {
        Serial.print("\nStarting event: ");
        Serial.println(sensor_values[i].threshold);
      }

      sensor_values[i].value = value;
      sensor_values[i].start = now;
    } else if (sensor_values[i].value != 0 && value < sensor_values[i].threshold) {
      /* end of a press event */
      struct input_event *new_event;

      new_event = (struct input_event *)malloc(sizeof(*new_event));
      /* XXX: millis() overflows after 50 days, eventually need an algorithm here */
      new_event->duration = now - sensor_values[i].start;
      new_event->start = sensor_values[i].start;
      new_event->type = i + 1; //i starts at 0, sensors start at 1
      new_event->value = sensor_values[i].value; //last non-zero value read, probably won't need this
      new_event->next = NULL;

      add_input_event(new_event);

      /* reset sensor data */
      sensor_values[i].value = 0;
      sensor_values[i].start = 0;

      if (printit) {
        Serial.print("New event: ");
        Serial.print(new_event->value);
        Serial.print("  Type=");
        Serial.print(new_event->type);
        Serial.print("  Duration=");
        Serial.print(new_event->duration);
        Serial.print("  ");
      }
    } else if (sensor_values[i].value != 0 && value >= sensor_values[i].threshold) {
      sensor_values[i].value = value;
    }

    if (printit) {
      Serial.print(sensor_values[i].start);
      Serial.print(" ");
      Serial.print(sensor_values[i].value);
      Serial.print(" ");
      Serial.print(value);
      Serial.print(",   ");
    }
  }

  if (printit) {
    Serial.println(" ");
  }
}


void setup()
{
  int i;

  Serial.begin(19200);
  process_events_id = createTask(process_events, FTALK_EVENT_TASK_TIME, TASK_ENABLE, NULL);
  for (i=0; i < FTALK_NUM_SENSORS; i++) {
    sensor_values[i].threshold = sensor_thresholds[i];
    sensor_values[i].value = 0;
    sensor_values[i].start = 0;
  }
}

void loop()
{
  read_sensors();
  delay(5);
}
