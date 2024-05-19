/**
 * @file atu.c
 * @author Akshay Godase
 * @brief ATU driver as described in https://github.com/Akshay1595/ARM_ATU_Problem/blob/main/README.md
 * @version 0.1
 * @date 2024-05-19
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "..\inc\atu.h"
/* ------------------------------------------------------------------------------------------------- */

/* Static functions */
static ATU_RESULT atu_get_channel_from_addr(uint32_t address, uint32_t * const channel_num);

/* ------------------------------------------------------------------------------------------------- */

/* Global Datas */
static volatile atu_channel_reg_t array_of_atu_channel_reg[ATU_NUM_OF_CHANNELS] = {0u};
static volatile const atu_channel_reg_t * const atu_reg_base_addr = array_of_atu_channel_reg;

/* ------------------------------------------------------------------------------------------------- */

/* Code Begins Static APIs first */

/**
 * @brief This is the Local function that extracts channel number from given 32-bit address.
 *        This function will search for 32-bit address in all channels addresses and returns
 *        the channel number.
 * 
 * @param address       32-bit address
 * @param channel_num   Channel number to fill in
 * @return ATU_RESULT   result of API SUCCESS if found else failure
 */
static ATU_RESULT atu_get_channel_from_addr(uint32_t address, uint32_t * const channel_num)
{
    ATU_RESULT eResult                          = ATU_FAILURE;
    uint32_t index                              = 0u;
    atu_channel_reg_t * intended_channel_addr   = NULL;

    /* Check if valid input parameters */
    if ((address != NULL) && (channel_num != NULL))
    {
        /* Check if address is a part of any channel addresses configured */
        for (index = 0U; index < ATU_NUM_OF_CHANNELS; index++)
        {
            intended_channel_addr = atu_reg_base_addr + index;
            if ((address <= intended_channel_addr->u32_endAddr) &&
                (address >= intended_channel_addr->u32_startAddr))
            {
                /* Address found, check if channel is enabled */
                if (intended_channel_addr->attr_enDis == ATU_CHAN_ENABLED)
                {
                    eResult = ATU_SUCCESS;
                    *channel_num = index;
                }
                break;
            }
        }
    }

    return eResult;
}

/* ------------------------------------------------------------------------------------------------- */

/* Global APIs */

/**
 * @brief This is the API used for Initialization of channel. This API will update registers for
 *        given channel with parameters passed.
 * 
 * @param channel_num   Channel index to be configured
 * @param channel_data  Channel data  to be configured for above channel
 * @return ATU_RESULT   Result of channel configuration SUCCESS if initialized otherwise failure
 */
ATU_RESULT atu_init_channel(uint32_t channel_num, const atu_channel_reg_t * const channel_data)
{
    ATU_RESULT eResult = ATU_SUCCESS;

    /* Check if valid input parameters have received */
    if ((channel_num < ATU_NUM_OF_CHANNELS) && (channel_data != NULL))
    {
        /* Update Valid data as received */
        atu_channel_reg_t * intended_channel_addr   = atu_reg_base_addr + channel_num;
        intended_channel_addr->attr_enDis           = channel_data->attr_enDis;
        intended_channel_addr->u32_startAddr        = channel_data->u32_startAddr;
        intended_channel_addr->u32_endAddr          = channel_data->u32_endAddr;
        intended_channel_addr->u64_startAddr_L      = channel_data->u64_startAddr_L;
        intended_channel_addr->u64_endAddr_L        = channel_data->u64_endAddr_L;
        intended_channel_addr->u64_startAddr_M      = channel_data->u64_startAddr_M;
        intended_channel_addr->u64_endAddr_M        = channel_data->u64_endAddr_M;
    }
    else
    {
        /* Invalid data hence mark failure */
        eResult = ATU_FAILURE;
    }

    return eResult;
}

/**
 * @brief These are the APIs deisgned to Implement logic of ATU hardware 
 *        to write to 32-bit address maped to 64-bit address.
 * @note  This API is just for demo purpose. It is not the actual Implementation.
 *        It will just demo how it will work. Actually CPU will issue write to address.
 *        But here we are trying to show with a model, how it will work.
 * 
 * @param u32_address   32-bit address to write to
 * @param value         value to be written
 * @return ATU_RESULT   Result of API SUCCESS if value written Succefully otherwise failure.
 */
ATU_RESULT atu_write_channel(uint32_t u32_address, uint32_t value)
{
    uint32_t channel_num                        = 0u;
    uint64_t address_to_write                   = 0u;
    atu_channel_reg_t * intended_channel_addr   = atu_reg_base_addr;
    uint32_t addr_offset                        = 0u;
    ATU_RESULT eResult                          = ATU_FAILURE;

    /* Check if valid input parameters have received */
    if (ATU_SUCCESS == atu_get_channel_from_addr(u32_address, &channel_num))
    {
        /* Get intended address to write by calculating offset */
        intended_channel_addr  += channel_num;
        addr_offset             = u32_address - intended_channel_addr->u32_startAddr;
        address_to_write        = (intended_channel_addr->u64_startAddr_L) | (intended_channel_addr->u64_startAddr_M << 32U);
        address_to_write       += addr_offset;
        *((uint64_t*)address_to_write) = value;
        eResult                 = ATU_SUCCESS;
    }

    return eResult;
}

/**
 * @brief These are the APIs deisgned to Implement logic of ATU hardware 
 *        to read to 32-bit address maped to 64-bit address.
 * @note  This API is just for demo purpose. It is not the actual Implementation.
 *        It will just demo how it will work. Actually CPU will issue read to address.
 *        But here we are trying to show with a model, how it will work.
 * 
 * @param u32_address   32-bit address to write to
 * @param value         Fill with value read
 * @return ATU_RESULT   Result of API SUCCESS if value read Succefully otherwise failure.
 */

ATU_RESULT atu_read_channel(uint32_t u32_address, uint32_t* const value)
{
    uint32_t channel_num                        = 0u;
    uint64_t address_to_read_from               = 0u;
    atu_channel_reg_t * intended_channel_addr   = atu_reg_base_addr;
    uint32_t addr_offset                        = 0u;
    ATU_RESULT eResult                          = ATU_FAILURE;

    /* Check if valid input parameters have received */
    if (ATU_SUCCESS == atu_get_channel_from_addr(u32_address, &channel_num))
    {
        /* Get intended address to read by calculating offset */
        intended_channel_addr  += channel_num;
        addr_offset             = u32_address - intended_channel_addr->u32_startAddr;
        address_to_read_from    = (intended_channel_addr->u64_startAddr_L) | (intended_channel_addr->u64_startAddr_M << 32U);
        address_to_read_from   += addr_offset;
        *value                  = *((uint64_t*)address_to_read_from);
        eResult                 = ATU_SUCCESS;
    }

    return eResult;
}
