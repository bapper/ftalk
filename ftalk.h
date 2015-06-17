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
#define EVENT_IL_DOUBLE_RSWIPE  23
#define EVENT_IL_DOUBLE_LSWIPE  24
#define EVENT_IL_RLSWIPE        25
#define EVENT_IL_LRSWIPE        26
#define EVENT_IL_RSWIPE_PUSH    27
#define EVENT_IL_LSWIPE_PUSH    28
#define EVENT_IV_RSWIPE         29
#define EVENT_IV_LSWIPE         30
#define EVENT_IV_DOUBLE_RSWIPE  31
#define EVENT_IV_DOUBLE_LSWIPE  32
#define EVENT_IV_RLSWIPE        33
#define EVENT_IV_LRSWIPE        34
#define EVENT_IV_RSWIPE_PUSH    35
#define EVENT_IV_LSWIPE_PUSH    36
#define EVENT_ML_RSWIPE         37
#define EVENT_ML_LSWIPE         38
#define EVENT_ML_DOUBLE_RSWIPE  39
#define EVENT_ML_DOUBLE_LSWIPE  40
#define EVENT_ML_RLSWIPE        41
#define EVENT_ML_LRSWIPE        42
#define EVENT_ML_RSWIPE_PUSH    43
#define EVENT_ML_LSWIPE_PUSH    44
#define EVENT_MV_RSWIPE         45
#define EVENT_MV_LSWIPE         46
#define EVENT_MV_DOUBLE_RSWIPE  47
#define EVENT_MV_DOUBLE_LSWIPE  48
#define EVENT_MV_RLSWIPE        49
#define EVENT_MV_LRSWIPE        50
#define EVENT_MV_RSWIPE_PUSH    51
#define EVENT_MV_LSWIPE_PUSH    52

/*********************************************************************
 * Index finger gesture lists
 * XXX: May need more ALT swipes for double swipes and RL/LR swipes
 *********************************************************************/
/* Lateral */
#define GESTURE_LIST_PUSH_IL1           EVENT_PUSH_IL1
#define GESTURE_LIST_DOUBLE_PUSH_IL1    EVENT_PUSH_IL1, EVENT_PUSH_IL1
#define GESTURE_LIST_PUSH_IL2           EVENT_PUSH_IL2
#define GESTURE_LIST_DOUBLE_PUSH_IL2    EVENT_PUSH_IL2, EVENT_PUSH_IL2
#define GESTURE_LIST_PUSH_IL3           EVENT_PUSH_IL3
#define GESTURE_LIST_DOUBLE_PUSH_IL3    EVENT_PUSH_IL3, EVENT_PUSH_IL3
#define GESTURE_LIST_IL_RSWIPE          EVENT_PUSH_IL1, EVENT_PUSH_IL2
#define GESTURE_LIST_IL_LSWIPE          EVENT_PUSH_IL2, EVENT_PUSH_IL1
#define GESTURE_LIST_IL_DOUBLE_RSWIPE   GESTURE_LIST_IL_RSWIPE, GESTURE_LIST_IL_RSWIPE
#define GESTURE_LIST_IL_DOUBLE_LSWIPE   GESTURE_LIST_IL_LSWIPE, GESTURE_LIST_IL_LSWIPE
#define GESTURE_LIST_IL_RLSWIPE         GESTURE_LIST_IL_RSWIPE, GESTURE_LIST_IL_LSWIPE
#define GESTURE_LIST_IL_LRSWIPE         GESTURE_LIST_IL_LSWIPE, GESTURE_LIST_IL_RSWIPE
#define GESTURE_LIST_IL_RSWIPE_PUSH     GESTURE_LIST_IL_RSWIPE, EVENT_PUSH_IL2
#define GESTURE_LIST_IL_LSWIPE_PUSH     GESTURE_LIST_IL_LSWIPE, EVENT_PUSH_IL1

/* These swipes include all three sensors */
#define GESTURE_LIST_IL_ALT_RSWIPE      EVENT_PUSH_IL1, EVENT_PUSH_IL2, EVENT_PUSH_IL3
#define GESTURE_LIST_IL_ALT_LSWIPE      EVENT_PUSH_IL3, EVENT_PUSH_IL2, EVENT_PUSH_IL1
#define GESTURE_LIST_IL_ALT_RSWIPE_PUSH GESTURE_LIST_IL_ALT_RSWIPE, EVENT_PUSH_IL3
#define GESTURE_LIST_IL_ALT_LSWIPE_PUSH GESTURE_LIST_IL_ALT_LSWIPE, EVENT_PUSH_IL1

