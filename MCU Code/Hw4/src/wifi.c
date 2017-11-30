/*
 * wifi.c
 *
 * Created: 2/4/2017 6:41:44 PM
 *  Author: Karan
 */ 

 #include "wifi.h"
 #include "camera.h"


 volatile uint32_t received_byte_wifi = 0;
 volatile uint32_t input_pos_wifi = 0;
 volatile uint32_t wifi_web_setup_flag = false;
 volatile uint32_t process_flag = false;
 volatile uint32_t stream_flag = false;
 void WIFI_USART_Handler(void)
 {
	 uint32_t ul_status;

	 /* Read USART status. */
	 ul_status = usart_get_status(BOARD_USART);

	 /* Receive buffer is full. */
	 if (ul_status & US_CSR_RXBUFF) 
	 {
		 usart_read(BOARD_USART, &received_byte_wifi);
		 process_IncomingByte_wifi((uint8_t)received_byte_wifi);
	  } 
}

void process_IncomingByte_wifi(uint8_t inByte)
{
	input_line_wifi[input_pos_wifi++] = inByte;

}

void wifi_command_response_handler(uint32_t ul_id, uint32_t ul_mask)
{
	unused(ul_id);
	unused(ul_mask);
	
	process_data_wifi();
	for (int jj = 0; jj < MAX_INPUT_WIFI; jj++) input_line_wifi[jj] = 0;
	input_pos_wifi = 0;
}

void process_data_wifi(void)
{ 
	WIFI_USART_Handler();
	if ((strstr(input_line_wifi, "File created")) || (strstr(input_line_wifi, "File deleted")) || (strstr(input_line_wifi, "Unknown command"))|| (strstr(input_line_wifi, "Command failed"))|| (strstr(input_line_wifi, "File not found")) || (strstr(input_line_wifi, "Success")) || (strstr(input_line_wifi, "In progress")) || (strstr(input_line_wifi, "None")) || (strstr(input_line_wifi, "Set OK")) || (strstr(input_line_wifi, "ZENTRI")) || (strstr(input_line_wifi, "0,0")))
	{
	process_flag = true;
	}
	if (strstr(input_line_wifi,"0,0"))
	{
		stream_flag = true;
	}
		
}

void configure_wifi_comm_pin(void)
{
	/* Configure PIO clock. */
	pmc_enable_periph_clk(WIFI_COMM_PIN_ID);

	/* Initialize PIO interrupt handler, see PIO definition in conf_board.h
	**/
	pio_handler_set(WIFI_COMM_PIN_PIO, WIFI_COMM_PIN_ID, WIFI_COMM_PIN_MASK,
			WIFI_COMM_PIN_ATTR, wifi_command_response_handler);

	/* Enable PIO controller IRQs. */
	NVIC_EnableIRQ((IRQn_Type)WIFI_COMM_PIN_ID);

	/* Enable PIO interrupt lines. */
	pio_enable_interrupt(WIFI_COMM_PIN_PIO, WIFI_COMM_PIN_MASK);
}

 void configure_usart_wifi(void)
{
	static uint32_t ul_sysclk;
	const sam_usart_opt_t usart_console_settings = {
		BOARD_USART_BAUDRATE,
		US_MR_CHRL_8_BIT,
		US_MR_PAR_NO,
		US_MR_NBSTOP_1_BIT,
		US_MR_CHMODE_NORMAL,
		/* This field is only used in IrDA mode. */
		0
	};

	/* Get peripheral clock. */
	ul_sysclk = sysclk_get_peripheral_hz();

	/* Enable peripheral clock. */
	sysclk_enable_peripheral_clock(BOARD_ID_USART);

	/* Configure USART. */
	usart_init_hw_handshaking(BOARD_USART, &usart_console_settings, ul_sysclk);

	/* Disable all the interrupts. */
	usart_disable_interrupt(BOARD_USART, ALL_INTERRUPT_MASK);
	
	/* Enable TX & RX function. */
	usart_enable_tx(BOARD_USART);
	usart_enable_rx(BOARD_USART);

	usart_enable_interrupt(BOARD_USART, US_IER_RXRDY);

	/* Configure and enable interrupt of USART. */
	NVIC_EnableIRQ(USART_IRQn);
}

void wifi_web_setup_handler(uint32_t ul_id, uint32_t ul_mask)
{
	unused(ul_id);
	unused(ul_mask);

	while(wifi_web_setup_flag){
		usart_write_line(BOARD_USART,"setup web\r\n");
		delay_ms(1000);
		while (!ioport_get_pin_level(NETWORK)){}
		wifi_web_setup_flag = false;
	}
	wifi_web_setup_flag = true;
	
}

void configure_wifi_web_setup_pin(void)
{
	/* Configure PIO clock. */
	pmc_enable_periph_clk(WIFI_WEB_SETUP_PIN_ID);

	/* Adjust PIO debounce filter using a 10 Hz filter. */
	pio_set_debounce_filter(WIFI_WEB_SETUP_PIN_PIO, WIFI_WEB_SETUP_PIN_MASK, 10);

	/* Initialize PIO interrupt handler, see PIO definition in conf_board.h
	**/
	pio_handler_set(WIFI_WEB_SETUP_PIN_PIO, WIFI_WEB_SETUP_PIN_ID, WIFI_WEB_SETUP_PIN_MASK,
			WIFI_WEB_SETUP_PIN_ATTR, wifi_web_setup_handler);

	/* Enable PIO controller IRQs. */
	NVIC_EnableIRQ((IRQn_Type)WIFI_WEB_SETUP_PIN_ID);

	/* Enable PIO interrupt lines. */
	pio_enable_interrupt(WIFI_WEB_SETUP_PIN_PIO, WIFI_WEB_SETUP_PIN_MASK);

}

void write_wifi_command(char* comm, uint8_t cnt)
{   
	usart_write_line(BOARD_USART, comm);
	
	counts = 0;
	tc_start(TC0, 0);
	if(counts < cnt)
	{	
		while(!process_flag){}
		process_flag = false;
		return;
		}

	return;
}

void write_image_to_file(void)
{

	usart_write_line(BOARD_USART, "fde img.jpg\r\n");
	delay_ms(10);
	uint8_t file_create_string[100];
	sprintf(file_create_string, "fcr img.jpg %d\r\n", im_length); 
	usart_write_line(BOARD_USART, file_create_string);
	delay_ms(10);
	for (uint32_t jj=im_start;jj<(im_start + im_length);jj++) 
	{
	usart_putchar(BOARD_USART, image_buf[jj]);
	}  
	delay_ms(10);
	while(!process_flag){}
	process_flag = false;
 	
}

void wait(void){
	

	
	
}