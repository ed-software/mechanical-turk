/*
 *  Mr Pass.  Brain the size of a planet!
 *
 *  Proundly Created by Richard Buckland
 *  Share Freely Creative Commons SA-BY-NC 3.0.
 *
 *  FINISHED 12/05/16
 *  RESPECT THE ROBOT
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Game.h"
#include "mechanicalTurk.h"

#define NUM_DISCIPLINES 6
#define SPINOFF_COST { 0, 0, 0, 1, 1, 1 }

action decideAction (Game g) {
   
   // assume this program only runs when it is his turn
   int player = getWhoseTurn (g);

   int cost[NUM_DISCIPLINES] = SPINOFF_COST;

   int numMJ = getStudents (g, player, STUDENT_MJ);
   int numMTV = getStudents (g, player, STUDENT_MTV);
   int numMMONEY = getStudents (g, player, STUDENT_MMONEY);


   int canSpinoff = numMJ     >= cost[STUDENT_MJ] &&
                    numMTV    >= cost[STUDENT_MTV] &&
                    numMMONEY >= cost[STUDENT_MMONEY];

   action nextAction;
   if (canSpinoff) {
      nextAction.actionCode = START_SPINOFF;
   } else {
      nextAction.actionCode = PASS;
   }

   return nextAction;
}
