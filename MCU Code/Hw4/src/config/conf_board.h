/**
 * \file
 *
 * \brief User board configuration template
 *
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#ifndef CONF_BOARD_H
#define CONF_BOARD_H

/** Configure TWI0 pins (for OV2640  communications). */
#define CONF_BOARD_TWI0
/** Configure PCK0 pins (for OV2640  communications). */
#define CONF_BOARD_PCK0
/** Enable Com Port. */
#define CONF_BOARD_UART_CONSOLE

/* USART1 module is used in hardware handshaking mode. */
#define CONF_BOARD_USART_RXD
#define CONF_BOARD_USART_TXD
#define CONF_BOARD_USART_CTS
#define CONF_BOARD_USART_RTS


#define PINS_TWI0               PIN_TWI_TWD0, PIN_TWI_TWCK0
#define ID_BOARD_TWI			ID_TWI0
#define BOARD_TWI				TWI0
#define BOARD_TWI_IRQn			TWI0_IRQn

#define BOARD_ID_USART             ID_USART0
#define BOARD_USART                USART0

#define BOARD_USART_BAUDRATE       115200
#define WIFI_USART_Handler         USART0_Handler
#define USART_IRQn                 USART0_IRQn

/** USART0 pin RX */
#define PIN_USART0_RXD			  {PIO_PA5A_RXD0, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_USART0_RXD_IDX        (PIO_PA5_IDX)
#define PIN_USART0_RXD_FLAGS      (PIO_PERIPH_A | PIO_DEFAULT)
/** USART0 pin TX */
#define PIN_USART0_TXD            {PIO_PA6A_TXD0, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_USART0_TXD_IDX        (PIO_PA6_IDX)
#define PIN_USART0_TXD_FLAGS      (PIO_PERIPH_A | PIO_DEFAULT)
/** USART0 pin CTS */
#define PIN_USART0_CTS            {PIO_PA8A_CTS0, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_USART0_CTS_IDX        (PIO_PA8_IDX)
#define PIN_USART0_CTS_FLAGS      (PIO_PERIPH_A | PIO_DEFAULT)
/** USART0 pin RTS */
// #define PIN_USART0_RTS			  {PIO_PA7A_RTS0, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define USART0_RTS_IDX        PIO_PA7_IDX
/*#define PIN_USART0_RTS_FLAGS      (PIO_PERIPH_A | PIO_DEFAULT)*/


#define WIFI_COMM_PIN             {PIO_PB10, PIOB, ID_PIOB, PIO_INPUT, PIO_IT_RISE_EDGE}
#define WIFI_COMM_PIN_MASK          PIO_PB10
#define WIFI_COMM_PIN_PIO           PIOB
#define WIFI_COMM_PIN_ID            ID_PIOB
#define WIFI_COMM_PIN_TYPE          PIO_INPUT
#define WIFI_COMM_PIN_ATTR			PIO_IT_RISE_EDGE
#define GPIO_WIFI_COMM_PIN             (PIO_PB10_IDX)
#define GPIO_WIFI_COMM_PIN_FLAGS       (PIO_INPUT | PIO_IT_RISE_EDGE)

#define WIFI_WEB_SETUP_PIN        {PIO_PA22, PIOA, ID_PIOA, PIO_INPUT, PIO_PULLUP | PIO_DEBOUNCE | PIO_IT_RISE_EDGE}
#define WIFI_WEB_SETUP_PIN_MASK		PIO_PA22
#define WIFI_WEB_SETUP_PIN_PIO      PIOA
#define WIFI_WEB_SETUP_PIN_ID       ID_PIOA
#define WIFI_WEB_SETUP_PIN_TYPE     PIO_INPUT
#define WIFI_WEB_SETUP_PIN_ATTR     PIO_PULLUP | PIO_DEBOUNCE | PIO_IT_RISE_EDGE
#define GPIO_WIFI_WEB_SETUP         (PIO_PA22_IDX)
#define GPIO_WIFI_WEB_SETUP_FLAGS   (PIO_INPUT | PIO_PULLUP | PIO_DEBOUNCE | PIO_IT_RISE_EDGE)

/** WIFI Reset Pin */
#define WIFI_RESET    PIO_PB0_IDX
//#define WIFI_RESET_FLAGS   (PIO_PERIPH_A | PIO_DEFAULT)
#define OV_RESET    PIO_PA20_IDX
// #define PIN_USART0_RTS PIO_PA7_IDX	

/** Network Status */
#define NETWORK   (PIO_PB11_IDX)
#define NETWORK_FLAGS    (PIO_INPUT | PIO_IT_RISE_EDGE)
		

/******************************* PCK1 definition
 *********************************/
/** PCK1 */
#define PIN_PCK1                       (PIO_PA17_IDX)
#define PIN_PCK1_FLAGS                 (PIO_PERIPH_B | PIO_DEFAULT)

/******************************* TWI definition
 *********************************/
/** TWI0 data pin */
#define PIN_TWI_TWD0                   {PIO_PA3A_TWD0, PIOA, ID_PIOA, \
                                         PIO_PERIPH_A, PIO_DEFAULT}

/** TWI0 clock pin */
#define PIN_TWI_TWCK0                  {PIO_PA4A_TWCK0, PIOA, ID_PIOA,	\
                                         PIO_PERIPH_A, PIO_DEFAULT}

