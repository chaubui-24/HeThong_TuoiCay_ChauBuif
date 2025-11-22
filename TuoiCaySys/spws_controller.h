#ifndef SPWS_CONTROLLER_H
#define SPWS_CONTROLLER_H

#include "config.h"

void SPWS_Init(SystemState_t *state);

void SPWS_RunOnce(SystemState_t *state, unsigned int elapsed_s);

#endif