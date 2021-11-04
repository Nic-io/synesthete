/*
 * Copyright (c) 2021 Nicolas Blazevic <nicolas@ecliptic.fr>
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "dacout.h"

LOG_MODULE_REGISTER(dacout, LOG_LEVEL_INF);
static TIM_HandleTypeDef htim2;
 
#define DACOUT DT_DMAS_CTLR_BY_NAME(DT_NODELABEL(dac1), dacout)

const struct device *dacdma;


struct dma_block_config dacdmablk_cfg = {
    .source_addr_adj = DMA_ADDR_ADJ_INCREMENT, 
    .dest_address = 0x40007408,//DT_REG_ADDR(DT_NODELABEL(dac1)),
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
    .head_block = &dacdmablk_cfg
};

int dacout_init(uint32_t *buffer, uint16_t size){
    
    int ret = 0;
    
    dacdma = DEVICE_DT_GET(DACOUT);
    dacdmablk_cfg.source_address = buffer;
    dacdmablk_cfg.block_size = size;
    
    ret = dma_config(dacdma, 5, &dacdma_cfg);
    if(ret != 0){
        LOG_ERR("DMA Config Error");
    } 

    MX_TIM2_Init();
    HAL_TIM_Base_Start(&htim2);

    ret = dma_start(dacdma, 5);
    if(ret != 0){
        LOG_ERR("DMA start Error");
    } 
    return ret;
}

static void MX_TIM2_Init(void)
{

    __HAL_RCC_TIM2_CLK_ENABLE();
    /* USER CODE BEGIN TIM2_Init 0 */

    /* USER CODE END TIM2_Init 0 */

    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    TIM_MasterConfigTypeDef sMasterConfig = {0};

    /* USER CODE BEGIN TIM2_Init 1 */

    /* USER CODE END TIM2_Init 1 */
    htim2.Instance = TIM2;
    htim2.Init.Prescaler = 84-1;
    htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim2.Init.Period = 1000-1;
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
    /* USER CODE BEGIN TIM2_Init 2 */

    /* USER CODE END TIM2_Init 2 */

}
