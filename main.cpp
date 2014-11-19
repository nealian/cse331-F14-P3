//
//  main.cpp
//  BranchPrediction
//
//  Created by Cris Gallegos  on 11/18/14.
//  Copyright (c) 2014 Cris Gallegos . All rights reserved.
//

#include <stdio.h>
#include <netinet/in.h>
#include "traceread.h"
#include "predictor.h"

FILE * stream;

void setup_trace (const char * filename)

{
    if (filename == NULL)
    {
        stream = stdin;
    }
    
    else
    {
        stream = fopen (filename, "r");
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
    printf ("Branches\t\t%10d\n", num_branches);
    printf ("Incorrect\t\t%10d\n", mis_preds);
    float mis_pred_rate = 100*(float)mis_preds / float(num_branches);
    printf ("100*wrong_predicts/total branches is %8d / %8d = %7.3f\n", mis_preds, num_branches, mis_pred_rate);
    
    if (argc == 2)
    {
        close_trace ();
    }
    
    return 0;
}

