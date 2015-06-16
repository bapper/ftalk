/*
 * Copyright (C) 2015 Yoshi Kanamiya
 * Copyright (C) 2015 Brian Pomerantz
 */

//#define DEBUG
int printit = 0;

#include "ftalk.h"

#define FTALK_NUM_SENSORS     3
#define FTALK_EVENT_MIN_TIME  10   //number of milliseconds a press must last
#define FTALK_EVENT_TASK_TIME (FTALK_EVENT_MIN_TIME + FTALK_EVENT_MIN_TIME/2)
#define FTALK_LOOP_MSDELAY    1    //Delay between sensor reads in milliseconds, without delay it gets false zeros, NOT USED RIGHT NOW
#define FTALK_LOOP_NSDELAY    500  //Delay between sensor reads in nanoseconds, without delay it gets false zeros
#define FTALK_GESTURE_TIMEOUT 1000 //Milliseconds between gestures, XXX: this should be tuned!

/*
 * Map of sensors to analog input ports.
 */
int sensor_input_map[FTALK_NUM_SENSORS] = {
  A2, A3, A8
};

/*
 * XXX: I found the sensors started reading high without pressing them, I had to set a
 * threshold for when a press occured. There should probably be a calibration on boot.
 */
int sensor_thresholds[FTALK_NUM_SENSORS] = {
  5, 5, 5
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
  unsigned long       start;
  unsigned long       duration;
  unsigned int        value;
  int                 type;
};

/*
 * The list of unprocessed events.
 */
struct event_list {
  struct input_event *first;
  struct input_event *last;
  int                count;
  unsigned long      last_time;
} event_list = { NULL, NULL, 0 , 0};


struct gesture_matches {
  struct gesture_event  *first;
  struct gesture_event  *last;
  int count;
};

struct gesture_matches gesture_matches = { NULL, NULL, 0 };

#define FTALK_GESTURES_LEN  (sizeof(gestures) / sizeof(struct gesture_event))

/*
 * Task id for processing events.
 */
int process_events_id;

void reset_gestures(void)
{
  int i;

  for (i=0; i < FTALK_GESTURES_LEN-1; i++) {
    gestures[i].next = &gestures[i+1];
  }
  gestures[FTALK_GESTURES_LEN-1].next = NULL;
  gesture_matches.first = &gestures[0];
  gesture_matches.last = &gestures[FTALK_GESTURES_LEN-1];
  gesture_matches.count = FTALK_GESTURES_LEN;
}

void free_events(void)
{
  while (event_list.first != NULL) {
    struct input_event *cur;

    cur = event_list.first;
    event_list.first = cur->next;
    free(cur);
    event_list.count--;
  }
  event_list.last = NULL;
}

int match_gesture_event(struct input_event *iv, int num_matched)
{
  struct gesture_event  *gesture;
  struct gesture_event  *prev;

  gesture = gesture_matches.first;
  prev = NULL;
  while (gesture) {
    if ((iv && (gesture->events[num_matched] == 0 || gesture->events[num_matched] != iv->type)) || 
               (iv == NULL && gesture->events[num_matched] != 0))
    {
      /* drop the gesture from matches if it doesn't match */
#ifdef DEBUG
      Serial.print("Dropping ");
      Serial.println(gesture->type);
#endif
      if (gesture_matches.first == gesture) {
        gesture_matches.first = gesture->next;
      } else {
        prev->next = gesture->next;
      }

      if (gesture_matches.last == gesture) {
        gesture_matches.last = NULL;
      }
      gesture_matches.count--;
    } else {
      /* Matched this time, keep track of this one */
      prev = gesture;
    }
    gesture = gesture->next;
  }

  return gesture_matches.count;
}

void print_gesture_events(void)
{
  struct gesture_event  *gesture;

  if (!gesture_matches.count) {
    Serial.print(long(gesture_matches.first));
    Serial.println("  No gestures matched!");
    return;
  }

  Serial.print("Gestures matched -> ");
  gesture = gesture_matches.first;
  while (gesture) {
    Serial.print(gesture->type);
    gesture = gesture->next;
    if (gesture != NULL) {
      Serial.print(", ");
    }
  }
  Serial.println(" ");
}

/*
 * Event processing task.
 *
 * XXX: should start pruning the gesture list here. There also needs to be timeout between
 * events to determine that a new guesture is to start.
 */
void process_events(int id, void *var)
{
  unsigned long now;
  struct input_event *cur;
  int i;
  int num_matched = 0;

  now = millis();
  /* See if we should end the current round of gesture pruning and see if we have a match */
  if (!event_list.last_time || (now - event_list.last_time < FTALK_GESTURE_TIMEOUT) || !event_list.count) {
    if (printit) {
      Serial.print("--- !");
      Serial.print(event_list.last_time);
      Serial.print(" || ");
      Serial.print(now - event_list.last_time);
      Serial.print(" < ");
      Serial.print(FTALK_GESTURE_TIMEOUT);
      Serial.print(" || !");
      Serial.print(event_list.count);
      Serial.println("---");
    }
    return;
  }

  if (!gesture_matches.first) {
    reset_gestures();
  }

  while (event_list.first != NULL) {
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

      match_gesture_event(cur, num_matched);
      num_matched++;
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
    event_list.count--;
  }

  match_gesture_event(NULL, num_matched);
  print_gesture_events();
  event_list.last_time = 0;
  reset_gestures();
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

  event_list.last_time = millis();
  event_list.count++;
}


/* To check throttle of printing debug statements. */
unsigned long last_time = 0;

/*
 * Read from each sensor, store values in sensor_values, create new events when a sensor
 * was pressed then released.
 */
void read_sensors(void)
{
  int i;

  if (printit) {
    Serial.print(event_list.count);
    Serial.print("->");
    Serial.print(event_list.last_time);
    Serial.print("->");
    Serial.print(long(event_list.first));
    Serial.print("-> ");
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
      new_event->type = i + 1; //type PUSH, i starts at 0, sensors start at 1
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
  //XXX: the task stopped runnning after a while, bug in base code?
  //process_events_id = createTask(process_events, FTALK_EVENT_TASK_TIME, TASK_ENABLE, NULL);
  for (i=0; i < FTALK_NUM_SENSORS; i++) {
    sensor_values[i].threshold = sensor_thresholds[i];
    sensor_values[i].value = 0;
    sensor_values[i].start = 0;
  }
}

void loop()
{
#ifdef DEBUG
  unsigned long now;
  now = millis();
  if (now > last_time+1000) {
    last_time = now;
    printit++;
  }
#endif
  read_sensors();
  process_events(0, NULL);
  //delay(FTALK_LOOP_MSDELAY);
  printit = 0;
  delayMicroseconds(FTALK_LOOP_NSDELAY);
}
