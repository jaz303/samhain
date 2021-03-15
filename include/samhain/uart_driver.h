#ifndef SAMHAIN_UART_DRIVER_
#define SAMHAIN_UART_DRIVER_

#include <sam.h>
#include <stdint.h>

#include "samhain/status.h"

typedef struct samh_uart_driver samh_uart_driver_t;

typedef void (*samh_uart_driver_rx_handler)(samh_uart_driver_t *drv, uint8_t *buffer, int len);
typedef void (*samh_uart_driver_tx_handler)(samh_uart_driver_t *drv, uint8_t *buffer, int len);

typedef struct samh_uart_driver_config {
	Sercom 		*hw;		/** Sercom instance */
	uint16_t	brr;		/** Baud rate register value */
	uint8_t		rx_pad;		/** Receive pad. Valid: 0, 1, 2, 3 */
	uint8_t		tx_pad;		/** Transmit pad. Valid: 0, 2 */
} samh_uart_driver_config_t;

struct samh_uart_driver {
	Sercom 		*hw;
	IRQn_Type	irq;

	samh_uart_driver_rx_handler rx_handler;
	samh_uart_driver_tx_handler tx_handler;

	int 	rx_state;
	uint8_t *rx_buffer;
	int 	rx_p;
	int 	rx_len;

	int 	tx_state;
	uint8_t	*tx_buffer;
	int 	tx_p;
	int 	tx_len;
};

/**
 * Initialise default configuration.
 *
 * The following fields must always be set by the user:
 *   - hw
 *   - brr
 *   - rx_pad
 *   - tx_pad
 */
void samh_uart_driver_get_default_config(samh_uart_driver_config_t *cfg);

samh_status_t samh_uart_driver_init(samh_uart_driver_t *drv, samh_uart_driver_config_t *cfg);

samh_status_t samh_uart_driver_read(samh_uart_driver_t *drv, uint8_t *buffer, int length);
samh_status_t samh_uart_driver_write(samh_uart_driver_t *drv, uint8_t *buffer, int length);

void samh_uart_driver_set_rx_handler(samh_uart_driver_t *drv, samh_uart_driver_rx_handler handler);
void samh_uart_driver_set_tx_handler(samh_uart_driver_t *drv, samh_uart_driver_tx_handler handler);

/**
 * Enable the driver's interrupt.
 */
void samh_uart_driver_enable_irq(samh_uart_driver_t *drv);

/**
 * Disable the driver's interrupt.
 */
void samh_uart_driver_disable_irq(samh_uart_driver_t *drv);

void samh_uart_driver_irq(samh_uart_driver_t *drv);

#endif