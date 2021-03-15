#include "samhain/port.h"

#include <sam.h>

#define EXTRACT_PP() \
	uint8_t port = SAMH_PORT(gpio); \
	uint8_t pin  = SAMH_PIN(gpio)

void samh_port_set_gpio_direction(uint8_t gpio, int direction) {
	EXTRACT_PP();

	if (direction == SAMH_DIR_OUTPUT) {
		PORT->Group[port].DIRSET.reg = (1 << pin);
	} else {
		PORT->Group[port].DIRCLR.reg = (1 << pin);
	}
}

int samh_port_get_gpio_level(uint8_t gpio) {
	EXTRACT_PP();

	return PORT->Group[port].IN.reg & (1 << pin);
}

void samh_port_set_gpio_level(uint8_t gpio, int level) {
	EXTRACT_PP();

	if (level) {
		PORT->Group[port].OUTSET.reg = (1 << pin);
	} else {
		PORT->Group[port].OUTCLR.reg = (1 << pin);
	}
}

void samh_port_toggle_gpio_level(uint8_t gpio) {
	EXTRACT_PP();

	PORT->Group[port].OUTTGL.reg = (1 << pin);
}

void samh_port_set_gpio_pull_mode(uint8_t gpio, int pull_mode) {
	EXTRACT_PP();

	switch (pull_mode) {
		case SAMH_PULL_NONE:
			PORT->Group[port].PINCFG[pin].bit.PULLEN = 0;
			break;
		case SAMH_PULL_UP:
			PORT->Group[port].PINCFG[pin].bit.PULLEN = 1;
			PORT->Group[port].OUTSET.reg |= (1 << pin);
			break;
		case SAMH_PULL_DOWN:
			PORT->Group[port].PINCFG[pin].bit.PULLEN = 1;
			PORT->Group[port].OUTCLR.reg |= (1 << pin);
			break;
	}
}

void samh_port_set_gpio_function(uint8_t gpio, int function) {
	EXTRACT_PP();

	if (function == SAMH_PIN_FUNCTION_OFF) {
		PORT->Group[port].PINCFG[pin].bit.PMUXEN = 0;
	} else {
		function &= 0x0F;
		uint32_t tmp = PORT->Group[port].PMUX[pin >> 1].reg;
		if (pin & 1) {
			tmp &= ~PORT_PMUX_PMUXO_Msk;
			tmp |= PORT_PMUX_PMUXO(function);
		} else {
			tmp &= ~PORT_PMUX_PMUXE_Msk;
			tmp |= PORT_PMUX_PMUXE(function);
		}
		PORT->Group[port].PMUX[pin >> 1].reg = tmp;
		PORT->Group[port].PINCFG[pin].bit.PMUXEN = 1;
	}
}

void samh_port_set_gpio_input_enabled(uint8_t gpio, int enabled) {
	EXTRACT_PP();

	PORT->Group[port].PINCFG[pin].bit.INEN = enabled;
}

void samh_port_set_gpio_strong_drive_enabled(uint8_t gpio, int enabled) {
	EXTRACT_PP();

	PORT->Group[port].PINCFG[pin].bit.DRVSTR = enabled;	
}

uint32_t samh_port_get_port_levels(uint8_t port, uint32_t mask) {
	return PORT->Group[port].IN.reg & mask;
}

void samh_port_set_port_levels(uint8_t port, uint32_t mask, uint32_t values) {
	// uint32_t val = PORT->Group[port].OUT.reg;
	// PORT->Group[port].OUT.reg = (val ^ mask) | (values & mask);
	// 0 0 -> 0 // ok
	// 0 1 -> 1 // wrong
	// 1 0 -> 1 // ok
	// 1 1 -> 0 // ok, want to set from vals

}

void samh_port_toggle_port_levels(uint8_t port, uint32_t mask) {
	PORT->Group[port].OUTTGL.reg = mask;
}

// /**
//  * \brief Set direction on port with mask
//  */
// static inline void _gpio_set_direction(const enum gpio_port port, const uint32_t mask,
//                                        const enum gpio_direction direction)
// {
// 	switch (direction) {
// 	case GPIO_DIRECTION_OFF:
// 		hri_port_clear_DIR_reg(PORT_IOBUS, port, mask);
// 		hri_port_write_WRCONFIG_reg(PORT, port, PORT_WRCONFIG_WRPINCFG | (mask & 0xffff));
// 		hri_port_write_WRCONFIG_reg(
// 		    PORT, port, PORT_WRCONFIG_HWSEL | PORT_WRCONFIG_WRPINCFG | ((mask & 0xffff0000) >> 16));
// 		break;

// 	case GPIO_DIRECTION_IN:
// 		hri_port_clear_DIR_reg(PORT_IOBUS, port, mask);
// 		hri_port_write_WRCONFIG_reg(PORT, port, PORT_WRCONFIG_WRPINCFG | PORT_WRCONFIG_INEN | (mask & 0xffff));
// 		hri_port_write_WRCONFIG_reg(PORT,
// 		                            port,
// 		                            PORT_WRCONFIG_HWSEL | PORT_WRCONFIG_WRPINCFG | PORT_WRCONFIG_INEN
// 		                                | ((mask & 0xffff0000) >> 16));
// 		break;

// 	case GPIO_DIRECTION_OUT:
// 		hri_port_set_DIR_reg(PORT_IOBUS, port, mask);
// 		hri_port_write_WRCONFIG_reg(PORT, port, PORT_WRCONFIG_WRPINCFG | (mask & 0xffff));
// 		hri_port_write_WRCONFIG_reg(
// 		    PORT, port, PORT_WRCONFIG_HWSEL | PORT_WRCONFIG_WRPINCFG | ((mask & 0xffff0000) >> 16));
// 		break;

// 	default:
// 		ASSERT(false);
// 	}
// }


// /**
//  * \brief Get input levels on all port pins
//  */
// static inline uint32_t _gpio_get_level(const enum gpio_port port)
// {
// 	uint32_t tmp;

// 	CRITICAL_SECTION_ENTER();

// 	uint32_t dir_tmp = hri_port_read_DIR_reg(PORT_IOBUS, port);

// 	tmp = hri_port_read_IN_reg(PORT, port) & ~dir_tmp;
// 	tmp |= hri_port_read_OUT_reg(PORT_IOBUS, port) & dir_tmp;

// 	CRITICAL_SECTION_LEAVE();

// 	return tmp;
// }
