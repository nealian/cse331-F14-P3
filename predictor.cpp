//
//  predictor.cpp
//  BranchPrediction
//
//  Created by Cris Gallegos  on 11/18/14.
//  Copyright (c) 2014 Cris Gallegos . All rights reserved.
//

#include "predictor.h"
// A very stupid predictor.  It will always predict not taken.

void init_predictor ()
{
}

bool make_prediction (unsigned int pc)
{
    return false;
}

void train_predictor (unsigned int pc, bool outcome)
{
}
