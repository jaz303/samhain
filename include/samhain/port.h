#ifndef SAMHAIN_PORT_H_
#define SAMHAIN_PORT_H_

#include <stdint.h>

/**
 * Indicates no special function should be assigned to a pin.
 * Pass this value to samh_port_set_gpio_function() to
 * disable the pin multiplexer.
 */
#define SAMH_PIN_FUNCTION_OFF	0xFFFFFFFF

/** GPIO/pin pull mode */
enum {
	SAMH_PULL_NONE = 0,
	SAMH_PULL_UP,
	SAMH_PULL_DOWN
};

/** GPIO/pin direction */
enum {
	SAMH_DIR_INPUT = 0,
	SAMH_DIR_OUTPUT
};

/**
 * GPIO/pin level
 *
 * We guarantee that low logic will always by falsy and that
 * high logic will always be truthy.
 */
enum {
	SAMH_LOW = 0,
	SAMH_HIGH
};

/**
 * Create a reference to a give port/pin
 */
#define SAMH_GPIO(port, pin)	(((port)<<5)|(pin))

/**
 * Extract the port number from a GPIO ref
 * 0 => Port A, 1 => Port B, etc.
 */
#define SAMH_PORT(gpio)			((gpio)>>5)

/**
 * Extract the pin number from a GPIO ref
 */
#define SAMH_PIN(gpio)			((gpio)&31)

void samh_port_set_gpio_direction(uint8_t gpio, int direction);
int samh_port_get_gpio_level(uint8_t gpio);
void samh_port_set_gpio_level(uint8_t gpio, int level);
void samh_port_toggle_gpio_level(uint8_t gpio);
void samh_port_set_gpio_pull_mode(uint8_t gpio, int pull);
void samh_port_set_gpio_function(uint8_t gpio, int function);
void samh_port_set_gpio_input_enabled(uint8_t gpio, int enabled);
void samh_port_set_gpio_strong_drive_enabled(uint8_t gpio, int enabled);

uint32_t samh_port_get_port_levels(uint8_t port, uint32_t mask);
void samh_port_set_port_levels(uint8_t port, uint32_t mask, uint32_t values);
void samh_port_toggle_port_levels(uint8_t port, uint32_t mask);

#endif