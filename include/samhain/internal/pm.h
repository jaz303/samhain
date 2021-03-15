#ifndef SAMHAIN_INTERNAL_PM_H_
#define SAMHAIN_INTERNAL_PM_H_

#include <stdint.h>

struct hardware_pm {
	void *hw;
	uint8_t bus;
	uint8_t bit;
};

#define AHB 	1
#define APBA	2
#define APBB	3
#define APBC 	4

#endif