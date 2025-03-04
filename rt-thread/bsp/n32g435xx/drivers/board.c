/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      first implementation
 */
#include <stdint.h>
#include <rthw.h>
#include <rtthread.h>
#include <board.h>

static void ResetClockController_Config(void)
{
}

/** System Clock Configuration
*/
static void SystemClock_Config(void)
{
    SysTick_Config(SystemCoreClock / RT_TICK_PER_SECOND);
    NVIC_SetPriority(SysTick_IRQn, 0);
}

/**
 * This is the timer interrupt service routine.
 *
 */
void SysTick_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    rt_tick_increase();

    /* leave interrupt */
    rt_interrupt_leave();
}

/**
 * This function will initial GD32 board.
 */
void rt_hw_board_init()
{
    /* NVIC Configuration */
#define NVIC_VTOR_MASK              0x3FFFFF80
#ifdef  VECT_TAB_RAM
    /* Set the Vector Table base location at 0x10000000 */
    SCB->VTOR  = (0x10000000 & NVIC_VTOR_MASK);
#else  /* VECT_TAB_FLASH  */
    /* Set the Vector Table base location at 0x08000000 */
    SCB->VTOR  = (0x08000000 & NVIC_VTOR_MASK);
#endif

    ResetClockController_Config();
    SystemClock_Config();

#ifdef RT_USING_PIN
    int rt_hw_pin_init(void);
    rt_hw_pin_init();
#endif

#ifdef RT_USING_SERIAL
    int rt_hw_usart_init(void);
    rt_hw_usart_init();
#endif

#ifdef RT_USING_CONSOLE
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif

#if defined(RT_USING_USER_MAIN) && defined(RT_USING_HEAP)
    rt_system_heap_init((void *)HEAP_BEGIN, (void *)HEAP_END);
#endif

#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif

    print_rcc_freq_info();
}

#ifdef BSP_USING_UART
void n32_msp_usart_init(void *Instance)
{
    GPIO_InitType GPIO_InitStructure;
    USART_Module *USARTx = (USART_Module *)Instance;

    GPIO_InitStruct(&GPIO_InitStructure);
#ifdef BSP_USING_UART1
    if (USART1 == USARTx)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_USART1, ENABLE);
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA | RCC_APB2_PERIPH_AFIO, ENABLE);
        GPIO_InitStructure.Pin        = GPIO_PIN_9;
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
        GPIO_InitStructure.GPIO_Alternate = GPIO_AF4_USART1;
        GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);
        GPIO_InitStructure.Pin       = GPIO_PIN_10;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitStructure.GPIO_Pull      = GPIO_Pull_Up;
        GPIO_InitStructure.GPIO_Alternate = GPIO_AF4_USART1;
        GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);
    }
#endif
#ifdef BSP_USING_UART2
    if (USART2 == USARTx)
    {
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_USART2, ENABLE);
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA | RCC_APB2_PERIPH_AFIO, ENABLE);
        GPIO_InitStructure.Pin        = GPIO_PIN_2;
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
        GPIO_InitStructure.GPIO_Alternate = GPIO_AF4_USART2;
        GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);
        GPIO_InitStructure.Pin       = GPIO_PIN_3;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitStructure.GPIO_Pull      = GPIO_Pull_Up;
        GPIO_InitStructure.GPIO_Alternate = GPIO_AF4_USART2;
        GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);
    }
#endif
#ifdef BSP_USING_UART3
    if (USART3 == USARTx)
    {
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_USART3, ENABLE);
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA | RCC_APB2_PERIPH_AFIO, ENABLE);
        GPIO_InitStructure.Pin        = GPIO_PIN_10;
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
        GPIO_InitStructure.GPIO_Alternate = GPIO_AF0_USART3;
        GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);
        GPIO_InitStructure.Pin       = GPIO_PIN_11;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitStructure.GPIO_Pull      = GPIO_Pull_Up;
        GPIO_InitStructure.GPIO_Alternate = GPIO_AF5_USART3;
        GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);
    }
#endif
    /* Add others */
}
#endif /* BSP_USING_SERIAL */

void n32_msp_adc_init(void *Instance)
{
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA, ENABLE);
    GPIO_InitType GPIO_InitStructure;
    GPIO_InitStruct(&GPIO_InitStructure);
    GPIO_InitStructure.Pin = GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Analog;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);
}

