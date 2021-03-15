#include "samhain/status.h"
#include <sam.h>
#include <stdlib.h>

#define AHB 	(1<<16)
#define APBA	(2<<16)
#define APBB	(3<<16)
#define APBC	(4<<16)

//
// SAMD21 table

static const void* s_hardwares[] = {

	/* AHB */

	/* APBA */

	PAC0,
	PM,
	SYSCTRL,
	GCLK,
	WDT,
	RTC,
	EIC,

	/* APBB */

	/* APBC */

#ifdef PAC2
	PAC2,
#endif

#ifdef EVSYS
	EVSYS,
#endif

#ifdef SERCOM0	
	SERCOM0,
#endif

#ifdef SERCOM1
	SERCOM1,
#endif

#ifdef SERCOM2
	SERCOM2,
#endif

#ifdef SERCOM3
	SERCOM3,
#endif

#ifdef SERCOM4
	SERCOM4,
#endif

#ifdef SERCOM5
	SERCOM5,
#endif

#ifdef TCC0
	TCC0,
#endif

#ifdef TCC1
	TCC1,
#endif

#ifdef TCC2
	TCC2,
#endif

#ifdef TC3
	TC3,
#endif

#ifdef TC4
	TC4,
#endif

#ifdef TC5
	TC5,
#endif

#ifdef TC6
	TC6,
#endif

#ifdef TC7
	TC7,
#endif

#ifdef ADC
	ADC,
#endif

#ifdef AC
	AC,
#endif

#ifdef DAC
	DAC,
#endif

#ifdef PTC
	PTC,
#endif

#ifdef I2S
	I2S,
#endif

#ifdef AC1
	AC1,
#endif

	NULL
};

static const int s_masks[] = {
	APBA | 0,
	APBA | 1,
	APBA | 2,
	APBA | 3,
	APBA | 4,
	APBA | 5,
	APBA | 6,

#ifdef PAC2
	APBC | PM_APBCMASK_PAC2_Pos,
#endif

#ifdef EVSYS
	APBC | PM_APBCMASK_EVSYS_Pos,
#endif

#ifdef SERCOM0	
	APBC | PM_APBCMASK_SERCOM0_Pos,
#endif

#ifdef SERCOM1
	APBC | PM_APBCMASK_SERCOM1_Pos,
#endif

#ifdef SERCOM2
	APBC | PM_APBCMASK_SERCOM2_Pos,
#endif

#ifdef SERCOM3
	APBC | PM_APBCMASK_SERCOM3_Pos,
#endif

#ifdef SERCOM4
	APBC | PM_APBCMASK_SERCOM4_Pos,
#endif

#ifdef SERCOM5
	APBC | PM_APBCMASK_SERCOM5_Pos,
#endif

#ifdef TCC0
	APBC | PM_APBCMASK_TCC0_Pos,
#endif

#ifdef TCC1
	APBC | PM_APBCMASK_TCC1_Pos,
#endif

#ifdef TCC2
	APBC | PM_APBCMASK_TCC2_Pos,
#endif

#ifdef TC3
	APBC | PM_APBCMASK_TC3_Pos,
#endif

#ifdef TC4
	APBC | PM_APBCMASK_TC4_Pos,
#endif

#ifdef TC5
	APBC | PM_APBCMASK_TC5_Pos,
#endif

#ifdef TC6
	APBC | PM_APBCMASK_TC6_Pos,
#endif

#ifdef TC7
	APBC | PM_APBCMASK_TC7_Pos,
#endif

#ifdef ADC
	APBC | PM_APBCMASK_ADC_Pos,
#endif

#ifdef AC
	APBC | PM_APBCMASK_AC_Pos,
#endif

#ifdef DAC
	APBC | PM_APBCMASK_DAC_Pos,
#endif

#ifdef PTC
	APBC | PM_APBCMASK_PTC_Pos,
#endif

#ifdef I2S
	APBC | PM_APBCMASK_I2S_Pos,
#endif

#ifdef AC1
	APBC | PM_APBCMASK_AC1_Pos,
#endif

	0
};

static int find_mask(void *hw) {
	for (int i = 0; s_hardwares[i]; ++i) {
		if (s_hardwares[i] == hw) {
			return s_masks[i];
		}
	}
	return 0;
}

static int get_prescaler_bits(int prescaler) {
	switch (prescaler) {
		case 1: return 0x0;
		case 2: return 0x1;
		case 4: return 0x2;
		case 8: return 0x3;
		case 16: return 0x4;
		case 32: return 0x5;
		case 64: return 0x6;
		case 128: return 0x7;
		default: return -1;
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

samh_status_t samh_pm_enable(void *hw) {
	int mask = find_mask(hw);
	if (mask == 0) {
		return SAMH_ERR_INVALID_ARG;
	}
	int bit = mask & 0x1F;
	switch (mask & 0xFFFF0000) {
		case AHB:	PM->AHBMASK.reg  |= (1 << bit); break;
		case APBA:	PM->APBAMASK.reg |= (1 << bit); break;
		case APBB:	PM->APBBMASK.reg |= (1 << bit); break;
		case APBC:	PM->APBCMASK.reg |= (1 << bit); break;
	}
	return SAMH_OK;
}

samh_status_t samh_pm_disable(void *hw) {
	int mask = find_mask(hw);
	if (mask == 0) {
		return SAMH_ERR_INVALID_ARG;
	}
	int bit = mask & 0x1F;
	switch (mask & 0xFFFF0000) {
		case AHB:	PM->AHBMASK.reg  &= ~(1 << bit); break;
		case APBA:	PM->APBAMASK.reg &= ~(1 << bit); break;
		case APBB:	PM->APBBMASK.reg &= ~(1 << bit); break;
		case APBC:	PM->APBCMASK.reg &= ~(1 << bit); break;
	}
	return SAMH_OK;
}