/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-09-22     Bernard      add board.h to this bsp
 */

// <<< Use Configuration Wizard in Context Menu >>>
#ifndef __BOARD_H__
    #define __BOARD_H__

    #include <n32g43x.h>
    #include "drv_common.h"
    #include "drv_clk.h"

    // <o> Internal SRAM memory size[Kbytes] <8-64>
    //  <i>Default: 64
    #ifdef __ICCARM__
        // Use *.icf ram symbal, to avoid hardcode.
        extern char __ICFEDIT_region_RAM_end__;
        #define N32_SRAM_END          &__ICFEDIT_region_RAM_end__
    #else
        #define N32_SRAM_SIZE         32
        #define N32_SRAM_END          (0x20000000 + N32_SRAM_SIZE * 1024)
    #endif

    #if defined(__CC_ARM) || defined(__CLANG_ARM)
        extern int Image$$RW_IRAM1$$ZI$$Limit;
        #define HEAP_BEGIN    (&Image$$RW_IRAM1$$ZI$$Limit)
    #elif __ICCARM__
        #pragma section="HEAP"
        #define HEAP_BEGIN    (__segment_end("HEAP"))
    #else
        extern int __bss_end;
        #define HEAP_BEGIN    (&__bss_end)
    #endif

    #define HEAP_END          N32_SRAM_END

#endif

//*** <<< end of configuration section >>>    ***
