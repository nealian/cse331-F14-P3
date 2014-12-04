/*************************************************************************
/
/ filename: predictor21264.h
/
/ description: The tournament-style branch predictor with both local and
/   global predictions, and a predictor to select between the two.
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

#ifndef PREDICTOR21264_H
#define PREDICTOR21264_H

/*
 Define all your tables and their sizes here.
 All tables must be statically-sized.
 Please don't call malloc () or any of its relatives within your
 program.  The predictor will have a budget, namely (64K + 256) bits
 (not bytes).  That encompasses all storage (all tables, plus GHR, if
 necessary -- but not PC) used for the predictor.  That may not be
 the amount of storage your predictor uses, however -- for example,
 you may implement 2-bit predictors with a table of ints, in which
 case the simulator will use more memory -- that's okay, we're only
 concerned about the memory used by the simulated branch predictor.
 */

#define LOCAL_HISTORY_TABLE_SIZE 1024
#define LOCAL_HISTORY_TABLE_BITS 10
#define LOCAL_PREDICTION_TABLE_SIZE 1024
#define LOCAL_PREDICTION_TABLE_BITS 3
#define GLOBAL_HISTORY_SIZE 12
#define GLOBAL_PREDICTION_TABLE_SIZE 4096
#define GLOBAL_PREDICTION_TABLE_BITS 2
#define CHOICE_PREDICTION_TABLE_SIZE 4096
#define CHOICE_PREDICTION_TABLE_BITS 2 // >half use global, <half use local

// THESE NEED TO BE DEFINED IN THE CPP FILE
/* unsigned short localHistory[LOCAL_HISTORY_TABLE_SIZE]; */
/* unsigned char localPrediction[LOCAL_PREDICTION_TABLE_SIZE]; */
/* unsigned short globalHistory; */
/* unsigned char globalPrediction[GLOBAL_PREDICTION_TABLE_SIZE]; */
/* unsigned char choicePrediction[CHOICE_PREDICTION_TABLE_SIZE]; */

/*
 Initialize the predictor.
 */
void init_predictor ();

/*
 Make a prediction for conditional branch instruction at PC 'pc'.
 Returning true indicates a prediction of taken; returning false
 indicates a prediction of not taken.
 */
bool make_prediction (unsigned int pc);

/*
 Train the predictor the last executed branch at PC 'pc' and with
 outcome 'outcome' (true indicates that the branch was taken, false
 indicates that the branch was not taken).
 */
void train_predictor (unsigned int pc, bool outcome);

#endif
