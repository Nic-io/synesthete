/*
 * Copyright (c) 2019 Jan Van Winkel <jan.van_winkel@dxplore.eu>
 *
 * Based on ST7789V sample:
 * Copyright (c) 2019 Marc Reilly
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <logging/log.h>
LOG_MODULE_REGISTER(sample, LOG_LEVEL_INF);

#include <zephyr.h>
#include <device.h>
#include <drivers/display.h>
#include <console/console.h>
#include <sys/printk.h>


#if DT_NODE_HAS_STATUS(DT_INST(0, ilitek_ili9340), okay)
#define DISPLAY_DEV_NAME DT_LABEL(DT_INST(0, ilitek_ili9340))
#endif

#if DT_NODE_HAS_STATUS(DT_INST(0, solomon_ssd1306fb), okay)
#define DISPLAY_DEV_NAME DT_LABEL(DT_INST(0, solomon_ssd1306fb))
#endif

#if DT_NODE_HAS_STATUS(DT_INST(0, solomon_ssd16xxfb), okay)
#define DISPLAY_DEV_NAME DT_LABEL(DT_INST(0, solomon_ssd16xxfb))
#endif

#if DT_NODE_HAS_STATUS(DT_INST(0, sitronix_st7789v), okay)
#define DISPLAY_DEV_NAME DT_LABEL(DT_INST(0, sitronix_st7789v))
#endif

#if DT_NODE_HAS_STATUS(DT_INST(0, sitronix_st7735r), okay)
#define DISPLAY_DEV_NAME DT_LABEL(DT_INST(0, sitronix_st7735r))
#endif

#if DT_NODE_HAS_STATUS(DT_INST(0, fsl_imx6sx_lcdif), okay)
#define DISPLAY_DEV_NAME DT_LABEL(DT_INST(0, fsl_imx6sx_lcdif))
#endif

#ifdef CONFIG_SDL_DISPLAY_DEV_NAME
#define DISPLAY_DEV_NAME CONFIG_SDL_DISPLAY_DEV_NAME
#endif

#ifdef CONFIG_DUMMY_DISPLAY_DEV_NAME
#define DISPLAY_DEV_NAME CONFIG_DUMMY_DISPLAY_DEV_NAME
#endif
#ifdef CONFIG_ARCH_POSIX
#include "posix_board_if.h"
#endif

#ifdef CONFIG_ARCH_POSIX
#define RETURN_FROM_MAIN(exit_code) posix_exit_main(exit_code)
#else
#define RETURN_FROM_MAIN(exit_code) return
#endif

enum corner {
	TOP_LEFT,
	TOP_RIGHT,
	BOTTOM_RIGHT,
	BOTTOM_LEFT
};

typedef void (*fill_buffer)(enum corner corner, uint8_t grey, uint8_t *buf,
			    size_t buf_size);


#ifdef CONFIG_ARCH_POSIX
static void posix_exit_main(int exit_code)
{
#if CONFIG_TEST
	if (exit_code == 0) {
		LOG_INF("PROJECT EXECUTION SUCCESSFUL");
	} else {
		LOG_INF("PROJECT EXECUTION FAILED");
	}
#endif
	posix_exit(exit_code);
}
#endif

static void fill_buffer_rgb888(enum corner corner, uint8_t grey, uint8_t *buf,
			       size_t buf_size)
{
	uint32_t color = 0;

	switch (corner) {
	case TOP_LEFT:
		color = 0x00FF0000u;
		break;
	case TOP_RIGHT:
		color = 0x0000FF00u;
		break;
	case BOTTOM_RIGHT:
		color = 0x000000FFu;
		break;
	case BOTTOM_LEFT:
		color = grey << 16 | grey << 8 | grey;
		break;
	}

	for (size_t idx = 0; idx < buf_size; idx += 3) {
		*(buf + idx + 0) = color >> 16;
		*(buf + idx + 1) = color >> 8;
		*(buf + idx + 2) = color >> 0;
	}
}

void main(void)
{
	size_t x;
	size_t y;
	size_t rect_w;
	size_t rect_h;
	size_t h_step;
	size_t scale;
	size_t grey_count;
	uint8_t *buf;
	int32_t grey_scale_sleep;
	const struct device *display_dev;
	struct display_capabilities capabilities;
	struct display_buffer_descriptor buf_desc;
	size_t buf_size = 0;
	fill_buffer fill_buffer_fnc = NULL;

	console_init();

	LOG_INF("Display sample for %s", DISPLAY_DEV_NAME);

	display_dev = device_get_binding(DISPLAY_DEV_NAME);

	if (display_dev == NULL) {
		LOG_ERR("Device %s not found. Aborting sample.",
			DISPLAY_DEV_NAME);
		RETURN_FROM_MAIN(1);
	}

	display_get_capabilities(display_dev, &capabilities);

	int bufthickness = 1;
	buf_size = capabilities.x_resolution*bufthickness*3;

	
	buf = k_malloc(buf_size);

	if (buf == NULL) {
		LOG_ERR("Could not allocate memory. Aborting sample.");
		RETURN_FROM_MAIN(1);
	}

	display_blanking_off(display_dev);


	buf_desc.buf_size = buf_size;
	buf_desc.pitch = capabilities.x_resolution;
	buf_desc.width = capabilities.x_resolution;
	buf_desc.height = bufthickness;

	char input;
	int colorcode;
	void * memptr = 0x20000000;
	(void)memset(buf, 0xFF, buf_size);

	for(int k=0; k<240; k++){
		display_write(display_dev, 0, k, &buf_desc, buf);
	}
	
	while (1) {
		
		//input = console_getchar();


		
		for(int k=0; k<240; k+=3){
			
			for (size_t idx = 0; idx < buf_size; idx += 3) {
				*(buf + idx + 0) = *(uint32_t*)(memptr + idx);
				*(buf + idx + 1) = *(uint32_t*)(memptr + idx) >> 8;
				*(buf + idx + 2) = *(uint32_t*)(memptr + idx) >> 16;
			}
			for(int j=0; j<3; j++){
				display_write(display_dev, 0, k+j, &buf_desc, buf);
			}
			memptr+=buf_size;
		}						
		memptr = 0x20000000;
#if CONFIG_TEST
		if (grey_count >= 1024) {
			break;
		}
#endif
	}

	RETURN_FROM_MAIN(0);
}
