/*
 * Copyright (c) 2021 Nicolas Blazevic <nicolas@ecliptic.fr>
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "dacout.h"

LOG_MODULE_REGISTER(dacout, LOG_LEVEL_INF);
 
#define DACOUT DT_DMAS_CTLR_BY_NAME(DT_NODELABEL(dac1), dacout)

const struct device *dacdma;


struct dma_block_config dacdmablk_cfg = {
    .source_addr_adj = DMA_ADDR_ADJ_INCREMENT, 
    .dest_address = DT_REG_ADDR(DT_NODELABEL(dac1)),
    .source_reload_en = 1,
    .dest_reload_en = 1,
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
    
    int ret;
    
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

}