/* Volar */
#define GESTURE_LIST_PUSH_IV1           EVENT_PUSH_IV1
#define GESTURE_LIST_DOUBLE_PUSH_IV1    EVENT_PUSH_IV1, EVENT_PUSH_IV1
#define GESTURE_LIST_PUSH_IV2           EVENT_PUSH_IV2
#define GESTURE_LIST_DOUBLE_PUSH_IV2    EVENT_PUSH_IV2, EVENT_PUSH_IV2
#define GESTURE_LIST_IV_RSWIPE          EVENT_PUSH_IV1, EVENT_PUSH_IV2
#define GESTURE_LIST_IV_LSWIPE          EVENT_PUSH_IV2, EVENT_PUSH_IV1
#define GESTURE_LIST_IV_DOUBLE_RSWIPE   GESTURE_LIST_IV_RSWIPE, GESTURE_LIST_IV_RSWIPE
#define GESTURE_LIST_IV_DOUBLE_LSWIPE   GESTURE_LIST_IV_LSWIPE, GESTURE_LIST_IV_LSWIPE
#define GESTURE_LIST_IV_RLSWIPE         GESTURE_LIST_IV_RSWIPE, GESTURE_LIST_IV_LSWIPE
#define GESTURE_LIST_IV_LRSWIPE         GESTURE_LIST_IV_LSWIPE, GESTURE_LIST_IV_RSWIPE
#define GESTURE_LIST_IV_RSWIPE_PUSH     GESTURE_LIST_IV_RSWIPE, EVENT_PUSH_IV2
#define GESTURE_LIST_IV_LSWIPE_PUSH     GESTURE_LIST_IV_LSWIPE, EVENT_PUSH_IV1
/*********************************************************************
 * Middle finger gesture lists
 * XXX: May need more ALT swipes for double swipes and RL/LR swipes
 *********************************************************************/
/* Lateral */
#define GESTURE_LIST_PUSH_ML1           EVENT_PUSH_ML1
#define GESTURE_LIST_DOUBLE_PUSH_ML1    EVENT_PUSH_ML1, EVENT_PUSH_ML1
#define GESTURE_LIST_PUSH_ML2           EVENT_PUSH_ML2
#define GESTURE_LIST_DOUBLE_PUSH_ML2    EVENT_PUSH_ML2, EVENT_PUSH_ML2
#define GESTURE_LIST_PUSH_ML3           EVENT_PUSH_ML3
#define GESTURE_LIST_DOUBLE_PUSH_ML3    EVENT_PUSH_ML3, EVENT_PUSH_ML3
#define GESTURE_LIST_ML_RSWIPE          EVENT_PUSH_ML1, EVENT_PUSH_ML2
#define GESTURE_LIST_ML_LSWIPE          EVENT_PUSH_ML2, EVENT_PUSH_ML1
#define GESTURE_LIST_ML_DOUBLE_RSWIPE   GESTURE_LIST_ML_RSWIPE, GESTURE_LIST_ML_RSWIPE
#define GESTURE_LIST_ML_DOUBLE_LSWIPE   GESTURE_LIST_ML_LSWIPE, GESTURE_LIST_ML_LSWIPE
#define GESTURE_LIST_ML_RLSWIPE         GESTURE_LIST_ML_RSWIPE, GESTURE_LIST_ML_LSWIPE
#define GESTURE_LIST_ML_LRSWIPE         GESTURE_LIST_ML_LSWIPE, GESTURE_LIST_ML_RSWIPE
#define GESTURE_LIST_ML_RSWIPE_PUSH     GESTURE_LIST_ML_RSWIPE, EVENT_PUSH_ML2
#define GESTURE_LIST_ML_LSWIPE_PUSH     GESTURE_LIST_ML_LSWIPE, EVENT_PUSH_ML1

/* These swipes include all three sensors */
#define GESTURE_LIST_ML_ALT_RSWIPE      EVENT_PUSH_ML1, EVENT_PUSH_ML2, EVENT_PUSH_ML3
#define GESTURE_LIST_ML_ALT_LSWIPE      EVENT_PUSH_ML3, EVENT_PUSH_ML2, EVENT_PUSH_ML1
#define GESTURE_LIST_ML_ALT_RSWIPE_PUSH GESTURE_LIST_ML_ALT_RSWIPE, EVENT_PUSH_ML3
#define GESTURE_LIST_ML_ALT_LSWIPE_PUSH GESTURE_LIST_ML_ALT_LSWIPE, EVENT_PUSH_ML1

