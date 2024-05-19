# ARM_ATU_Problem
In the interview with ARM ATU bare metal driver implementation was expected. Here is an implementation for that.

## Problem in Detail:
As described in [Block_Diagram](https://github.com/Akshay1595/ARM_ATU_Problem/blob/main/ATU_Problem_Block_Diag.jpg), we have 32-bit CPU with 32-bit address bus and 64-bit address bus which has peripherals attached to it.
There is ATU (Address translation Unit) which is responsible for mapping 32-bit addresses to 64-bit addresses. 
ATU peripheral has few registers that can be configured for multiple 64-bit addressable channels which are assigned to peripherals/modules.
ATU registers:
1] 32-bit start address register
2] 32-bit end address register
3] 64-bit start address register (LSB and MSB)
4] 64-bit end address register (LSB and MSB)
5] channel attributes (Enable/Disable)

Problem: Design a bare metal driver code to configure this ATU peripheral with above requirements.

### Solution:
1] [Driver_Code](https://github.com/Akshay1595/ARM_ATU_Problem/blob/main/src/atu.c) Implements API atu_init_channel() for initialization of ATU
2] To test the code we have written model which implements functionality of hardware IP ATU with two APIs: atu_write_channel() and atu_read_channel().
   In real hardware, whenever write or read is issued to 32-bit mapped address, such read and write will not need any API.
   This model is just for demo purpose.
3] With such model we have designed few testcases in [test.c](https://github.com/Akshay1595/ARM_ATU_Problem/blob/main/src/test.c)


