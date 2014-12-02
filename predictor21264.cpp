/*************************************************************************
/
/ filename: predictor21264.cpp
/
/ description:
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

#include "predictor21264.h"
#include <string.h>
#include <limits.h>

unsigned short localHistory[LOCAL_HISTORY_TABLE_SIZE];
unsigned short localPrediction[LOCAL_PREDICTION_TABLE_SIZE];
unsigned char globalHistory;
unsigned short globalPrediction[GLOBAL_PREDICTION_TABLE_SIZE];
unsigned short choicePrediction[CHOICE_PREDICTION_TABLE_SIZE];

void init_predictor ()
{
    memset(localHistory, 0, LOCAL_HISTORY_TABLE_SIZE * sizeof(unsigned short));
    memset(localPrediction, 0, LOCAL_PREDICTION_TABLE_SIZE * sizeof(unsigned short));
    memset(globalPrediction, 0, GLOBAL_PREDICTION_TABLE_SIZE * sizeof(unsigned short));
    memset(choicePrediction, 0, CHOICE_PREDICTION_TABLE_SIZE * sizeof(unsigned short));
    globalHistory = 0;
}

bool choice_prediction (unsigned int pc) {
    pc &= (1 << GLOBAL_HISTORY_SIZE) - 1;
    return choicePrediction[pc] >= (1 << (CHOICE_PREDICTION_TABLE_BITS - 1));
}

// But was that last choice right?
bool choice_right (unsigned int pc, bool outcome) {
    unsigned int pc_lp = pc & ((1 << LOCAL_HISTORY_TABLE_BITS) - 1);
    unsigned int pc_gp = pc & ((1 << GLOBAL_HISTORY_SIZE) - 1);

    if (choice_prediction(pc)) {
        // global prediction was chosen?
        return outcome == // Should return True for outcome matching prediction
            (globalPrediction[pc_gp] >=
                (1 << (GLOBAL_PREDICTION_TABLE_BITS - 1))
            );
    } else {
        // local
        return outcome ==
            (localPrediction[pc_lp] >=
                (1 << (LOCAL_PREDICTION_TABLE_BITS - 1))
            );
    }
}

bool make_prediction (unsigned int pc)
{
    unsigned int pc_lp = pc & ((1 << LOCAL_HISTORY_TABLE_BITS) - 1);
    unsigned int pc_gp = pc & ((1 << GLOBAL_HISTORY_SIZE) - 1);

    if (choice_prediction(pc)) {
        return globalPrediction[pc_gp] >= (1 << (GLOBAL_PREDICTION_TABLE_BITS - 1));
    } else {
        return localPrediction[pc_lp] >= (1 << (LOCAL_PREDICTION_TABLE_BITS - 1));
    }
}

void train_predictor (unsigned int pc, bool outcome)
{
    unsigned int pc_lh = pc & ((1 << LOCAL_HISTORY_TABLE_BITS) - 1);
    unsigned int pc_lp = pc & ((1 << LOCAL_HISTORY_TABLE_BITS) - 1);
    unsigned int pc_gp = pc & ((1 << GLOBAL_HISTORY_SIZE) - 1);
    unsigned int pc_cp = pc & ((1 << GLOBAL_HISTORY_SIZE) - 1);

    if(choice_right(pc, outcome)) {
        choicePrediction[pc_cp] += localPrediction[pc_cp] < (1 << LOCAL_HISTORY_TABLE_BITS) - 1 ? 1 : 0; // Max out at LOCAL_HISTORY_TABLE_MAX (don't overflow)
    } else {
        choicePrediction[pc_cp] -= choicePrediction[pc_cp] > 0 ? 1 : 0; // Min out at 0 (don't overflow)
    }

    globalHistory <<= 1;
    globalHistory += outcome;
    globalHistory &= ~(USHRT_MAX - GLOBAL_HISTORY_SIZE);

    localHistory[pc_lh] <<= 1;
    localHistory[pc_lh] += outcome;
    localHistory[pc_lh] &= ~(USHRT_MAX - GLOBAL_HISTORY_SIZE);

    unsigned short *current_local = &(localPrediction[localHistory[pc_lh] ^ pc_lp]);
    unsigned short *current_global = &(globalPrediction[globalHistory ^ pc_gp]);
    if(outcome) {
        *current_local += *current_local < (1 << LOCAL_HISTORY_TABLE_BITS) - 1 ? 1 : 0;
        *current_global += *current_global < (1 << GLOBAL_HISTORY_SIZE) - 1 ? 1 : 0;
    } else {
        *current_local -= *current_local > 0 ? 1 : 0;
        *current_global -= *current_global > 0 ? 1 : 0;
    }
}