#ifdef BSP_USING_PWM
void n32_msp_tim_init(void *Instance)
{
    TIM_Module *TIMx = (TIM_Module *)Instance;

    if (TIMx == TIM1)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_TIM1, ENABLE);
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA, ENABLE);
        GPIO_InitType GPIO_InitStructure;
        GPIO_InitStruct(&GPIO_InitStructure);
        GPIO_InitStructure.Pin = GPIO_PIN_8 | GPIO_PIN_11;
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
        GPIO_InitStructure.GPIO_Alternate = GPIO_AF2_TIM1;
        GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);
    }

    if (TIMx == TIM2)
    {
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM2, ENABLE);
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA | RCC_APB2_PERIPH_GPIOB, ENABLE);
        GPIO_InitType GPIO_InitStructure;
        GPIO_InitStruct(&GPIO_InitStructure);
        GPIO_InitStructure.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2;
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
        GPIO_InitStructure.GPIO_Alternate = GPIO_AF2_TIM2;
        GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);
        GPIO_InitStructure.Pin = GPIO_PIN_11;
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
        GPIO_InitStructure.GPIO_Alternate = GPIO_AF2_TIM2;
        GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);
    }

    if (TIMx == TIM3)
    {
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM3, ENABLE);
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA | RCC_APB2_PERIPH_GPIOB, ENABLE);
        GPIO_InitType GPIO_InitStructure;
        GPIO_InitStruct(&GPIO_InitStructure);
        GPIO_InitStructure.Pin = GPIO_PIN_6 | GPIO_PIN_7;
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
        GPIO_InitStructure.GPIO_Alternate = GPIO_AF2_TIM3;
        GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);
        GPIO_InitStructure.Pin = GPIO_PIN_0 | GPIO_PIN_1;
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
        GPIO_InitStructure.GPIO_Alternate = GPIO_AF2_TIM3;
        GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);
    }

    if (TIMx == TIM4)
    {
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM4, ENABLE);
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB, ENABLE);
        GPIO_InitType GPIO_InitStructure;
        GPIO_InitStruct(&GPIO_InitStructure);
        GPIO_InitStructure.Pin = GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9;
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
        GPIO_InitStructure.GPIO_Alternate = GPIO_AF2_TIM4;
        GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);
    }

    if (TIMx == TIM5)
    {
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM5, ENABLE);
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA | RCC_APB2_PERIPH_AFIO, ENABLE);
        GPIO_InitType GPIO_InitStructure;
        GPIO_InitStruct(&GPIO_InitStructure);
        GPIO_InitStructure.Pin = GPIO_PIN_0;
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
        GPIO_InitStructure.GPIO_Alternate = GPIO_AF1_TIM5;
        GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);
        GPIO_InitStructure.Pin = GPIO_PIN_1;
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
        GPIO_InitStructure.GPIO_Alternate = GPIO_AF7_TIM5;
        GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);
        GPIO_InitStructure.Pin = GPIO_PIN_2;
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
        GPIO_InitStructure.GPIO_Alternate = GPIO_AF6_TIM5;
        GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);
        GPIO_InitStructure.Pin = GPIO_PIN_3;
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
        GPIO_InitStructure.GPIO_Alternate = GPIO_AF7_TIM5;
        GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);
    }

    if (TIMx == TIM8)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_TIM8, ENABLE);
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOC, ENABLE);
        GPIO_InitType GPIO_InitStructure;
        GPIO_InitStruct(&GPIO_InitStructure);
        GPIO_InitStructure.Pin = GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9;
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
        GPIO_InitStructure.GPIO_Alternate = GPIO_AF6_TIM8;
        GPIO_InitPeripheral(GPIOC, &GPIO_InitStructure);
    }
}
#endif /* BSP_USING_PWM */


#ifdef RT_USING_FINSH
#include <rtdevice.h>
#include <finsh.h>
#if defined(BSP_USING_GPIO)
static int pin_get_sample(int argc, char *argv[])
{
    uint16_t num = atoi(argv[1]);
    int8_t lvl = rt_pin_read(num);
    rt_kprintf("pin=[%d], lvl=[%d]\n", num, lvl);
    return 0;
}
MSH_CMD_EXPORT(pin_get_sample, pin_get_sample num);
static int pin_set_sample(int argc, char *argv[])
{
    uint16_t num = atoi(argv[1]);
    int8_t lvl = atoi(argv[2]);
    rt_kprintf("pin=[%d], lvl=[%d]\n", num, lvl);
    rt_pin_write(num, lvl);
    return 0;
}
MSH_CMD_EXPORT(pin_set_sample, pin_set_sample num lvl);
static int pin_mode_sample(int argc, char *argv[])
{
    uint16_t num = atoi(argv[1]);
    int8_t mode = atoi(argv[2]);
    rt_kprintf("pin=[%d], mode=[%d]\n", num, mode);
    rt_pin_mode(num, mode);
    return 0;
}
MSH_CMD_EXPORT(pin_mode_sample, pin_mode_sample num mode);
static int pin_mode_print(int argc, char *argv[])
{
    rt_kprintf("PIN_MODE_OUTPUT         = 0x00  \n");
    rt_kprintf("PIN_MODE_INPUT          = 0x01  \n");
    rt_kprintf("PIN_MODE_INPUT_PULLUP   = 0x02  \n");
    rt_kprintf("PIN_MODE_INPUT_PULLDOWN = 0x03  \n");
    rt_kprintf("PIN_MODE_OUTPUT_OD      = 0x04  \n");
    return 0;
}
MSH_CMD_EXPORT(pin_mode_print, pin_mode_print);
#endif

