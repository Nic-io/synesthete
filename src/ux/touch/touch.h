/*
 * Copyright (c) 2021 Nicolas Blazevic <nicolas@ecliptic.fr>
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef __SYNESTHETE_TOUCH_H_
#define __SYNESTHETE_TOUCH_H_

#include "touch_adc.h"
#include "touch_gpio.h"

typedef struct{
    int x;
    int y;
}xyPos;

void touch_init();
void touch_read();
xyPos touch_get();

#endif
