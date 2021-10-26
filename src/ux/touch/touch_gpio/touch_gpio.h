/*
 * Copyright (c) 2021 Nicolas Blazevic <nicolas@ecliptic.fr>
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef __SYNESTHETE_TOUCH_GPIO_H_
#define __SYNESTHETE_TOUCH_GPIO_H_

#include <zephyr.h>
#include <sys/printk.h>
#include <devicetree.h>
#include <drivers/gpio.h>
#include <logging/log.h>

typedef enum {
    xpos,
    xneg,
    ypos,
    yneg
}touchPin;

int gpios_init(void);
int touch_gpioSet(touchPin hPin, int value);


#endif