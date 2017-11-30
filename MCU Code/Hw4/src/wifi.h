/*
 * wifi.h
 *
 * Created: 2/4/2017 6:42:00 PM
 *  Author: Karan
 */ 



#ifndef WIFI_H_
#define WIFI_H_

#include "asf.h"
 #include "string.h"
#include "camera.h"
#include "timer_interface.h"


#define ALL_INTERRUPT_MASK  0xffffffff
#define MAX_INPUT_WIFI		10000

void configure_usart_wifi(void);
void process_IncomingByte_wifi(uint8_t inByte);
void wifi_command_response_handler(uint32_t ul_id, uint32_t ul_mask);
void process_data_wifi(void);
void configure_wifi_comm_pin(void);
void wifi_web_setup_handler(uint32_t ul_id, uint32_t ul_mask);
void configure_wifi_web_setup_pin(void);
void write_wifi_command(char* comm, uint8_t cnt);
void write_image_to_file(void);
void wait(void);

volatile uint32_t received_byte_wifi;
volatile uint8_t input_line_wifi[MAX_INPUT_WIFI];
volatile uint32_t input_pos_wifi;
volatile uint32_t wifi_web_setup_flag;
volatile uint32_t process_flag;
volatile uint32_t stream_flag;

#endif /* WIFI_H_ */