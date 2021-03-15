#include "samhain/internal/pm.h"
#include <sam.h>
#include <stdlib.h>

const struct hardware_pm samh_pm_hardware[] = {
	
	// APBA

	{ PAC0, APBA, PM_APBAMASK_PAC0_Pos },
	{ PM, APBA, PM_APBAMASK_PM_Pos },
	{ SYSCTRL, APBA, PM_APBAMASK_SYSCTRL_Pos },
	{ GCLK, APBA, PM_APBAMASK_GCLK_Pos },
	{ WDT, APBA, PM_APBAMASK_WDT_Pos },
	{ RTC, APBA, PM_APBAMASK_RTC_Pos },
	{ EIC, APBA, PM_APBAMASK_EIC_Pos },

	// APBB

	{ PAC1, APBB, PM_APBBMASK_PAC1_Pos },
	{ DSU, APBB, PM_APBBMASK_DSU_Pos },
	{ NVMCTRL, APBB, PM_APBBMASK_NVMCTRL_Pos },
	{ PORT, APBB, PM_APBBMASK_PORT_Pos },
	{ DMAC, APBB, PM_APBBMASK_DMAC_Pos },

#ifdef USB
	{ USB, APBB, PM_APBBMASK_USB_Pos },
#endif

	// APBC

	{ PAC2, APBC, PM_APBCMASK_PAC2_Pos },
	{ EVSYS, APBC, PM_APBCMASK_EVSYS_Pos },
	{ SERCOM0, APBC, PM_APBCMASK_SERCOM0_Pos },
	{ SERCOM1, APBC, PM_APBCMASK_SERCOM1_Pos },
	{ SERCOM2, APBC, PM_APBCMASK_SERCOM2_Pos },
	{ SERCOM3, APBC, PM_APBCMASK_SERCOM3_Pos },

#ifdef SERCOM4
	{ SERCOM4, APBC, PM_APBCMASK_SERCOM4_Pos },
#endif

#ifdef SERCOM5
	{ SERCOM5, APBC, PM_APBCMASK_SERCOM5_Pos },
#endif

#ifdef TCC0
	{ TCC0, APBC, PM_APBCMASK_TCC0_Pos },
#endif

#ifdef TCC1
	{ TCC1, APBC, PM_APBCMASK_TCC1_Pos },
#endif

#ifdef TCC2
	{ TCC2, APBC, PM_APBCMASK_TCC2_Pos },
#endif

#ifdef TC3
	{ TC3, APBC, PM_APBCMASK_TC3_Pos },
#endif

#ifdef TC4
	{ TC4, APBC, PM_APBCMASK_TC4_Pos },
#endif

#ifdef TC5
	{ TC5, APBC, PM_APBCMASK_TC5_Pos },
#endif

#ifdef TC6
	{ TC6, APBC, PM_APBCMASK_TC6_Pos },
#endif

#ifdef TC7
	{ TC7, APBC, PM_APBCMASK_TC7_Pos },
#endif

#ifdef ADC
	{ ADC, APBC, PM_APBCMASK_ADC_Pos },
#endif

#ifdef DAC
	{ DAC, APBC, PM_APBCMASK_DAC_Pos },
#endif

#ifdef PTC
	{ PTC, APBC, PM_APBCMASK_PTC_Pos },
#endif

#ifdef I2S
	{ I2S, APBC, PM_APBCMASK_I2S_Pos },
#endif

#ifdef AC1
	{ AC1, APBC, PM_APBCMASK_AC1_Pos },
#endif

	{ NULL, 0, 0 }
};
