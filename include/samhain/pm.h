#ifndef SAMHAIN_PM_H_
#define SAMHAIN_PM_H_

// Power Manager
//
// Functions for setting prescalers and enabling/disabling peripherals.
//
// Out of scope for now:
//   - Sleep mode (simple register access)
//   - Interrupts (simple register access)
//   - Reset cause (simple register access)
//
// TODO: AHBMASK is currently unimplemented

#include "samhain/status.h"

samh_status_t samh_pm_set_cpu_prescaler(int prescaler);
samh_status_t samh_pm_set_apba_prescaler(int prescaler);
samh_status_t samh_pm_set_apbb_prescaler(int prescaler);
samh_status_t samh_pm_set_apbc_prescaler(int prescaler);

samh_status_t samh_pm_enable(void *hw);
samh_status_t samh_pm_disable(void *hw);

#endif