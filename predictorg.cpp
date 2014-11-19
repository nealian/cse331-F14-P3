/*************************************************************************
/
/ filename: predictorg.cpp
/
/ description: gshare predictor
/
/ authors: Neal, Ian
/ Gallegos, Cristobal
/
/ class: CSE 331
/ instructor: Zheng
/ assignment: Lab Project #3
/
/ assigned: Nov 11, 2014
/ due: Dec 2, 2014
/
 ************************************************************************/

#include "predictorg.h"
#include <string.h>
#include <limits.h>

unsigned short globalHistory;
unsigned char branchHistory[BRANCH_HISTORY_SIZE];

void init_predictor ()
{
    globalHistory = 0;
    memset(branchHistory, 0, BRANCH_HISTORY_SIZE * sizeof(char));
}

bool make_prediction (unsigned int pc)
{
    return false;
}

void train_predictor (unsigned int pc, bool outcome)
{
    globalHistory <<= 1; //left shift and resign
    globalHistory += outcome; // add outcome to end (outcome is implicitly typecast to int as 1 or 0)
    globalHistory &= ~(USHRT_MAX - GLOBAL_HISTORY_SIZE); //truncate to needed size
    
    branchHistory[pc] = (globalHistory ^ pc) & ((1 << BRANCH_HISTORY_BITS) - 1); //Place XOR value in branch history table
}
