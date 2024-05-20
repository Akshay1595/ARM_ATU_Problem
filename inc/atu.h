#ifndef ATU_H
#define ATU_H

#include <stdint.h>
#include <stddef.h>

/* Enum to hold API result */
typedef enum
{
    ATU_SUCCESS,
    ATU_FAILURE
} ATU_RESULT;

/* Few MACROS needed */
#define ATU_CHAN_ENABLED        (1U)
#define ATU_CHAN_DISBLED        (0U)
#define ATU_NUM_OF_CHANNELS     (10U)

/**
 * @brief   Structure to hold registers together
 * @note    Assumption here is registers are placed in consecutive mem locations
 *          If not, we would have added offset or changed design.
 */
typedef struct ATU_Channel
{
    uint32_t u32_startAddr;     /* 32-bit start address for channel */
    uint32_t u32_endAddr;       /* 32-bit end   address for channel */
    uint32_t u64_startAddr_L;   /* 64-bit start address for channel LSB */
    uint32_t u64_startAddr_M;   /* 64-bit start address for channel MSB */
    uint32_t u64_endAddr_L;     /* 64-bit end   address for channel LSB */
    uint32_t u64_endAddr_M;     /* 64-bit end   address for channel MSB */
    uint32_t attr_enDis:1;      /* Attributes Channel Enabled/Disabled */
} atu_channel_reg_t;

/* Global APIs */
extern ATU_RESULT atu_write_channel(uint32_t u32_address, uint32_t value);
extern ATU_RESULT atu_init_channel(uint32_t channel_num, const atu_channel_reg_t * const channel_data);
extern ATU_RESULT atu_read_channel(uint32_t u32_address, uint32_t* const value);

#endif /* ATU_H */