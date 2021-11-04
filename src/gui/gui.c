/*
 * Copyright (c) 2021 Nicolas Blazevic <nicolas@ecliptic.fr>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "gui.h"

K_MUTEX_DEFINE(buf_mutex);

static const struct device *display_dev;
static struct display_buffer_descriptor buf_desc;
static struct display_capabilities capabilities;
static uint8_t *buf;


LOG_MODULE_REGISTER(gui, LOG_LEVEL_INF);

int gui_init(void)
{
	size_t buf_size = 0;

	display_dev = device_get_binding(DISPLAY_DEV_NAME);

	if (display_dev == NULL) {
		LOG_ERR("Device %s not found. Aborting.",
			DISPLAY_DEV_NAME);
		return 1;
	}

	display_get_capabilities(display_dev, &capabilities);

	buf_size = capabilities.x_resolution*3;

	buf = k_malloc(buf_size);	
	if (buf == NULL) {
		LOG_ERR("Could not allocate memory. Aborting sample.");
		return 1;
	}

	display_blanking_off(display_dev);
	buf_desc.buf_size = buf_size;
	buf_desc.pitch = capabilities.x_resolution;
	buf_desc.width = capabilities.x_resolution;
	buf_desc.height = 1;

	if (k_mutex_lock(&buf_mutex, K_MSEC(100)) == 0) {
    	/* mutex successfully locked */
		(void)memset(buf, 0x00, buf_size);
		k_mutex_unlock(&buf_mutex);
	}
	
	if (k_mutex_lock(&buf_mutex, K_MSEC(100)) == 0) {
    	/* mutex successfully locked */
		for(int k=0; k<capabilities.y_resolution; k++){
			display_write(display_dev, 0, k, &buf_desc, buf);
		}
		k_mutex_unlock(&buf_mutex);
	}
		
	return 0;
}

void fill_buffer(uint32_t *color){
	for (size_t idx = 0; idx < buf_desc.buf_size; idx += 3) {
		*(buf + idx + 0) =*(uint32_t*)color >> 16;
		*(buf + idx + 1) =*(uint32_t*)color >> 8;
		*(buf + idx + 2) =*(uint32_t*)color >> 0;
	}
}

void gui_draw_column(uint32_t *table, int *newflag, int size){

	for (size_t i = 0; i < size; i++)
	{
		//Only update changed pixels
		if(*(newflag + i) == 1){
			//reset flag
			*(newflag + i) = 0;
			//fill column with black 
			uint32_t color = 0;

			buf_desc.height = capabilities.y_resolution;
			buf_desc.width = capabilities.x_resolution / size;
			buf_desc.buf_size = buf_desc.height * buf_desc.width * 3;
			buf_desc.pitch = buf_desc.width;
			
			fill_buffer(&color);
			display_write(display_dev, buf_desc.width*i, 0, &buf_desc, buf);

			//resize buffer do display value over newly cleared column
			
			buf_desc.buf_size = buf_desc.height * buf_desc.width * 3;

			if(*(table + i) > (capabilities.y_resolution/2)){
				color = 0x3F9F16;
				buf_desc.height = *(table + i)-capabilities.y_resolution/2;
				buf_desc.buf_size = (buf_desc.height * buf_desc.width) * 3;
				fill_buffer(&color);
				display_write(display_dev,  buf_desc.width*i, capabilities.y_resolution/2, &buf_desc, buf);
			}

			if(*(table + i) <= (capabilities.y_resolution/2)){
				color = 0x1F90F0;
				buf_desc.buf_size = (buf_desc.height * buf_desc.width) * 3;
				buf_desc.height =capabilities.y_resolution/2 - *(table + i);
				fill_buffer(&color);
				display_write(display_dev,  buf_desc.width*i, (capabilities.y_resolution/2)-buf_desc.height, &buf_desc, buf);
			}	
		}
	}
}

void gui_draw_point(int x, int y){

	//color changing
	static uint32_t color = 0x000000F; 
	color +=0x010306;

	buf_desc.height = 4;
	buf_desc.width = 4;
	buf_desc.buf_size = buf_desc.height * buf_desc.width * 3;
	buf_desc.pitch = buf_desc.width;

	fill_buffer(&color);	
	
	if(x > 0 && x < capabilities.x_resolution && y > 0 && y < capabilities.y_resolution){
		display_write(display_dev, x, y, &buf_desc, buf);		
	} 
}
