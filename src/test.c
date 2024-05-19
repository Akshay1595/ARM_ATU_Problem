#include <stdio.h>
#include <stdint.h>
#include "..\inc\atu.h"
#include "..\inc\test.h"

#define BUFF1_SIZE      (16U)
#define BUFF2_SIZE      (8U)

test_result test1(void)
{
    uint32_t buff1[BUFF1_SIZE]  = {0u}; /* 1000 - 1015 */
    uint32_t data;

    atu_channel_reg_t channel_data = {
        .attr_enDis         = ATU_CHAN_ENABLED,
        .u32_startAddr      = 1000,
        .u32_endAddr        = (1000 + (BUFF1_SIZE - 1U)),
        .u64_startAddr_L    = (uint32_t)buff1,
        .u64_startAddr_M    = 0U,
        .u64_endAddr_L      = (uint32_t)(&buff1[BUFF1_SIZE - 1U]),
        .u64_endAddr_M      = 0U
    };

    if (ATU_SUCCESS != atu_init_channel(0, &channel_data))
    {
        printf ("Initialization failed \n");
        return TEST_FAILED;
    }

    if (ATU_SUCCESS == atu_write_channel(1000U, 12U))
    {
        if (ATU_SUCCESS != atu_read_channel(1000U, &data))
        {
            return TEST_FAILED;
        }
        printf("data = %d\n", data);
    }

    return TEST_PASSED;
}

test_result test2(void)
{
    uint32_t buff2[BUFF2_SIZE]  = {0u}; /* 2000 - 2007 */
    uint32_t data;

    atu_channel_reg_t channel_data2 = {
        .attr_enDis         = ATU_CHAN_ENABLED,
        .u32_startAddr      = 2000,
        .u32_endAddr        = 2007,
        .u64_startAddr_L    = (uint32_t)buff2,
        .u64_startAddr_M    = 0U,
        .u64_endAddr_L      = (uint32_t)(&buff2[BUFF2_SIZE - 1U]),
        .u64_endAddr_M      = 0U
    };

    if (ATU_SUCCESS != atu_init_channel(1, &channel_data2))
    {
        printf ("Initialization failed \n");
        return TEST_FAILED;
    }

    if (ATU_SUCCESS == atu_write_channel(2000U, 13U))
    {
        if (ATU_SUCCESS != atu_read_channel(2000U, &data))
        {
            return TEST_FAILED;
        }
        printf("data = %d\n", data);
    }

    return TEST_PASSED;
}