/*
 * Copyright (c) 2021 Nicolas Blazevic <nicolas@ecliptic.fr>
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef __SYNESTHETE_DACOUT_H_
#define __SYNESTHETE_DACOUT_H_

#include <zephyr.h>
#include <sys/printk.h>
#include <devicetree.h>
#include <logging/log.h>
#include <drivers/dma.h>
#include <drivers/dac.h>
#include <soc.h>

int dacout_init(uint32_t *buffer, uint16_t size);
void dacout_timer_init(void);
static void * dmadaccall(const struct device *dev, void *user_data, uint32_t channel, int status);

#endif