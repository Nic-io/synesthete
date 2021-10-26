/*
 * Copyright (c) 2021 Nicolas Blazevic <nicolas@ecliptic.fr>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "touch_gpio.h"

//LOG_MODULE_REGISTER(touchgpio, LOG_LEVEL_INF);

/* The devicetree node identifier for the pins. */
#define TOUCHXPOS DT_PATH(touchpins, xpos)
#define TOUCHXNEG DT_PATH(touchpins, xgnd)
#define TOUCHYPOS DT_PATH(touchpins, ypos)
#define TOUCHYNEG DT_PATH(touchpins, ygnd)

#if DT_NODE_HAS_STATUS(TOUCHXPOS, okay) && \
    DT_NODE_HAS_STATUS(TOUCHXNEG, okay) && \
    DT_NODE_HAS_STATUS(TOUCHYPOS, okay) && \
    DT_NODE_HAS_STATUS(TOUCHYNEG, okay)

#define XPOS	DT_GPIO_LABEL(TOUCHXPOS, gpios)
#define PIN_X_P	DT_GPIO_PIN(TOUCHXPOS, gpios)
#define FLAGS_X_P	DT_GPIO_FLAGS(TOUCHXPOS, gpios)

#define XNEG	DT_GPIO_LABEL(TOUCHXNEG, gpios)
#define PIN_X_N	DT_GPIO_PIN(TOUCHXNEG, gpios)
#define FLAGS_X_N	DT_GPIO_FLAGS(TOUCHXNEG, gpios)

#define YPOS	DT_GPIO_LABEL(TOUCHYPOS, gpios)
#define PIN_Y_P	DT_GPIO_PIN(TOUCHYPOS, gpios)
#define FLAGS_Y_P	DT_GPIO_FLAGS(TOUCHYPOS, gpios)

#define YNEG	DT_GPIO_LABEL(TOUCHYNEG, gpios)
#define PIN_Y_N	DT_GPIO_PIN(TOUCHYNEG, gpios)
#define FLAGS_Y_N	DT_GPIO_FLAGS(TOUCHYNEG, gpios)

#else
#error "Unsupported board"
#endif

const struct device *devXpos;
const struct device *devXneg;
const struct device *devYpos;
const struct device *devYneg;

int gpios_init(void){

	devXpos = device_get_binding(XPOS);
    devXneg = device_get_binding(XNEG);
    devYpos = device_get_binding(YPOS);
    devYneg = device_get_binding(YNEG);
    if (devXneg == NULL || devXpos == NULL || devXneg == NULL || devYneg == NULL){
        //LOG_ERR("device initialization failed");
        return 1;
    }

	gpio_pin_set(devXneg, PIN_X_N, 0);
    gpio_pin_set(devYneg, PIN_Y_N, 0);

    return 0;
}

int touch_gpioSet(touchPin hPin, int value){
    int ret=0;
    switch(hPin){
        case xpos :
            gpio_pin_configure(devXpos, PIN_X_P, GPIO_OUTPUT_ACTIVE | FLAGS_X_P);
	        ret = gpio_pin_set(devXpos, PIN_X_P, value);
            break;
        case xneg :
            gpio_pin_configure(devXneg, PIN_X_N, GPIO_OUTPUT_ACTIVE | FLAGS_X_N);
	        ret = gpio_pin_set(devXneg, PIN_X_N, value);
            break;
        case ypos :
            gpio_pin_configure(devYpos, PIN_Y_P, GPIO_OUTPUT_ACTIVE | FLAGS_Y_P);
	        ret = gpio_pin_set(devYpos, PIN_Y_P, value);
            break;
        case yneg:
            gpio_pin_configure(devYneg, PIN_Y_N, GPIO_OUTPUT_ACTIVE | FLAGS_Y_N);
	        ret = gpio_pin_set(devYneg, PIN_Y_N, value);
            break;
    }
    return ret;
}

int touch_gpioDisable(touchPin tPin){
    switch (tPin){
        case xpos :
            gpio_pin_configure(devXpos, PIN_X_P, GPIO_DISCONNECTED);
        case xneg :
            gpio_pin_configure(devXneg, PIN_X_N, GPIO_DISCONNECTED);
        case ypos :
            gpio_pin_configure(devYpos, PIN_Y_P, GPIO_DISCONNECTED);
        case yneg :
            gpio_pin_configure(devYneg, PIN_Y_N, GPIO_DISCONNECTED);
    }
}
