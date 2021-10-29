/*
 * Copyright (c) 2021 Nicolas Blazevic <nicolas@ecliptic.fr>
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "touch.h"

static xyPos pressedPos;

void touch_init(void){
    adc_init();
    gpios_init();
}

void touch_read(void){
    int xval, yval;
    
    touch_gpioDisable(ypos);
    touch_gpioDisable(yneg);
    touch_gpioSet(xpos, 1);
    touch_gpioSet(xneg, 0);
    yval = touchADC_get(y);
    
    touch_gpioDisable(xpos);
    touch_gpioDisable(xneg);
    touch_gpioSet(ypos, 1);
    touch_gpioSet(yneg, 0);
    xval = touchADC_get(x);

    pressedPos.x=320-(xval-500)/9.5f;
    pressedPos.y=(yval-680)/12.4f;
    
    if(pressedPos.y < 0){
        pressedPos.y = 0;
    }
    if(pressedPos.y > 240){
        pressedPos.y = 240;
    }
    if(pressedPos.x < 0){
        pressedPos.x = 0;
    }
    if(pressedPos.x >320){
        pressedPos.x = 320;
    }
}

xyPos touch_get(void){
    return pressedPos;
}