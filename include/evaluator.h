#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "com.h"

#define CORNER_POINT  120
#define X_POINT       90
#define C_POINT       80

void Evaluator_evaluate(const Board *board, int next_color, int *eval_point);

#endif
