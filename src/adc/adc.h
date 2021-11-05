/*
 * Copyright (c) 2021 Nicolas Blazevic <nicolas@ecliptic.fr>
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef __SYNESTHETE_TOUCH_ADC_H_
#define __SYNESTHETE_TOUCH_ADC_H_

#include <zephyr.h>
#include <sys/printk.h>
#include <devicetree.h>
#include <drivers/adc.h>
#include <logging/log.h>

typedef enum {
    y = 0,
    x
}touchAxis;

void adc_init(void);
int adc_get_touch_axis(touchAxis axis);

#endif