/* Volar */
#define GESTURE_LIST_PUSH_MV1           EVENT_PUSH_MV1
#define GESTURE_LIST_DOUBLE_PUSH_MV1    EVENT_PUSH_MV1, EVENT_PUSH_MV1
#define GESTURE_LIST_PUSH_MV2           EVENT_PUSH_MV2
#define GESTURE_LIST_DOUBLE_PUSH_MV2    EVENT_PUSH_MV2, EVENT_PUSH_MV2
#define GESTURE_LIST_MV_RSWIPE          EVENT_PUSH_MV1, EVENT_PUSH_MV2
#define GESTURE_LIST_MV_LSWIPE          EVENT_PUSH_MV2, EVENT_PUSH_MV1
#define GESTURE_LIST_MV_DOUBLE_RSWIPE   GESTURE_LIST_MV_RSWIPE, GESTURE_LIST_MV_RSWIPE
#define GESTURE_LIST_MV_DOUBLE_LSWIPE   GESTURE_LIST_MV_LSWIPE, GESTURE_LIST_MV_LSWIPE
#define GESTURE_LIST_MV_RLSWIPE         GESTURE_LIST_MV_RSWIPE, GESTURE_LIST_MV_LSWIPE
#define GESTURE_LIST_MV_LRSWIPE         GESTURE_LIST_MV_LSWIPE, GESTURE_LIST_MV_RSWIPE
#define GESTURE_LIST_MV_RSWIPE_PUSH     GESTURE_LIST_MV_RSWIPE, EVENT_PUSH_MV2
#define GESTURE_LIST_MV_LSWIPE_PUSH     GESTURE_LIST_MV_LSWIPE, EVENT_PUSH_MV1
/*********************************************************************
 *********************************************************************/

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
  short events[7]; //XXX: 6 (+ 0 term) should be the most, some wasted space here but easier than parsing text definitions
  struct gesture_event *next; /* list of currently matching gestures */
};

