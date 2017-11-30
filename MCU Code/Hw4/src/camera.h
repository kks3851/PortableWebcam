/*
 * camera.h
 *
 * Created: 2/7/2017 12:38:27 AM
 *  Author: Tom
 */ 

#include "asf.h"
#include "ov2640.h"
#ifndef CAMERA_H_
#define CAMERA_H_



#define TWI_CLK     (400000UL)
#define array_size   100000


volatile uint32_t g_ul_vsync_flag;

volatile uint8_t image_buf[array_size];
volatile uint32_t im_length;
volatile uint32_t im_start;




void vsync_handler(uint32_t ul_id, uint32_t ul_mask);

void configure_twi(void);

void init_vsync_interrupts(void);

void pio_capture_init(Pio *p_pio, uint32_t ul_id);

uint8_t pio_capture_to_buffer(Pio *p_pio, uint8_t *uc_bu, uint32_t ul_size);

void init_camera(void);


void configure_camera(void);

uint8_t start_capture(void);

uint8_t find_image_len(void);


#endif /* CAMERA_H_ */