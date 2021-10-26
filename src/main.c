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
#include "touch.h"

#define STACK_SIZE 1024
#define GUI_PRIO 6
#define TABLE_PRIO 5
K_THREAD_STACK_DEFINE(gui_stack_area, STACK_SIZE);
K_THREAD_STACK_DEFINE(table_stack_area, STACK_SIZE);
k_tid_t my_tid;
k_tid_t my_tid2;

int32_t tune_table[320] = { 0xFFFFFFFF };
int valueIn;

xyPos current;

void gui_thread(void *p1, void *p2, void *p3){
	while (1){
		current = touch_get();
		gui_draw_point(current.x, current.y);
		k_msleep(1);
	}
}

void update_table(void *p1, void *p2, void *p3){
	while (1){
		touch_read();
		k_msleep(1);
	}
}

void main(void)
{
	console_init();
	gui_init();
	touch_init();
		
	struct k_thread guiThread;

	my_tid = k_thread_create(&guiThread, gui_stack_area,
                            K_THREAD_STACK_SIZEOF(gui_stack_area),
                            gui_thread,
                            &my_tid2, NULL, NULL,
                            GUI_PRIO, 0, K_NO_WAIT);
	
	
	struct k_thread tableThread;

	my_tid2 = k_thread_create(&tableThread, table_stack_area,
                            K_THREAD_STACK_SIZEOF(table_stack_area),
                            update_table,
                            &my_tid, NULL, NULL,
                            TABLE_PRIO, 0, K_NO_WAIT);
	while (1)
	{
		k_msleep(100);
	}
}
