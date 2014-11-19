/*************************************************************************
/
/ filename: predictor.h
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

#ifndef PREDICTOR_H
#define PREDICTOR_H

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
