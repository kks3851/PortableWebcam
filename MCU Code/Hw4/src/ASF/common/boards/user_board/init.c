/**
 * \file
 *
 * \brief User board initialization template
 *
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#include <asf.h>
#include <board.h>
#include <conf_board.h>

void board_init(void)
{
	ioport_init();
	
	//ioport_set_pin_dir(TWI0_DATA_GPIO, IOPORT_DIR_OUTPUT);
	//ioport_set_pin_dir(TWI0_CLK_GPIO, IOPORT_DIR_OUTPUT);
	gpio_configure_pin(TWI0_DATA_GPIO, TWI0_DATA_FLAGS);
	gpio_configure_pin(TWI0_CLK_GPIO, TWI0_CLK_FLAGS);

	gpio_configure_pin(PIN_PCK1, PIN_PCK1_FLAGS);

	
	/* Configure Image sensor pins */
	//gpio_configure_pin(OV_RST_GPIO, OV_RST_FLAGS);
	//gpio_configure_pin(OV_FSIN_GPIO, OV_FSIN_FLAGS);
	gpio_configure_pin(OV_HSYNC_GPIO, OV_HSYNC_FLAGS);
	gpio_configure_pin(OV_VSYNC_GPIO, OV_VSYNC_FLAGS);
	gpio_configure_pin(OV_DATA_BUS_D0, OV_DATA_BUS_FLAGS);
	gpio_configure_pin(OV_DATA_BUS_D1, OV_DATA_BUS_FLAGS);
	gpio_configure_pin(OV_DATA_BUS_D2, OV_DATA_BUS_FLAGS);
	gpio_configure_pin(OV_DATA_BUS_D3, OV_DATA_BUS_FLAGS);
	gpio_configure_pin(OV_DATA_BUS_D4, OV_DATA_BUS_FLAGS);
	gpio_configure_pin(OV_DATA_BUS_D5, OV_DATA_BUS_FLAGS);
	gpio_configure_pin(OV_DATA_BUS_D6, OV_DATA_BUS_FLAGS);
	gpio_configure_pin(OV_DATA_BUS_D7, OV_DATA_BUS_FLAGS);

	ioport_set_pin_dir(GPIO_WIFI_COMM_PIN, IOPORT_DIR_INPUT);
	ioport_set_pin_dir(GPIO_WIFI_WEB_SETUP, IOPORT_DIR_INPUT);
	ioport_set_pin_dir(NETWORK, IOPORT_DIR_INPUT);
	ioport_set_pin_dir(WIFI_RESET, IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(OV_RESET, IOPORT_DIR_OUTPUT);

	gpio_configure_pin(GPIO_WIFI_WEB_SETUP , GPIO_WIFI_WEB_SETUP_FLAGS);
    gpio_configure_pin(GPIO_WIFI_COMM_PIN , GPIO_WIFI_COMM_PIN_FLAGS);
	//gpio_configure_pin(WIFI_RESET , WIFI_RESET_FLAGS);
	gpio_configure_pin(NETWORK , NETWORK_FLAGS);
	
	/* Configure USART RXD pin */
	gpio_configure_pin(PIN_USART0_RXD_IDX, PIN_USART0_RXD_FLAGS);
	


	/* Configure USART TXD pin */
	gpio_configure_pin(PIN_USART0_TXD_IDX, PIN_USART0_TXD_FLAGS);


	/* Configure USART CTS pin */
	gpio_configure_pin(PIN_USART0_CTS_IDX, PIN_USART0_CTS_FLAGS);



// 	/* Configure USART RTS pin */
// 	gpio_configure_pin(PIN_USART0_RTS_IDX, PIN_USART0_RTS_FLAGS);

	
}
