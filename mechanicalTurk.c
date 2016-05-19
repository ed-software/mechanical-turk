/*
 *  Nelson Odins-Jones
 *
 *  I have no idea how this will go. I just wanted to
 *  get something in before tomorrow's tutorial.
 *
 *  Godspeed, fair Turk!
 *  Version 3
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "Game.h"
#include "mechanicalTurk.h"

#define TRUE 1
#define FALSE 0

#define ALL_PATHS { \
    "L", \
    "RR", \
    "R", \
    "LR", \
    "LRL", \
    "RRLR", \
    "RRL", \
    "RL", \
    "RLL", \
    "LRLR", \
    "LRLRL", \
    "RRLRL", \
    "RRLL", \
    "RLR", \
    "RLLR", \
    "RLLRL", \
    "LRLRLR", \
    "RRLRLL", \
    "RRLLR", \
    "RLRL", \
    "RLRLL", \
    "LRRLLR", \
    "LRRLLRL", \
    "RRLRLLR", \
    "RRLRLLLR", \
    "RRLRLLLRL", \
    "RLRLLR", \
    "RLRLLRL", \
    "RLLRLRLR", \
    "RRLRLLRL", \
    "RRLRLLRLL", \
    "RLRLRL", \
    "RLRLRLL", \
    "LRRLLRRL", \
    "LRRLLRRLL", \
    "RRLRLLRLR", \
    "RRLLRLRL", \
    "RRLLRLRLL", \
    "LRRLRLRL", \
    "LRRLRLRLL", \
    "LRRLLRRLLR", \
    "RRLRLLRLRL", \
    "RRLRLLRLRLL", \
    "RLRLRLRL", \
    "RLRLRLRLL", \
    "LRRLRLLRRL", \
    "LRRLRLLRRLL", \
    "RRLRLLRLRLLR", \
    "RRLRLLRLRLLRL", \
    "LRRLRLRLRL", \
    "LRRLRLRLRLL", \
    "RRLRLLRLRLLRLR", \
    "RRLRLLRLRLLRLRL", \
}
#define NUM_VERTICES 54
#define NUM_DISCIPLINES 6
#define SPINOFF_COST { 0, 0, 0, 1, 1, 1 }

action decideAction (Game g) {

   // assume this program only runs when it is his turn
   int playerID = getWhoseTurn (g);
   action nextAction;
   nextAction.actionCode = PASS;

   path allPaths[NUM_VERTICES] = ALL_PATHS;
   int found = 0;

   // if it can build a go8, do that

   int i = 0;
   while (i < NUM_VERTICES && !found) {
      nextAction.actionCode = BUILD_GO8;
      strcpy(nextAction.destination, allPaths[i]);
      if (isLegalAction(g, nextAction)) {
         found = TRUE;
      }
      i++;
   }

   // if not, and it can build a campus, do that

   i = 0;
   while (i < NUM_VERTICES && !found) {
      nextAction.actionCode = BUILD_CAMPUS;
      strcpy(nextAction.destination, allPaths[i]);
      if (isLegalAction(g, nextAction)) {
         found = TRUE;
      }
      i++;
   }

   // if not, and it can do a spinoff, do that

   int spinCost[NUM_DISCIPLINES] = SPINOFF_COST;

   int numMJ = getStudents (g, playerID, STUDENT_MJ);
   int numMTV = getStudents (g, playerID, STUDENT_MTV);
   int numMMONEY = getStudents (g, playerID, STUDENT_MMONEY);

   int canSpinoff = numMJ     >= spinCost[STUDENT_MJ] &&
                    numMTV    >= spinCost[STUDENT_MTV] &&
                    numMMONEY >= spinCost[STUDENT_MMONEY];

   if (canSpinoff && !found) {
      found = TRUE;
      nextAction.actionCode = START_SPINOFF;
   }

   // if not, and it can build an arc, do that

   i = 0;
   while (i < NUM_VERTICES && !found) {
      nextAction.actionCode = OBTAIN_ARC;
      strcpy(nextAction.destination, allPaths[i]);
      if (isLegalAction(g, nextAction)) {
         found = TRUE;
      }
      i++;
   }

   // if all else fails, pass
   printf("Action code: %d\n", nextAction.actionCode);
   return nextAction;
}
