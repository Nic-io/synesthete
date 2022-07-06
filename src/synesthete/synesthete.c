/*
 * Copyright (c) 2021 Nicolas Blazevic <nicolas@ecliptic.fr>
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <zephyr.h>
#include <sys/printk.h>
#include <drivers/dac.h>

#include "synesthete.h"
#include "dacout.h"

LOG_MODULE_REGISTER(Synesthete, LOG_LEVEL_INF);

static uint32_t aquisition_table[TABLE_RESOLUTION] = { 3700 };
static uint16_t sound_table[TABLE_RESOLUTION] = { 3700 };
static int updated_samples[TABLE_RESOLUTION] = { 0 };

void wave_aquire(void)
{
	touch_read();
	xyPos newWave = touch_get();
	if (newWave.x > 0 && newWave.rawy != 0) {
		int place;
		k_msleep(5);
		place = (newWave.x / TABLE_STEPSIZE);

		if (place < TABLE_RESOLUTION && updated_samples[place] == 0) {
			aquisition_table[place] = newWave.y;
			updated_samples[place] = 1;
			sound_table[TABLE_RESOLUTION - (place + 1)] =
				4096 - newWave.rawy;
			LOG_INF("soundtabab[%d]: %d", place, newWave.rawy);
		}
	}
}
void getfreq(void)
{
	dacout_change_freq(0);
}
void wave_draw(void)
{
	gui_draw_column(aquisition_table, updated_samples, TABLE_RESOLUTION);
}

void synesthete_init(void)
{
	gui_init();
	touch_init();
	dacout_init(sound_table, TABLE_RESOLUTION);
}
