/*
 * Copyright (c) 2021 Nicolas Blazevic <nicolas@ecliptic.fr>
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <zephyr.h>
#include <sys/printk.h>
#include <drivers/dac.h>

#include "wavetab.h"

LOG_MODULE_REGISTER(wavetab, LOG_LEVEL_INF);

static uint16_t aquisition_table[TABLE_RESOLUTION];
static int updated_samples[TABLE_RESOLUTION];

void wave_aquire(void){
   
    if(touch_get().x > 0){
        int place;
        k_msleep(5);
        place = (touch_get().x/TABLE_STEPSIZE);
        if(place<= TABLE_RESOLUTION){
                
            LOG_INF("Tab[%d]: %d", place, touch_get().y);
            
            aquisition_table[place] = touch_get().y;
            updated_samples[place] = 1;
        }
    }
}

void wave_draw(void){
    gui_draw_column(aquisition_table, updated_samples, TABLE_RESOLUTION);
}

#define ZEPHYR_USER_NODE DT_PATH(zephyr_user)

#if (DT_NODE_HAS_PROP(ZEPHYR_USER_NODE, dac) && \
	DT_NODE_HAS_PROP(ZEPHYR_USER_NODE, dac_channel_id) && \
	DT_NODE_HAS_PROP(ZEPHYR_USER_NODE, dac_resolution))
#define DAC_NODE DT_PHANDLE(ZEPHYR_USER_NODE, dac)
#define DAC_CHANNEL_ID DT_PROP(ZEPHYR_USER_NODE, dac_channel_id)
#define DAC_RESOLUTION DT_PROP(ZEPHYR_USER_NODE, dac_resolution)
#else
#error "Unsupported board: see README and check /zephyr,user node"
#define DAC_NODE DT_INVALID_NODE
#define DAC_CHANNEL_ID 0
#define DAC_RESOLUTION 0
#endif

static const struct device *dac_dev = DEVICE_DT_GET(DAC_NODE);

static const struct dac_channel_cfg dac_ch_cfg = {
	.channel_id  = DAC_CHANNEL_ID,
	.resolution  = DAC_RESOLUTION
};

void sound_init(void)
{
	if (!device_is_ready(dac_dev)) {
		printk("DAC device %s is not ready\n", dac_dev->name);
		return;
	}

	int ret = dac_channel_setup(dac_dev, &dac_ch_cfg);

	if (ret != 0) {
		printk("Setting up of DAC channel failed with code %d\n", ret);
		return;
	}
}

void sound(void){

	/* Number of valid DAC values, e.g. 4096 for 12-bit DAC */
	const int dac_values = 1U << DAC_RESOLUTION;
	/*
	 * 1 msec sleep leads to about 4 sec signal period for 12-bit
	 * DACs. For DACs with lower resolution, sleep time needs to
	 * be increased.
	 * Make sure to sleep at least 1 msec even for future 16-bit
	 * DACs (lowering signal frequency).
	 */
	const int sleep_time = 4096 / dac_values > 0 ?
		4096 / dac_values : 1;
	for (int i = TABLE_RESOLUTION; i > 0; i--) {
		int ret = dac_write_value(dac_dev, DAC_CHANNEL_ID, (aquisition_table[i-1]*4096/240));
		if (ret != 0) {
			printk("dac_write_value() failed with code %d\n", ret);
			return;
		}
		k_sleep(K_USEC(50));
	}
}

 