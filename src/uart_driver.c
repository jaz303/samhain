#include "samhain/uart_driver.h"
#include "samhain/sercom.h"

#include <string.h>

#define RX_IDLE 0
#define RX_BUSY 1

#define TX_IDLE 0
#define TX_BUSY 1

void samh_uart_driver_get_default_config(samh_uart_driver_config_t *cfg) {
	memset(cfg, 0, sizeof(samh_uart_driver_config_t));
}

samh_status_t samh_uart_driver_init(samh_uart_driver_t *drv, samh_uart_driver_config_t *cfg) {
	Sercom *hw = cfg->hw;

	if (cfg->rx_pad > 3) {
		return SAMH_ERR_CONFIG;
	}

	// There are other valid combinations and factors to consider when
	// supporting flow control and synchronous modes. We'll add support
	// for flow control later. Synchronous support is out of scope as
	// this is specifically a UART driver.
	int txpo;
	switch (cfg->tx_pad) {
		case 0: txpo = 0; break;
		case 2: txpo = 1; break;
		default:
			return SAMH_ERR_CONFIG;
	}

	drv->hw = hw;
	drv->irq = samh_sercom_get_irq(hw);
	drv->rx_handler = NULL;
	drv->tx_handler = NULL;
	drv->tx_state = 0;

	NVIC_DisableIRQ(drv->irq);
	NVIC_ClearPendingIRQ(drv->irq);
	
	hw->USART.CTRLA.reg =
		SERCOM_USART_CTRLA_DORD // LSB first
		| SERCOM_USART_CTRLA_RXPO(cfg->rx_pad)
		| SERCOM_USART_CTRLA_TXPO(txpo)
		| SERCOM_USART_CTRLA_SAMPR(0x0) // 16x over-sampling, arithmetic baud gen
		| SERCOM_USART_CTRLA_RUNSTDBY 
		| SERCOM_USART_CTRLA_MODE_USART_INT_CLK;

	hw->USART.CTRLB.reg =
		SERCOM_USART_CTRLB_CHSIZE(0) // 8 bit
		| SERCOM_USART_CTRLB_TXEN
		| SERCOM_USART_CTRLB_RXEN;
	
	hw->USART.BAUD.reg = cfg->brr;
	
	hw->USART.INTENSET.bit.ERROR = 1;
	hw->USART.INTENSET.bit.RXC = 1;

	while (hw->USART.SYNCBUSY.bit.ENABLE);
	hw->USART.CTRLA.bit.ENABLE = 1;
	while (hw->USART.SYNCBUSY.bit.ENABLE);

	NVIC_EnableIRQ(drv->irq);

	return SAMH_OK;
}

samh_status_t samh_uart_driver_read(samh_uart_driver_t *drv, uint8_t *buffer, int length) {
	if (drv->rx_state != RX_IDLE) {
		return SAMH_ERR_BUSY;
	}

	if (length <= 0) {
		return SAMH_ERR_LENGTH;
	}

	drv->rx_buffer = buffer;
	drv->rx_p = 0;
	drv->rx_len = length;
	drv->rx_state = RX_BUSY;
	
	return SAMH_OK;
}

samh_status_t samh_uart_driver_write(samh_uart_driver_t *drv, uint8_t *buffer, int length) {
	if (drv->tx_state != TX_IDLE) {
		return SAMH_ERR_BUSY;
	}

	if (length <= 0) {
		return SAMH_ERR_LENGTH;
	}

	drv->tx_buffer = buffer;
	drv->tx_p = 1;
	drv->tx_len = length;
	drv->tx_state = TX_BUSY;

	drv->hw->USART.DATA.reg = buffer[0];
	drv->hw->USART.INTENSET.bit.DRE = 1;

	return SAMH_OK;
}

void samh_uart_driver_set_rx_handler(samh_uart_driver_t *drv, samh_uart_driver_rx_handler handler) {
	drv->rx_handler = handler;
}

void samh_uart_driver_set_tx_handler(samh_uart_driver_t *drv, samh_uart_driver_tx_handler handler) {
	drv->tx_handler = handler;
}

void samh_uart_driver_enable_irq(samh_uart_driver_t *drv) {
	NVIC_EnableIRQ(drv->irq);
}

void samh_uart_driver_disable_irq(samh_uart_driver_t *drv) {
	NVIC_DisableIRQ(drv->irq);
}

void samh_uart_driver_irq(samh_uart_driver_t *drv) {
	Sercom *hw = drv->hw;

	// TODO: need to handle errors
	if (hw->USART.INTFLAG.reg & SERCOM_USART_INTFLAG_ERROR) {
		hw->USART.INTFLAG.reg = SERCOM_USART_INTFLAG_ERROR;
	}

	if (hw->USART.INTFLAG.reg & SERCOM_USART_INTFLAG_DRE) {
		if (drv->tx_p < drv->tx_len) {
			hw->USART.DATA.reg = drv->tx_buffer[drv->tx_p++];
		} else {
			hw->USART.INTENCLR.reg = SERCOM_USART_INTENCLR_DRE;
			drv->tx_state = TX_IDLE;
			if (drv->tx_handler) {
				drv->tx_handler(drv, drv->tx_buffer, drv->tx_len);
			}
		}
	}
	
	if (hw->USART.INTFLAG.reg & SERCOM_USART_INTFLAG_RXC) {
		uint8_t b = hw->USART.DATA.reg;
		if (drv->rx_state == RX_BUSY) {
			drv->rx_buffer[drv->rx_p++] = b;
			if (drv->rx_p == drv->rx_len) {
				drv->rx_state = RX_IDLE;
				if (drv->rx_handler) {
					drv->rx_handler(drv, drv->rx_buffer, drv->rx_len);
				}
			}
		}
	}
}