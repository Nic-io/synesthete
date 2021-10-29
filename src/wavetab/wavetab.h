/*
 * Copyright (c) 2021 Nicolas Blazevic <nicolas@ecliptic.fr>
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef __SYNESTHETE_WAVETAB_H_
#define __SYNESTHETE_WAVETAB_H_

#include "touch.h"
#include "gui.h"

#define TABLE_SCREENSIZE 320
#define TABLE_RESOLUTION 50

#define TABLE_STEPSIZE (TABLE_SCREENSIZE / TABLE_RESOLUTION)

void wave_aquire(void);
void wave_draw(void);


#endif