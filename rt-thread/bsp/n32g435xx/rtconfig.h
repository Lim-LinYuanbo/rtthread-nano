/* RT-Thread config file */

#ifndef __RTTHREAD_CFG_H__
#define __RTTHREAD_CFG_H__

// <<< Use Configuration Wizard in Context Menu >>>

// <h>Basic Configuration
// <o>Maximal level of thread priority <8-256>
//  <i>Default: 32
#define RT_THREAD_PRIORITY_MAX  32
// <o>OS tick per second
//  <i>Default: 1000   (1ms)
#define RT_TICK_PER_SECOND  1000
// <o>Alignment size for CPU architecture data access
//  <i>Default: 4
#define RT_ALIGN_SIZE   4
// <o>the max length of object name<2-16>
//  <i>Default: 8
#define RT_NAME_MAX    8
// <c1>Using RT-Thread components initialization
//  <i>Using RT-Thread components initialization
#define RT_USING_COMPONENTS_INIT
// </c>

#define RT_USING_USER_MAIN

// <o>the stack size of main thread<1-4086>
//  <i>Default: 512
#define RT_MAIN_THREAD_STACK_SIZE     256

// </h>

// <h>Debug Configuration
// <c1>enable kernel debug configuration
//  <i>Default: enable kernel debug configuration
//#define RT_DEBUG
// </c>
// <o>enable components initialization debug configuration<0-1>
//  <i>Default: 0
#define RT_DEBUG_INIT 0
// <c1>thread stack over flow detect
//  <i> Diable Thread stack over flow detect
//#define RT_USING_OVERFLOW_CHECK
// </c>
// </h>

// <h>Hook Configuration
// <c1>using hook
//  <i>using hook
//#define RT_USING_HOOK
// </c>
// <c1>using idle hook
//  <i>using idle hook
//#define RT_USING_IDLE_HOOK
// </c>
// </h>

// <e>Software timers Configuration
// <i> Enables user timers
#define RT_USING_TIMER_SOFT         0
#if RT_USING_TIMER_SOFT == 0
    #undef RT_USING_TIMER_SOFT
#endif
// <o>The priority level of timer thread <0-31>
//  <i>Default: 4
#define RT_TIMER_THREAD_PRIO        4
// <o>The stack size of timer thread <0-8192>
//  <i>Default: 512
#define RT_TIMER_THREAD_STACK_SIZE  512
// </e>

// <h>IPC(Inter-process communication) Configuration
// <c1>Using Semaphore
//  <i>Using Semaphore
#define RT_USING_SEMAPHORE
// </c>
// <c1>Using Mutex
//  <i>Using Mutex
#define RT_USING_MUTEX
// </c>
// <c1>Using Event
//  <i>Using Event
//#define RT_USING_EVENT
// </c>
// <c1>Using MailBox
//  <i>Using MailBox
#define RT_USING_MAILBOX
// </c>
// <c1>Using Message Queue
//  <i>Using Message Queue
#define RT_USING_MESSAGEQUEUE
// </c>
// </h>

// <h>Memory Management Configuration
// <c1>Dynamic Heap Management
//  <i>Dynamic Heap Management
#define RT_USING_HEAP
// </c>
// <c1>using small memory
//  <i>using small memory
#define RT_USING_SMALL_MEM
// </c>
// <c1>using tiny size of memory
//  <i>using tiny size of memory
//#define RT_USING_TINY_SIZE
// </c>
// </h>

// <h>Console Configuration
// <c1>Using console
//  <i>Using console
#define RT_USING_CONSOLE

// </c>
// <o>the buffer size of console <1-1024>
//  <i>the buffer size of console
//  <i>Default: 128  (128Byte)
#define RT_CONSOLEBUF_SIZE          256
// </h>

// <h>FinSH Configuration
// <c1>include finsh config
//  <i>Select this choice if you using FinSH 
#include "finsh_config.h"
// </c>
// </h>

// <h>Device Configuration
// <c1>using device framework
//  <i>using device framework
#define RT_USING_DEVICE
#define RT_USING_CONSOLE
#define RT_CONSOLEBUF_SIZE 256
#define RT_CONSOLE_DEVICE_NAME "uart1"
// </c>
// </h>

#define RT_USING_PIN
#define RT_USING_SERIAL
#define RT_SERIAL_USING_DMA
#define RT_SERIAL_RB_BUFSZ 64
//#define RT_USING_ADC
//#define RT_USING_PWM

#define BSP_USING_GPIO
#define BSP_USING_UART
#define BSP_USING_UART1
//#define BSP_USING_UART2
//#define BSP_USING_UART3
//#define BSP_USING_TIM3
//#define BSP_USING_PWM
//#define BSP_USING_TIM1_CH1
//#define BSP_USING_TIM1_CH2
//#define BSP_USING_TIM1_CH3
//#define BSP_USING_TIM1_CH4
//#define BSP_USING_TIM2_CH1
//#define BSP_USING_TIM2_CH2
//#define BSP_USING_TIM2_CH3
//#define BSP_USING_TIM2_CH4
//#define BSP_USING_TIM3_CH1
//#define BSP_USING_TIM3_CH2
//#define BSP_USING_TIM3_CH3
//#define BSP_USING_TIM3_CH4
//#define BSP_USING_TIM4_CH1
//#define BSP_USING_TIM4_CH2
//#define BSP_USING_TIM4_CH3
//#define BSP_USING_TIM4_CH4
//#define BSP_USING_TIM5_CH1
//#define BSP_USING_TIM5_CH2
//#define BSP_USING_TIM5_CH3
//#define BSP_USING_TIM5_CH4
//#define BSP_USING_TIM8_CH1
//#define BSP_USING_TIM8_CH2
//#define BSP_USING_TIM8_CH3
//#define BSP_USING_TIM8_CH4
//#define BSP_USING_ADC
//#define BSP_USING_ADC2


// <<< end of configuration section >>>

#endif
