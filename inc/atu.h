#ifndef ATU_H
#define ATU_H

#include <stdint.h>
#include <stddef.h>

typedef enum
{
    ATU_SUCCESS,
    ATU_FAILURE
} ATU_RESULT;

#define ATU_CHAN_ENABLED        (1U)
#define ATU_CHAN_DISBLED        (0U)
#define ATU_NUM_OF_CHANNELS     (10U)

typedef struct ATU_Channel
{
    uint32_t u32_startAddr;
    uint32_t u32_endAddr;
    uint32_t u64_startAddr_L;
    uint32_t u64_startAddr_M;
    uint32_t u64_endAddr_L;
    uint32_t u64_endAddr_M;
    uint32_t attr_enDis:1;
} atu_channel_reg_t;

extern ATU_RESULT atu_write_channel(uint32_t u32_address, uint32_t value);
extern ATU_RESULT atu_init_channel(uint32_t channel_num, const atu_channel_reg_t * const channel_data);
extern ATU_RESULT atu_read_channel(uint32_t u32_address, uint32_t* const value);

#endif /* ATU_H */