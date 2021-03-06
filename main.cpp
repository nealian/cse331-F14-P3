/*************************************************************************
/
/ filename: main.cpp
/
/ description: Takes a trace file, call predictors. Mostly untouched.
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

#include <stdio.h>
#include <netinet/in.h>
#include "traceread.h"

// Use the correct header for the target; determined by the Makefile.
#ifdef PREDICTORG
  #include "predictorg.h"
#endif
#ifdef PREDICTOR21264
  #include "predictor21264.h"
#endif

FILE * stream;

void setup_trace (const char * filename)

{
    if (filename == NULL)
    {
        stream = stdin;
    }
    
    else
    {
        stream = fopen (filename, "r"); //r is for read mode
    }
}

void close_trace ()

{
    fclose (stream);
}

int main (int argc, char * argv[])

{
    long mis_preds = 0;
    long num_branches = 0;
    uint32_t pc = 0;
    bool outcome = false;
    
    // Initialize the predictor
    init_predictor ();
    if (argc == 2)
    {
        setup_trace (argv[1]);
    }
    else
    {
        setup_trace (NULL);
    }
    
    
    // Read the number of instructions from the trace
    uint32_t stat_num_insts = 0;
    
    if (fread (&stat_num_insts, sizeof (uint32_t), 1, stream) != 1)
    {
        printf ("Could not read intput file\n");
        return 1;
    }
    
    stat_num_insts = ntohl (stat_num_insts);

    // Read each branch from the trace
    while (read_branch (&pc, &outcome))
    {
        pc = ntohl (pc);
        num_branches ++;
        
        // Make a prediction and compare with actual outcome
        if (make_prediction (pc) != outcome)
        {
            mis_preds ++;
        }
        
        // Train the predictor
        train_predictor (pc, outcome);
    }
    
    // Print out the mispredict statistics
    printf ("Branches\t\t%10ld\n", num_branches);
    printf ("Incorrect\t\t%10ld\n", mis_preds);
    float mis_pred_rate = 100*(float)mis_preds / float(num_branches);
    printf ("100*wrong_predicts/total branches is %8ld / %8ld = %7.3f\n", mis_preds, num_branches, mis_pred_rate);
    
    if (argc == 2)
    {
        close_trace ();
    }
    
    return 0;
}

