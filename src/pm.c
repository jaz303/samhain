#include "samhain/status.h"
#include "samhain/internal/pm.h"
#include <sam.h>
#include <stdlib.h>

extern const struct hardware_pm samh_pm_hardware[];

static int get_prescaler_bits(int prescaler) {
	switch (prescaler) {
		case 1: 	return 0x0;
		case 2: 	return 0x1;
		case 4: 	return 0x2;
		case 8: 	return 0x3;
		case 16: 	return 0x4;
		case 32: 	return 0x5;
		case 64: 	return 0x6;
		case 128:	return 0x7;
		default: 	return -1;
	}
}

samh_status_t samh_pm_set_cpu_prescaler(int prescaler) {
	int bits = get_prescaler_bits(prescaler);
	if (bits < 0) {
		return SAMH_ERR_INVALID_ARG;
	}
	PM->CPUSEL.bit.CPUDIV = bits;
	return SAMH_OK;
}

samh_status_t samh_pm_set_apba_prescaler(int prescaler) {
	int bits = get_prescaler_bits(prescaler);
	if (bits < 0) {
		return SAMH_ERR_INVALID_ARG;
	}
	PM->APBASEL.bit.APBADIV = bits;
	return SAMH_OK;
}

samh_status_t samh_pm_set_apbb_prescaler(int prescaler) {
	int bits = get_prescaler_bits(prescaler);
	if (bits < 0) {
		return SAMH_ERR_INVALID_ARG;
	}
	PM->APBBSEL.bit.APBBDIV = bits;
	return SAMH_OK;
}

samh_status_t samh_pm_set_apbc_prescaler(int prescaler) {
	int bits = get_prescaler_bits(prescaler);
	if (bits < 0) {
		return SAMH_ERR_INVALID_ARG;
	}
	PM->APBCSEL.bit.APBCDIV = bits;
	return SAMH_OK;
}

static const struct hardware_pm* find_mask(void *hw) {
	for (int i = 0; samh_pm_hardware[i].hw; ++i) {
		if (samh_pm_hardware[i].hw == hw) {
			return &samh_pm_hardware[i];
		}
	}
	return NULL;
}

samh_status_t samh_pm_enable(void *hw) {
	const struct hardware_pm *mask = find_mask(hw);
	if (mask == NULL) {
		return SAMH_ERR_INVALID_ARG;
	}
	
	switch (mask->bus) {
		case AHB:	PM->AHBMASK.reg  |= (1 << mask->bit); break;
		case APBA:	PM->APBAMASK.reg |= (1 << mask->bit); break;
		case APBB:	PM->APBBMASK.reg |= (1 << mask->bit); break;
		case APBC:	PM->APBCMASK.reg |= (1 << mask->bit); break;
	}
	
	return SAMH_OK;
}

samh_status_t samh_pm_disable(void *hw) {
	const struct hardware_pm *mask = find_mask(hw);
	if (mask == NULL) {
		return SAMH_ERR_INVALID_ARG;
	}

	switch (mask->bus) {
		case AHB:	PM->AHBMASK.reg  &= ~(1 << mask->bit); break;
		case APBA:	PM->APBAMASK.reg &= ~(1 << mask->bit); break;
		case APBB:	PM->APBBMASK.reg &= ~(1 << mask->bit); break;
		case APBC:	PM->APBCMASK.reg &= ~(1 << mask->bit); break;
	}

	return SAMH_OK;
}