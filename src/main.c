/*
 * Copyright (c) 2021 Nicolas Blazevic <nicolas@ecliptic.fr>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <logging/log.h>
LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

#include <zephyr.h>
#include <device.h>
#include <drivers/display.h>
#include <console/console.h>
#include <sys/printk.h>
#include "gui.h"


int32_t tune_table[320] = { 0xFFFFFFFF };
int valueIn;

void gui_thread(void *p1, void *p2, void *p3){
	while (1){
		gui_draw_wave(tune_table);
		k_sleep(K_MSEC(40));
	}
}

void update_table(void *p1, void *p2, void *p3){
	while (1){
		valueIn = console_getchar();
		printk("Acquired %d \n", valueIn);
		memset(tune_table, valueIn*40, 320*4);
	}
}

#define STACK_SIZE 1024
#define GUI_PRIO 3
#define TABLE_PRIO 1

K_THREAD_STACK_DEFINE(gui_stack_area, STACK_SIZE);
K_THREAD_STACK_DEFINE(table_stack_area, STACK_SIZE);

struct k_thread guiThread;
struct k_thread tableThread;

void main(void)
{
	console_init();
	gui_init();

	k_tid_t my_tid = k_thread_create(&guiThread, gui_stack_area,
                                 K_THREAD_STACK_SIZEOF(gui_stack_area),
                                 gui_thread,
                                 NULL, NULL, NULL,
                                 GUI_PRIO, 0, K_NO_WAIT);

	k_tid_t my_tid2 = k_thread_create(&tableThread, table_stack_area,
                                 K_THREAD_STACK_SIZEOF(table_stack_area),
                                 update_table,
                                 NULL, NULL, NULL,
                                 TABLE_PRIO, 0, K_NO_WAIT);
	while (1)
	{
		k_msleep(100);
	}
	
}
