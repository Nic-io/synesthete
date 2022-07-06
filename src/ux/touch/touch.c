/*
 * Copyright (c) 2021 Nicolas Blazevic <nicolas@ecliptic.fr>
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "touch.h"

static xyPos pressedPos;

void touch_init(void)
{
	adc_init();
	gpios_init();
}

void touch_read(void)
{
	int xval, yval;

	gpio_disable_touchpin(ypos);
	gpio_disable_touchpin(yneg);
	gpio_set_touchpin(xpos, 1);
	gpio_set_touchpin(xneg, 0);
	yval = adc_get_touch_axis(y);
	pressedPos.rawy = yval;
	gpio_disable_touchpin(xpos);
	gpio_disable_touchpin(xneg);
	gpio_set_touchpin(ypos, 1);
	gpio_set_touchpin(yneg, 0);
	xval = adc_get_touch_axis(x);

	pressedPos.x = 320 - (xval - 500) / 9.5f;
	pressedPos.y = (yval - 680) / 12.4f;

	if (pressedPos.y < 0) {
		pressedPos.y = 0;
	}
	if (pressedPos.y > 240) {
		pressedPos.y = 240;
	}
	if (pressedPos.x < 0) {
		pressedPos.x = 0;
	}
	if (pressedPos.x > 320) {
		pressedPos.x = 320;
	}
}

xyPos touch_get(void)
{
	return pressedPos;
}
