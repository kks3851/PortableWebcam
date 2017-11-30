/*
 * camera.c
 *
 * Created: 2/7/2017 12:38:08 AM
 *  Author: Tom
 */ 

#include "camera.h"


volatile uint32_t g_ul_vsync_flag = false;



void vsync_handler(uint32_t ul_id, uint32_t ul_mask)
{
	unused(ul_id);
	unused(ul_mask);
	g_ul_vsync_flag = true;	
}

void init_vsync_interrupts(void)
{
	/* Initialize PIO interrupt handler, see PIO definition in conf_board.h
	**/
	pio_handler_set(OV_VSYNC_PIO, OV_VSYNC_ID, OV_VSYNC_MASK,
			OV_VSYNC_TYPE, vsync_handler);

	/* Enable PIO controller IRQs */
	NVIC_EnableIRQ((IRQn_Type)OV_VSYNC_ID); 
}

void pio_capture_init(Pio *p_pio, uint32_t ul_id)
{
	/* Enable periphral clock */
	pmc_enable_periph_clk(ul_id);

	/* Disable pio capture */
	p_pio->PIO_PCMR &= ~((uint32_t)PIO_PCMR_PCEN);

	/* Disable rxbuff interrupt */
	p_pio->PIO_PCIDR |= PIO_PCIDR_RXBUFF;

	/* 32bit width*/
	p_pio->PIO_PCMR &= ~((uint32_t)PIO_PCMR_DSIZE_Msk);
	p_pio->PIO_PCMR |= PIO_PCMR_DSIZE_WORD;

	/* Only HSYNC and VSYNC enabled */
	p_pio->PIO_PCMR &= ~((uint32_t)PIO_PCMR_ALWYS);
	p_pio->PIO_PCMR &= ~((uint32_t)PIO_PCMR_HALFS);


// 	/* Samples only data with even index */
// 	p_pio->PIO_PCMR |= PIO_PCMR_HALFS;
// 	p_pio->PIO_PCMR &= ~((uint32_t)PIO_PCMR_FRSTS);
	
}

uint8_t pio_capture_to_buffer(Pio *p_pio, uint8_t *uc_buf ,uint32_t ul_size)
{
	/* Check if the first PDC bank is free */
	if ((p_pio->PIO_RCR == 0) && (p_pio->PIO_RNCR == 0)) {
		p_pio->PIO_RPR = (uint32_t)uc_buf;
		p_pio->PIO_RCR = ul_size;
		p_pio->PIO_PTCR = PIO_PTCR_RXTEN;
		return 1;
		} else if (p_pio->PIO_RNCR == 0) {
		p_pio->PIO_RNPR = (uint32_t)uc_buf;
		p_pio->PIO_RNCR = ul_size;
		return 1;
		} else {
		return 0;
	}
}

void init_camera(void)
{ 
	init_vsync_interrupts();
    configure_twi();
	/* Init PCK1 to work at 24 Mhz */
	/* 96/4=24 Mhz */
	PMC->PMC_PCK[1] = (PMC_PCK_PRES_CLK_4 | PMC_PCK_CSS_PLLA_CLK);
	PMC->PMC_SCER = PMC_SCER_PCK1;
	while (!(PMC->PMC_SCSR & PMC_SCSR_PCK1)) {
	}
	delay_ms(3000);
	configure_camera();
	pio_capture_init(OV_DATA_BUS_PIO ,OV_DATA_BUS_ID);
	/* Wait 3 seconds to let the image sensor to adapt to environment */
	delay_ms(3000);
}

void configure_twi(void)
{
	twi_options_t opt;
	/* Enable TWI peripheral */
	pmc_enable_periph_clk(ID_BOARD_TWI);

	/* Init TWI peripheral */
	opt.master_clk = sysclk_get_cpu_hz();
	opt.speed      = TWI_CLK;
	twi_master_init(BOARD_TWI, &opt);

	/* Configure TWI interrupts */
	NVIC_DisableIRQ(BOARD_TWI_IRQn);
	NVIC_ClearPendingIRQ(BOARD_TWI_IRQn);
	NVIC_SetPriority(BOARD_TWI_IRQn, 0);
	NVIC_EnableIRQ(BOARD_TWI_IRQn);
}

void configure_camera(void)
{
	
	/* ov2640 Initialization 
	// First, make sure reg 0xFF=1  */
	const uint8_t cont_reg_val = 1;
	twi_packet_t init_packet = {
		.addr         = 0xFF,                      // TWI slave memory address data
		.addr_length  = 1,                         // TWI slave memory address data size
		.chip         = OV_I2C_SENSOR_ADDRESS,     // TWI slave bus address
		.buffer       = &cont_reg_val,             // transfer data destination buffer
		.length       = 1                          // transfer data size (bytes)
	};
	ov_write_reg(BOARD_TWI, &init_packet);
	while (ov_init(BOARD_TWI) == 1) {
	}
	
	/* ov2640 configuration */
	ov_configure(BOARD_TWI, JPEG_INIT);
	ov_configure(BOARD_TWI, YUV422);
	
	ov_configure(BOARD_TWI, JPEG);
	ov_configure(BOARD_TWI, JPEG_640x480);
	//ov_configure_finish(BOARD_TWI);
}


uint8_t start_capture(void)
{   /* clearing the image buffer */

	//for(int ii=0; ii<array_size; ii++) image_buf[ii] = 0;
	
	uint8_t im_error;
	/* Enable vsync interrupt*/
	pio_enable_interrupt(OV_VSYNC_PIO, OV_VSYNC_MASK);

	/* Capture acquisition will start on rising edge of Vsync signal.
	 * So wait g_vsync_flag = 1 before start process
	 */
	while (!g_ul_vsync_flag) {
	}

	/* Disable vsync interrupt*/
	pio_disable_interrupt(OV_VSYNC_PIO, OV_VSYNC_MASK);

	/* Enable pio capture*/
	pio_capture_enable(OV_DATA_BUS_PIO);

	
	im_error = pio_capture_to_buffer(OV_DATA_BUS_PIO, image_buf,(array_size)>>2);

	/* Wait end of capture*/
	while (!((OV_DATA_BUS_PIO->PIO_PCISR & PIO_PCIMR_RXBUFF) ==
			PIO_PCIMR_RXBUFF)) {
	}

	/* Disable pio capture*/
	pio_capture_disable(OV_DATA_BUS_PIO);

	/* Reset vsync flag*/
	g_ul_vsync_flag = false;
	
	return im_error;
}

uint8_t find_image_len(void)
{
	uint8_t len_found = false;
	
	for( uint32_t i = 0; i< array_size; i++)
	{
	if ((image_buf[i] == 255)&& (image_buf[i+1] == 216))//&& (image_buf[i+2] = 0xD)&& (image_buf[i+3] = 0x9))
		{	im_start = i;
			break;
		}
	}
	
	for( uint32_t j = im_start; j< array_size; j++)
	{
	if ((image_buf[j] == 255)&& (image_buf[j+1] == 217))//&& (image_buf[i+2] = 0xD)&& (image_buf[i+3] = 0x9))
		{	im_length = j+2 - im_start;
			len_found = true;
			break;
		}
	}
	return len_found;
	
} 