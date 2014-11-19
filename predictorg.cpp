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
    memset(branchHistory, 0, BRANCH_HISTORY_SIZE * sizeof(unsigned char));
}

bool make_prediction (unsigned int pc)
{
    pc &= (1 << GLOBAL_HISTORY_SIZE) - 1; //truncates PC to within branchHistory table size
    return branchHistory[pc] >= (1 << (BRANCH_HISTORY_BITS - 1)); //Make the prediction
}

void train_predictor (unsigned int pc, bool outcome)
{
    pc &= (1 << GLOBAL_HISTORY_SIZE) - 1;
    globalHistory <<= 1; //left shift and resign
    globalHistory += outcome; // add outcome to end (outcome is implicitly typecast to int as 1 or 0)
    globalHistory &= ~(USHRT_MAX - GLOBAL_HISTORY_SIZE); //truncate to needed size
    
    unsigned char *current_p = &(branchHistory[globalHistory ^ pc]); //pointing to needed value in array
    
    if(outcome)
    {
        *current_p += (*current_p < (1 << BRANCH_HISTORY_BITS) - 1) ? 1 : 0; //Calculating value then putting back where pointer points to
    }
    else
    {
        *current_p -= (*current_p > 0) ? 1 : 0;
    }
}
