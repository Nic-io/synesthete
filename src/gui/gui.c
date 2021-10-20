/*
 * Copyright (c) 2021 Nicolas Blazevic <nicolas@ecliptic.fr>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "gui.h"

static const struct device *display_dev;
static struct display_buffer_descriptor buf_desc;
static struct display_capabilities capabilities;
static uint8_t *buf;
LOG_MODULE_REGISTER(synesthete, LOG_LEVEL_INF);

int gui_init(void)
{
	size_t x;
	size_t y;
	size_t rect_w;
	size_t rect_h;
	size_t h_step;
	size_t scale;
	size_t buf_size = 0;

	display_dev = device_get_binding(DISPLAY_DEV_NAME);

	if (display_dev == NULL) {
		LOG_ERR("Device %s not found. Aborting.",
			DISPLAY_DEV_NAME);
		return 1;
	}

	display_get_capabilities(display_dev, &capabilities);

	int bufthickness = 1;
	buf_size = capabilities.x_resolution*bufthickness*3;

	buf = k_malloc(buf_size);	
	if (buf == NULL) {
		LOG_ERR("Could not allocate memory. Aborting sample.");
		return 1;
	}

	display_blanking_off(display_dev);

	buf_desc.buf_size = buf_size;
	buf_desc.pitch = capabilities.x_resolution;
	buf_desc.width = capabilities.x_resolution;
	buf_desc.height = bufthickness;

	(void)memset(buf, 0xFF, buf_size);

	for(int k=0; k<capabilities.y_resolution; k++){
		display_write(display_dev, 0, k, &buf_desc, buf);
	}
	
	return 0;
}

void gui_draw_wave(int32_t *wave_array){
	LOG_INF("enter drawWave\n");
	for(int k=0; k<capabilities.y_resolution; k++){
	
		for (size_t idx = 0; idx < buf_desc.buf_size; idx += 3) {
			*(buf + idx + 0) = *(uint32_t*)(wave_array+k);
			*(buf + idx + 1) = *(uint32_t*)(wave_array+k) >> 8;
			*(buf + idx + 2) = *(uint32_t*)(wave_array+k) >> 16;
		}		
		display_write(display_dev, 0, k, &buf_desc, buf);
	}    
}
