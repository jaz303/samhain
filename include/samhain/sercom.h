#ifndef SAMHAIN_SERCOM_
#define SAMHAIN_SERCOM_

#include <sam.h>

IRQn_Type samh_sercom_get_irq(Sercom *hw);

void samh_sercom_sw_reset(Sercom *hw);
void samh_sercom_irq_enable(Sercom *hw);
void samh_sercom_irq_disable(Sercom *hw);

#endif