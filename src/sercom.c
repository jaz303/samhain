#include "samhain/sercom.h"

IRQn_Type samh_sercom_get_irq(Sercom *hw) {
	return (IRQn_Type)(SERCOM0_IRQn + (((uint32_t)hw - (uint32_t)SERCOM0) >> 10));;
}

void samh_sercom_sw_reset(Sercom *hw) {
	hw->USART.CTRLA.bit.SWRST = 1;
	while (hw->USART.SYNCBUSY.bit.SWRST);
}

void samh_sercom_irq_enable(Sercom *hw) {
	NVIC_EnableIRQ(samh_sercom_get_irq(hw));
}

void samh_sercom_irq_disable(Sercom *hw) {
	NVIC_DisableIRQ(samh_sercom_get_irq(hw));
}