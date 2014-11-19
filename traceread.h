/*************************************************************************
/
/ filename: traceread.h
/
/ description: Reads the trace files
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

#ifndef TRACEREAD_H
#define TRACEREAD_H


/*
 Read the next conditional branch from the trace from stdin.
 Returns true if a conditional branch was found, false otherwise.
 The first pointer argument will contain the branch instruction's PC.
 The second pointer argument will contain the branch outcome.
 */

bool read_branch (unsigned int * pc, bool * outcome);


#endif

