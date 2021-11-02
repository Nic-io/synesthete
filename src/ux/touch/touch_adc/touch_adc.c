/*
 * Copyright (c) 2020 Libre Solar Technologies GmbH
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "touch_adc.h"

#if !DT_NODE_EXISTS(DT_PATH(zephyr_user)) || \
	!DT_NODE_HAS_PROP(DT_PATH(zephyr_user), io_channels)
#error "No suitable devicetree overlay specified"
#endif

#define ADC_NODE		DT_PHANDLE(DT_PATH(zephyr_user), io_channels)

/* Common settings supported by most ADCs */
#define ADC_RESOLUTION		12
#define ADC_GAIN		ADC_GAIN_1
#define ADC_REFERENCE		ADC_REF_INTERNAL
#define ADC_ACQUISITION_TIME	ADC_ACQ_TIME_DEFAULT

static int16_t sample_buffer;

struct adc_channel_cfg channel_cfg = {
	.gain = ADC_GAIN,
	.reference = ADC_REFERENCE,
	.acquisition_time = ADC_ACQUISITION_TIME,
	/* channel ID will be overwritten below */
	.channel_id = 1,
	.differential = 0
};

struct adc_sequence sequence = {
	/* individual channels will be added below */
	.channels    = 0,
	.buffer      = &sample_buffer,
	/* buffer size in bytes, not number of samples */
	.buffer_size = sizeof(sample_buffer),
	.resolution  = ADC_RESOLUTION,
};

const struct device *dev_adc;
int32_t adc_vref;

void adc_init(void){
	dev_adc = DEVICE_DT_GET(ADC_NODE);

	if (!device_is_ready(dev_adc)) {
		printk("ADC device not found\n");
		return;
	}
	adc_channel_setup(dev_adc, &channel_cfg);
	adc_vref = adc_ref_internal(dev_adc);
}

int touchADC_get(touchAxis axis){

	channel_cfg.channel_id = axis;
	sequence.channels = BIT(axis);

	k_msleep(10);
	adc_channel_setup(dev_adc, &channel_cfg);
	int err = adc_read(dev_adc, &sequence);
	
	if (err != 0) {
		printk("ADC reading failed with error %d.\n", err);
		return err;
	}
			
	int32_t raw_value = sample_buffer;
	if (adc_vref > 0) {
		/*
		* Convert raw reading to millivolts if driver
		* supports reading of ADC reference voltage
		*/
		int32_t mv_value = raw_value;
		adc_raw_to_millivolts(adc_vref, ADC_GAIN,
		ADC_RESOLUTION, &mv_value);
		printk(" = %d mV  ", mv_value);
	}
	return raw_value;
}
