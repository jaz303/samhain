#ifndef SAMHAIN_DELAY_H_
#define SAMHAIN_DELAY_H_

#include <stdint.h>

#ifndef SAMH_F_CPU
#error "You must define SAMH_F_CPU"
#endif

#define SAMH_DELAY_CYCLES_PER_TICK		8
#define SAMH_DELAY_MS_TO_TICKS(ms)		(uint32_t)(SAMH_F_CPU / 1000 * (ms) / SAMH_DELAY_CYCLES_PER_TICK)

#define samh_delay_ticks(ticks)			{ volatile uint32_t n = (ticks); while (n--); }
#define samh_delay_ms(ms)				samh_delay_ticks(SAMH_DELAY_MS_TO_TICKS(ms));

#endif