/** TWI0 Data pins definition */
#define TWI0_DATA_GPIO                 PIO_PA3_IDX
#define TWI0_DATA_FLAGS                (PIO_PERIPH_A | PIO_DEFAULT)
#define TWI0_DATA_MASK                 PIO_PA3
#define TWI0_DATA_PIO                  PIOA
#define TWI0_DATA_ID                   ID_PIOA
#define TWI0_DATA_TYPE                 PIO_PERIPH_A
#define TWI0_DATA_ATTR                 PIO_DEFAULT

/** TWI0 clock pins definition */
#define TWI0_CLK_GPIO                  PIO_PA4_IDX
#define TWI0_CLK_FLAGS                 (PIO_PERIPH_A | PIO_DEFAULT)
#define TWI0_CLK_MASK                  PIO_PA4
#define TWI0_CLK_PIO                   PIOA
#define TWI0_CLK_ID                    ID_PIOA
#define TWI0_CLK_TYPE                  PIO_PERIPH_A
#define TWI0_CLK_ATTR                  PIO_DEFAULT

/** TWI0 pins */
#define PINS_TWI0                      PIN_TWI_TWD0, PIN_TWI_TWCK0

#define ID_BOARD_TWI		               ID_TWI0
#define BOARD_TWI			                 TWI0
#define BOARD_TWI_IRQn		             TWI0_IRQn

/******************************* Image sensor definition
 *********************************/
 /* Image sensor board defines.
 // Image sensor Power pin.


#define PIN_OV_FSIN                    { PIO_PA23, PIOA, ID_PIOA, \
										PIO_OUTPUT_0, PIO_DEFAULT}
 

#define PIN_OV_RST                     { PIO_PA20, PIOA, ID_PIOA, \
                                         PIO_OUTPUT_1, PIO_DEFAULT}

										 */
/** HSYNC pin */
#define PIN_OV_HSYNC                   { PIO_PA16, PIOA, ID_PIOA, \
                                         PIO_INPUT, PIO_PULLUP | \
                                         PIO_IT_RISE_EDGE }

/** VSYNC pin */
#define PIN_OV_VSYNC                   { PIO_PA15, PIOA, ID_PIOA, \
                                         PIO_INPUT, PIO_PULLUP | \
                                         PIO_IT_RISE_EDGE }

/** OV_PCLK pin definition
#define OV_FSIN_GPIO                   PIO_PA23_IDX
#define OV_FSIN_FLAGS                  (PIO_OUTPUT_0 | PIO_DEFAULT)
#define OV_FSIN_MASK                   PIO_PA23
#define OV_FSIN_PIO                    PIOA
#define OV_FSIN_ID                     ID_PIOA
#define OV_FSIN_TYPE                   PIO_OUTPUT_0

 */


/** OV_RST pin definition */
#define OV_RST_GPIO                    PIO_PA22_IDX
#define OV_RST_FLAGS                   (PIO_OUTPUT_1 | PIO_DEFAULT)
#define OV_RST_MASK                    PIO_PA22
#define OV_RST_PIO                     PIOA
#define OV_RST_ID                      ID_PIOA
#define OV_RST_TYPE                    PIO_OUTPUT_1


/** OV_HSYNC pin definition */
#define OV_HSYNC_GPIO                  PIO_PA16_IDX
#define OV_HSYNC_FLAGS                 (PIO_PULLUP | PIO_IT_RISE_EDGE)
#define OV_HSYNC_MASK                  PIO_PA16
#define OV_HSYNC_PIO                   PIOA
#define OV_HSYNC_ID                    ID_PIOA
#define OV_HSYNC_TYPE                  PIO_PULLUP

/** OV_VSYNC pin definition */
#define OV_VSYNC_GPIO                  PIO_PA15_IDX
#define OV_VSYNC_FLAGS                 (PIO_PULLUP | PIO_IT_RISE_EDGE)
#define OV_VSYNC_MASK                  PIO_PA15
#define OV_VSYNC_PIO                   PIOA
#define OV_VSYNC_ID                    ID_PIOA
#define OV_VSYNC_TYPE                  PIO_PULLUP

/** OV Data Bus pins */
#define OV_DATA_BUS_D0                 PIO_PA24_IDX
#define OV_DATA_BUS_D1                 PIO_PA25_IDX
#define OV_DATA_BUS_D2                 PIO_PA26_IDX
#define OV_DATA_BUS_D3                 PIO_PA27_IDX
#define OV_DATA_BUS_D4                 PIO_PA28_IDX
#define OV_DATA_BUS_D5                 PIO_PA29_IDX
#define OV_DATA_BUS_D6                 PIO_PA30_IDX
#define OV_DATA_BUS_D7                 PIO_PA31_IDX
#define OV_DATA_BUS_FLAGS              (PIO_INPUT | PIO_PULLUP)
#define OV_DATA_BUS_MASK               (0xFF000000UL)
#define OV_DATA_BUS_PIO                PIOA
#define OV_DATA_BUS_ID                 ID_PIOA
#define OV_DATA_BUS_TYPE               PIO_INPUT
#define OV_DATA_BUS_ATTR               PIO_DEFAULT

/** List of Image sensor definitions. */
#define PINS_OV                        PIN_PCK1


/******************************* Parallel Capture definition
 *********************************/
/** Parallel Capture Mode Data Enable1 */
#define PIN_PIODCEN1                   PIO_PA15

/** Parallel Capture Mode Data Enable2 */
#define PIN_PIODCEN2                   PIO_PA16





#endif // CONF_BOARD_H
