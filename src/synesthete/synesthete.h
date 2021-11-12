/*
 * Copyright (c) 2021 Nicolas Blazevic <nicolas@ecliptic.fr>
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef __SYNESTHETE_WAVETAB_H_
#define __SYNESTHETE_WAVETAB_H_

#include "touch.h"
#include "gui.h"
#include "dacout.h"

#define TABLE_SCREENSIZE 320
#define TABLE_RESOLUTION 100

#define TABLE_STEPSIZE (TABLE_SCREENSIZE / TABLE_RESOLUTION)

void wave_aquire(void);
void wave_draw(void);
void synesthete_init(void);
void getfreq(void);
void sound(void);

#endif