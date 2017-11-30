#include <asf.h>
#include "wifi.h"
#include "camera.h"
#include "timer_interface.h"
#include "ov2640.h"
#include "board.h"
#include "conf_board.h"
#include "conf_clock.h"

int main (void)
{
	sysclk_init();
	board_init();
	ioport_init();
	wdt_disable(WDT);
    pmc_enable_pllack(7, 0x1, 1); /* PLLA work at 96 Mhz */
	configure_usart_wifi();
	wifi_web_setup_flag=false;
	configure_wifi_comm_pin();
	configure_wifi_web_setup_pin();
	configure_tc();
	ioport_set_pin_dir(USART0_RTS_IDX,IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(USART0_RTS_IDX,false);
	ioport_set_pin_level(OV_RESET,false);
	delay_ms(1);
	ioport_set_pin_level(OV_RESET,true);
	init_camera();
	uint8_t find_len = false;
	uint8_t cap = false;

	/* Reset Wifi and wait for network */
	ioport_set_pin_level(WIFI_RESET, false);
	delay_ms(100);
	ioport_set_pin_level(WIFI_RESET, true);
	
	
	while (!ioport_get_pin_level(NETWORK)){}
	//write_wifi_command("set system.cmd.prompt_enabled off\r\n", 1);
		
	
	//write_wifi_command("set system.cmd.echo off\r\nh\r", 1);
	
	
	
	while(1)
	{	
		
		while (!ioport_get_pin_level(NETWORK)){}
		while(!stream_flag){
		write_wifi_command("poll all\r\n", 1); 
		
		delay_ms(500);
		}
		stream_flag = false;
	    cap = start_capture();
	
		while(!cap){}
		
		find_len = find_image_len();
		cap = false;

		while(!find_len) {}

		write_image_to_file();
		find_len = false;

		write_wifi_command("stream_write 0 1\r\n ", 1);	
	}
}