struct gesture_event gestures[] = {
  /* Index finger */
  { EVENT_PUSH_IL1,         { GESTURE_LIST_PUSH_IL1, 0 } },
  { EVENT_PUSH_IL2,         { GESTURE_LIST_PUSH_IL2, 0 } },
  { EVENT_PUSH_IL3,         { GESTURE_LIST_PUSH_IL3, 0 } },
  { EVENT_DOUBLE_PUSH_IL1,  { GESTURE_LIST_DOUBLE_PUSH_IL1, 0 } },
  { EVENT_DOUBLE_PUSH_IL2,  { GESTURE_LIST_DOUBLE_PUSH_IL2, 0 } },
  { EVENT_DOUBLE_PUSH_IL3,  { GESTURE_LIST_DOUBLE_PUSH_IL3, 0 } },
  { EVENT_IL_RSWIPE,        { GESTURE_LIST_IL_RSWIPE, 0 } },
  { EVENT_IL_LSWIPE,        { GESTURE_LIST_IL_LSWIPE, 0 } },
  { EVENT_IL_DOUBLE_RSWIPE, { GESTURE_LIST_IL_DOUBLE_RSWIPE, 0 } },
  { EVENT_IL_DOUBLE_LSWIPE, { GESTURE_LIST_IL_DOUBLE_LSWIPE, 0 } },
  { EVENT_IL_RLSWIPE,       { GESTURE_LIST_IL_RLSWIPE, 0 } },
  { EVENT_IL_LRSWIPE,       { GESTURE_LIST_IL_LRSWIPE, 0 } },
  { EVENT_IL_RSWIPE_PUSH,   { GESTURE_LIST_IL_RSWIPE_PUSH, 0 } },
  { EVENT_IL_LSWIPE_PUSH,   { GESTURE_LIST_IL_LSWIPE_PUSH, 0 } },
  { EVENT_IL_RSWIPE,        { GESTURE_LIST_IL_ALT_RSWIPE, 0 } },
  { EVENT_IL_LSWIPE,        { GESTURE_LIST_IL_ALT_LSWIPE, 0 } },
  { EVENT_IL_RSWIPE_PUSH,   { GESTURE_LIST_IL_ALT_RSWIPE_PUSH, 0 } },
  { EVENT_IL_LSWIPE_PUSH,   { GESTURE_LIST_IL_ALT_LSWIPE_PUSH, 0 } },
  { EVENT_PUSH_IV1,         { GESTURE_LIST_PUSH_IV1, 0 } },
  { EVENT_PUSH_IV2,         { GESTURE_LIST_PUSH_IV2, 0 } },
  { EVENT_DOUBLE_PUSH_IV1,  { GESTURE_LIST_DOUBLE_PUSH_IV1, 0 } },
  { EVENT_DOUBLE_PUSH_IV2,  { GESTURE_LIST_DOUBLE_PUSH_IV2, 0 } },
  { EVENT_IV_RSWIPE,        { GESTURE_LIST_IV_RSWIPE, 0 } },
  { EVENT_IV_LSWIPE,        { GESTURE_LIST_IV_LSWIPE, 0 } },
  { EVENT_IV_DOUBLE_RSWIPE, { GESTURE_LIST_IV_DOUBLE_RSWIPE, 0 } },
  { EVENT_IV_DOUBLE_LSWIPE, { GESTURE_LIST_IV_DOUBLE_LSWIPE, 0 } },
  { EVENT_IV_RLSWIPE,       { GESTURE_LIST_IV_RLSWIPE, 0 } },
  { EVENT_IV_LRSWIPE,       { GESTURE_LIST_IV_LRSWIPE, 0 } },
  { EVENT_IV_RSWIPE_PUSH,   { GESTURE_LIST_IV_RSWIPE_PUSH, 0 } },
  { EVENT_IV_LSWIPE_PUSH,   { GESTURE_LIST_IV_LSWIPE_PUSH, 0 } },
  /* Middle finger */
  { EVENT_PUSH_ML1,         { GESTURE_LIST_PUSH_ML1, 0 } },
  { EVENT_PUSH_ML2,         { GESTURE_LIST_PUSH_ML2, 0 } },
  { EVENT_PUSH_ML3,         { GESTURE_LIST_PUSH_ML3, 0 } },
  { EVENT_DOUBLE_PUSH_ML1,  { GESTURE_LIST_DOUBLE_PUSH_ML1, 0 } },
  { EVENT_DOUBLE_PUSH_ML2,  { GESTURE_LIST_DOUBLE_PUSH_ML2, 0 } },
  { EVENT_DOUBLE_PUSH_ML3,  { GESTURE_LIST_DOUBLE_PUSH_ML3, 0 } },
  { EVENT_ML_RSWIPE,        { GESTURE_LIST_ML_RSWIPE, 0 } },
  { EVENT_ML_LSWIPE,        { GESTURE_LIST_ML_LSWIPE, 0 } },
  { EVENT_ML_DOUBLE_RSWIPE, { GESTURE_LIST_ML_DOUBLE_RSWIPE, 0 } },
  { EVENT_ML_DOUBLE_LSWIPE, { GESTURE_LIST_ML_DOUBLE_LSWIPE, 0 } },
  { EVENT_ML_RLSWIPE,       { GESTURE_LIST_ML_RLSWIPE, 0 } },
  { EVENT_ML_LRSWIPE,       { GESTURE_LIST_ML_LRSWIPE, 0 } },
  { EVENT_ML_RSWIPE_PUSH,   { GESTURE_LIST_ML_RSWIPE_PUSH, 0 } },
  { EVENT_ML_LSWIPE_PUSH,   { GESTURE_LIST_ML_LSWIPE_PUSH, 0 } },
  { EVENT_ML_RSWIPE,        { GESTURE_LIST_ML_ALT_RSWIPE, 0 } },
  { EVENT_ML_LSWIPE,        { GESTURE_LIST_ML_ALT_LSWIPE, 0 } },
  { EVENT_ML_RSWIPE_PUSH,   { GESTURE_LIST_ML_ALT_RSWIPE_PUSH, 0 } },
  { EVENT_ML_LSWIPE_PUSH,   { GESTURE_LIST_ML_ALT_LSWIPE_PUSH, 0 } },
  { EVENT_PUSH_MV1,         { GESTURE_LIST_PUSH_MV1, 0 } },
  { EVENT_PUSH_MV2,         { GESTURE_LIST_PUSH_MV2, 0 } },
  { EVENT_DOUBLE_PUSH_MV1,  { GESTURE_LIST_DOUBLE_PUSH_MV1, 0 } },
  { EVENT_DOUBLE_PUSH_MV2,  { GESTURE_LIST_DOUBLE_PUSH_MV2, 0 } },
  { EVENT_MV_RSWIPE,        { GESTURE_LIST_MV_RSWIPE, 0 } },
  { EVENT_MV_LSWIPE,        { GESTURE_LIST_MV_LSWIPE, 0 } },
  { EVENT_MV_DOUBLE_RSWIPE, { GESTURE_LIST_MV_DOUBLE_RSWIPE, 0 } },
  { EVENT_MV_DOUBLE_LSWIPE, { GESTURE_LIST_MV_DOUBLE_LSWIPE, 0 } },
  { EVENT_MV_RLSWIPE,       { GESTURE_LIST_MV_RLSWIPE, 0 } },
  { EVENT_MV_LRSWIPE,       { GESTURE_LIST_MV_LRSWIPE, 0 } },
  { EVENT_MV_RSWIPE_PUSH,   { GESTURE_LIST_MV_RSWIPE_PUSH, 0 } },
  { EVENT_MV_LSWIPE_PUSH,   { GESTURE_LIST_MV_LSWIPE_PUSH, 0 } },
};

#endif /* _FTALK_H */
/* vi: set ts=2 sw=2 expandtab: */
