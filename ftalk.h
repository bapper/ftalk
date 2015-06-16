#ifndef _FTALK_H
#define _FTALK_H

#include <arduino.h>

/*********************************************************
 * Events, to be translated to ASCII
 *********************************************************/
#define EVENT_PUSH_IL1          1
#define EVENT_PUSH_IL2          2
#define EVENT_PUSH_IL3          3
#define EVENT_PUSH_IV1          4
#define EVENT_PUSH_IV2          5
#define EVENT_PUSH_ML1          6
#define EVENT_PUSH_ML2          7
#define EVENT_PUSH_ML3          8
#define EVENT_PUSH_MV1          9
#define EVENT_PUSH_MV2          10
#define EVENT_DOUBLE_PUSH_IL1   11
#define EVENT_DOUBLE_PUSH_IL2   12
#define EVENT_DOUBLE_PUSH_IL3   13
#define EVENT_DOUBLE_PUSH_IV1   14
#define EVENT_DOUBLE_PUSH_IV2   15
#define EVENT_DOUBLE_PUSH_ML1   16
#define EVENT_DOUBLE_PUSH_ML2   17
#define EVENT_DOUBLE_PUSH_ML3   18
#define EVENT_DOUBLE_PUSH_MV1   19
#define EVENT_DOUBLE_PUSH_MV2   20
#define EVENT_IL_RSWIPE         21
#define EVENT_IL_LSWIPE         22
#define EVENT_IL_RSWIPE_PUSH    23
#define EVENT_IL_LSWIPE_PUSH    24

/*********************************************************
 * Index finger gesture lists
 *********************************************************/
/* Lateral */
#define GESTURE_LIST_PUSH_IL1           EVENT_PUSH_IL1
#define GESTURE_LIST_DOUBLE_PUSH_IL1    EVENT_PUSH_IL1, EVENT_PUSH_IL1
#define GESTURE_LIST_PUSH_IL2           EVENT_PUSH_IL2
#define GESTURE_LIST_DOUBLE_PUSH_IL2    EVENT_PUSH_IL2, EVENT_PUSH_IL2
#define GESTURE_LIST_PUSH_IL3           EVENT_PUSH_IL3
#define GESTURE_LIST_DOUBLE_PUSH_IL3    EVENT_PUSH_IL3, EVENT_PUSH_IL3
#define GESTURE_LIST_IL_RSWIPE          EVENT_PUSH_IL1, EVENT_PUSH_IL2
#define GESTURE_LIST_IL_LSWIPE          EVENT_PUSH_IL2, EVENT_PUSH_IL1
#define GESTURE_LIST_IL_RSWIPE_PUSH     GESTURE_LIST_IL_RSWIPE, EVENT_PUSH_IL2
#define GESTURE_LIST_IL_LSWIPE_PUSH     GESTURE_LIST_IL_LSWIPE, EVENT_PUSH_IL1

/* These swipes include all three sensors */
#define GESTURE_LIST_IL_ALT_RSWIPE      EVENT_PUSH_IL1, EVENT_PUSH_IL2, EVENT_PUSH_IL3
#define GESTURE_LIST_IL_ALT_LSWIPE      EVENT_PUSH_IL3, EVENT_PUSH_IL2, EVENT_PUSH_IL1
#define GESTURE_LIST_IL_ALT_RSWIPE_PUSH GESTURE_LIST_IL_ALT_RSWIPE, EVENT_PUSH_IL3
#define GESTURE_LIST_IL_ALT_LSWIPE_PUSH GESTURE_LIST_IL_ALT_LSWIPE, EVENT_PUSH_IL1

/* Volar */
#define GESTURE_LIST_PUSH_IV1         EVENT_PUSH_IV1
#define GESTURE_LIST_DOUBLE_PUSH_IV1  EVENT_PUSH_IV1, EVENT_PUSH_IV1
#define GESTURE_LIST_PUSH_IV2         EVENT_PUSH_IV2
#define GESTURE_LIST_DOUBLE_PUSH_IV2  EVENT_PUSH_IV2, EVENT_PUSH_IV2
#define GESTURE_LIST_IV_RSWIPE        EVENT_PUSH_IV1, EVENT_PUSH_IV2
#define GESTURE_LIST_IV_LSWIPE        EVENT_PUSH_IV2, EVENT_PUSH_IV1
/*********************************************************
 * Middle finger gesture lists
 *********************************************************/

/*
 * This structure defines a gesture event. Simple input events contribute to make a
 * gesture.  The cur pointer is used to track where in the list we are in pruning the
 * gesture from the list of available gestures.
 *
 * list:  The list of input events that makes up this gesture
 * cur:   The current pointer into the list
 * len:   The number of input events that make up the gesture
 */
struct gesture_event {
  int type;
  int events[7]; //XXX: 6 (+ 0 term) should be the most, some wasted space here but easier than parsing text definitions
  struct gesture_event *next; /* list of currently matching gestures */
};

struct gesture_event gestures[] = {
  { EVENT_PUSH_IL1,         { GESTURE_LIST_PUSH_IL1, 0 } },
  { EVENT_PUSH_IL2,         { GESTURE_LIST_PUSH_IL2, 0 } },
  { EVENT_PUSH_IL3,         { GESTURE_LIST_PUSH_IL3, 0 } },
  { EVENT_DOUBLE_PUSH_IL1,  { GESTURE_LIST_DOUBLE_PUSH_IL1, 0 } },
  { EVENT_DOUBLE_PUSH_IL2,  { GESTURE_LIST_DOUBLE_PUSH_IL2, 0 } },
  { EVENT_DOUBLE_PUSH_IL3,  { GESTURE_LIST_DOUBLE_PUSH_IL3, 0 } },
  { EVENT_IL_RSWIPE,        { GESTURE_LIST_IL_RSWIPE, 0 } },
  { EVENT_IL_LSWIPE,        { GESTURE_LIST_IL_LSWIPE, 0 } },
  { EVENT_IL_RSWIPE_PUSH,   { GESTURE_LIST_IL_RSWIPE_PUSH, 0 } },
  { EVENT_IL_LSWIPE_PUSH,   { GESTURE_LIST_IL_LSWIPE_PUSH, 0 } },
  { EVENT_IL_RSWIPE,        { GESTURE_LIST_IL_ALT_RSWIPE, 0 } },
  { EVENT_IL_LSWIPE,        { GESTURE_LIST_IL_ALT_LSWIPE, 0 } },
  { EVENT_IL_RSWIPE_PUSH,   { GESTURE_LIST_IL_ALT_RSWIPE_PUSH, 0 } },
  { EVENT_IL_LSWIPE_PUSH,   { GESTURE_LIST_IL_ALT_LSWIPE_PUSH, 0 } },
};

#endif /* _FTALK_H */
