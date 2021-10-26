/*
 * Copyright (c) 2021 Nicolas Blazevic <nicolas@ecliptic.fr>
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef __SYNESTHETE_GUI_H
#define __SYNESTHETE_GUI_H

#include <logging/log.h>
#include <zephyr.h>
#include <device.h>
#include <drivers/display.h>
#include <console/console.h>

#define DISPLAY_DEV_NAME DT_LABEL(DT_INST(0, ilitek_ili9340))

int gui_init();
void gui_draw_wave(int32_t *wave_array);

#endif