#include "samhain/status.h"

#include <sam.h>

void samh_osc8_set_enabled(int enabled) {
	SYSCTRL->OSC8M.bit.ENABLE = enabled;
}

samh_status_t samh_osc8_set_prescaler(int prescaler) {
	switch (prescaler) {
		case 1: 	SYSCTRL->OSC8M.bit.PRESC = 0; break; // 8MHz
		case 2: 	SYSCTRL->OSC8M.bit.PRESC = 1; break; // 4MHz
		case 4: 	SYSCTRL->OSC8M.bit.PRESC = 2; break; // 2MHz
		case 8: 	SYSCTRL->OSC8M.bit.PRESC = 3; break; // 1MHz
		default:	return SAMH_ERR_INVALID_ARG;
	}
	return SAMH_OK;
}