#if defined(BSP_USING_UART2) || defined(BSP_USING_UART3)
static void uart_test_rw(rt_device_t uartx, const char *name)
{
    if (uartx == NULL)
    {
        uartx = rt_device_find(name);
        rt_err_t err = rt_device_open(uartx, RT_DEVICE_FLAG_DMA_RX);
        RT_ASSERT(err == RT_EOK);
    }
    rt_device_write(uartx, 0, name, strlen(name));
    rt_device_write(uartx, 0, "\r\n", 2);
    uint8_t recv_buf[64] = {0x0};
    int ret = rt_device_read(uartx, 0, recv_buf, sizeof(recv_buf));
    if (ret != 0)
    {
        for (int i = 0; i < ret; ++i)
            rt_kprintf("[%02x]", recv_buf[i]);
    }
    rt_device_write(uartx, 0, "\r\n", 2);
}
static void uart_test(void)
{
#ifdef BSP_USING_UART2
    static rt_device_t u2 = NULL;
    uart_test_rw(u2, "uart2");
#endif
#ifdef BSP_USING_UART3
    static rt_device_t u3 = NULL;
    uart_test_rw(u3, "uart3");
#endif
}
MSH_CMD_EXPORT(uart_test, uart_test)
#endif

#ifdef BSP_USING_ADC
#define ADC_DEV_NAME        "adc"
#define REFER_VOLTAGE       3300
#define CONVERT_BITS        (1 << 12)
static int adc_vol_sample(int argc, char *argv[])
{
    rt_adc_device_t adc_dev;
    rt_uint32_t value, vol;
    int ch = 0;
    rt_err_t ret = RT_EOK;

    adc_dev = (rt_adc_device_t)rt_device_find(ADC_DEV_NAME);
    if (adc_dev == RT_NULL)
    {
        rt_kprintf("adc sample run failed! can't find %s device!\n", ADC_DEV_NAME);
        return RT_ERROR;
    }

    static const int ch_arr[] = {5, 6, 7, 8, 0, 17, 18};
    for (int i = 0; i < (sizeof(ch_arr) / sizeof(ch_arr[0])); ++i)
    {
        ch = ch_arr[i];
        ret = rt_adc_enable(adc_dev, ch);
        value = rt_adc_read(adc_dev, ch);
        rt_kprintf("ch=[%d] the value is :[%d] \n", ch, value);
        vol = value * REFER_VOLTAGE / CONVERT_BITS;
        rt_kprintf("ch=[%d] the voltage is :[%d] \n", ch, vol);
    }
    rt_kprintf("correct ------>\n");
    uint16_t vref = rt_adc_read(adc_dev, 0);
    static const int ch_tar_arr[] = {5, 6, 7, 8};
    for (int i = 0; i < (sizeof(ch_tar_arr) / sizeof(ch_tar_arr[0])); ++i)
    {
        ch = ch_tar_arr[i];
        ret = rt_adc_enable(adc_dev, ch);
        value = rt_adc_read(adc_dev, ch);
        rt_kprintf("ch=[%d] the value is :[%d] \n", ch, value);
        vol = (1200 * value / vref);
        rt_kprintf("ch=[%d] the voltage is :[%d] \n", ch, vol);
    }

    return ret;
}
MSH_CMD_EXPORT(adc_vol_sample, adc voltage convert sample);
#endif

#ifdef BSP_USING_PWM
static int pwm_set_test(const char *name, int ch,
                        rt_uint32_t period, rt_uint32_t pulse)
{
    struct rt_device_pwm *pwm_dev = (struct rt_device_pwm *)rt_device_find(name);
    if (pwm_dev == RT_NULL)
    {
        rt_kprintf("pwm sample run failed! can't find %s device!\n", name);
        return RT_ERROR;
    }
    rt_pwm_set(pwm_dev, ch, period, pulse);
    rt_pwm_enable(pwm_dev, ch);
    return RT_EOK;
}
static int pwm_led_sample(int argc, char *argv[])
{
    pwm_set_test("tim3pwm", 3, 1000, 400);
    pwm_set_test("tim3pwm", 4, 1000, 600);
    return RT_EOK;
}
MSH_CMD_EXPORT(pwm_led_sample, pwm sample);
#endif

#endif


