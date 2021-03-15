#ifndef SAMHAIN_CLOCKS_H_
#define SAMHAIN_CLOCKS_H_

#include "samhain/status.h"

void samh_osc8_set_enabled(int enabled);
samh_status_t samh_osc8_set_prescaler(int prescaler);

#endif