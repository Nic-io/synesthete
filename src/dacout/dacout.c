/*
 * Copyright (c) 2021 Nicolas Blazevic <nicolas@ecliptic.fr>
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "dacout.h"

LOG_MODULE_REGISTER(Synesthete_dacout, LOG_LEVEL_INF);
 
 /*Device tree definition of DMA 1*/
#define DACOUT DT_DMAS_CTLR_BY_NAME(DT_NODELABEL(dac1), dacout)

/*Device tree definition of DAC */
#define ZEPHYR_USER_NODE DT_PATH(zephyr_user)

#if (DT_NODE_HAS_PROP(ZEPHYR_USER_NODE, dac) && \
	DT_NODE_HAS_PROP(ZEPHYR_USER_NODE, dac_channel_id) && \
	DT_NODE_HAS_PROP(ZEPHYR_USER_NODE, dac_resolution))
#define DAC_NODE DT_PHANDLE(ZEPHYR_USER_NODE, dac)
#define DAC_CHANNEL_ID DT_PROP(ZEPHYR_USER_NODE, dac_channel_id)
#define DAC_RESOLUTION DT_PROP(ZEPHYR_USER_NODE, dac_resolution)
#else
#error "Unsupported board: see README and check /zephyr,user node"
#endif

static TIM_HandleTypeDef htim2;
static const struct device *dac_dev = DEVICE_DT_GET(DAC_NODE);
const struct device *dacdma;

void * dmadaccall(const struct device *dev, void *user_data, uint32_t channel, int status){
    if (status != 0){
        LOG_ERR("DMACallBK Error");
    }
}

int dacout_init(uint32_t *buffer, uint16_t size){
    int ret = 0;

    dacout_timer_init();

    // DAC initialization block 
    static const struct dac_channel_cfg dac_ch_cfg = {
	    .channel_id  = DAC_CHANNEL_ID,
	    .resolution  = DAC_RESOLUTION
    };
    if (!device_is_ready(dac_dev)) {
		LOG_ERR("DAC device %s is not ready\n", dac_dev->name);
		return 1;
	}

	ret = dac_channel_setup(dac_dev, &dac_ch_cfg);
	
    if (ret != 0) {
		LOG_ERR("Setting up of DAC channel failed with code %d\n", ret);
		return 1;
	} 

    //DMA initialization block
    struct dma_block_config dacdmablk_cfg = {
        .source_addr_adj = DMA_ADDR_ADJ_INCREMENT, 
    #warning "change the way to get the address of DHR"
        .dest_address = 0x40007408,
        .source_reload_en = 1,
        .dest_reload_en = 1,
        .dest_addr_adj = DMA_ADDR_ADJ_NO_CHANGE
    };

    struct dma_config dacdma_cfg = {
        .dma_slot = 7,
        .channel_direction = MEMORY_TO_PERIPHERAL,
        .channel_priority = 1, 
        .dest_chaining_en = 0,
        .source_chaining_en = 1,
        .source_data_size = 2,
        .dest_data_size = 2,
        .source_burst_length =1,
        .dest_burst_length =1,
        .head_block = &dacdmablk_cfg,
        .complete_callback_en = 0,
        .error_callback_en = 1,
        .dma_callback = dmadaccall
    };

    dacdma = DEVICE_DT_GET(DACOUT);
    dacdmablk_cfg.source_address = buffer;
    dacdmablk_cfg.block_size = size*2;
    ret = dma_config(dacdma, 5, &dacdma_cfg);
    
    if(ret != 0){
        LOG_ERR("DMA Config Error");
    } 

    ret = dma_start(dacdma, 5);
    
    if(ret != 0){
        LOG_ERR("DMA start Error");
    } 

    HAL_TIM_Base_Start(&htim2);
    return ret;
}

void dacout_timer_init(void)
{
    __HAL_RCC_TIM2_CLK_ENABLE();

    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    TIM_MasterConfigTypeDef sMasterConfig = {0};

    htim2.Instance = TIM2;
    htim2.Init.Prescaler = 84-1;
    htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim2.Init.Period = 20000-1;
    htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
    {
        LOG_ERR("HAL_TIM_Base_Init Error");
    }
    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
    {
        LOG_ERR("HAL_TIM_ConfigClockSource Error");
    }
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
    {
       LOG_ERR("HAL_TIMEx_MasterConfigSynchronization Error");
    }
}