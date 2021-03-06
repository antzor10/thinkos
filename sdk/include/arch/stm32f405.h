/* 
 * Copyright(C) 2013 Robinson Mittmann. All Rights Reserved.
 * 
 * This file is part of the libstm32f.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3.0 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You can receive a copy of the GNU Lesser General Public License from 
 * http://www.gnu.org/
 */

/** 
 * @file stm32f405.h
 * @brief
 * @author Robinson Mittmann <bobmittmann@gmail.com>
 */ 

#ifndef __STM32F405_H__
#define __STM32F405_H__

#include <arch/stm32f4xx.h>

#ifndef __ASSEMBLER__

#define STM32_PWR ((struct stm32_pwr *)STM32F_BASE_PWR)
#define STM32_RCC ((struct stm32_rcc *)STM32_BASE_RCC)
#define STM32_FLASH ((struct stm32_flash *)STM32_BASE_FLASH)

#define STM32F_RTC ((struct stm32f_rtc *)STM32F_BASE_RTC)
#define STM32F_OTG_FS ((struct stm32f_otg_fs *)STM32F_BASE_OTG_FS)
#define STM32F_FSMC ((struct stm32f_fsmc *)STM32F_BASE_FSMC)
#define STM32F_SYSCFG ((struct stm32f_syscfg *)STM32F_BASE_SYSCFG)
#define STM32F_DAC ((struct stm32f_dac *)STM32F_BASE_DAC)
#define STM32F_ADC1 ((struct stm32f_adc *)STM32F_BASE_ADC1)
#define STM32F_ADC2 ((struct stm32f_adc *)STM32F_BASE_ADC2)
#define STM32F_ADC3 ((struct stm32f_adc *)STM32F_BASE_ADC3)
#define STM32F_ADCC ((struct stm32f_adcc *)STM32F_BASE_ADCC)

#define STM32F_EXTI ((struct stm32f_exti *)STM32F_BASE_EXTI)

#define STM32_USART1 ((struct stm32_usart *)STM32F_BASE_USART1)
#define STM32_USART2 ((struct stm32_usart *)STM32F_BASE_USART2)
#define STM32_USART3 ((struct stm32_usart *)STM32F_BASE_USART3)
#define STM32_UART4 ((struct stm32_usart *)STM32F_BASE_UART4)
#define STM32_UART5 ((struct stm32_usart *)STM32F_BASE_UART5)
#define STM32_USART6 ((struct stm32_usart *)STM32F_BASE_USART6)

#define STM32F_SPI1 ((struct stm32f_spi *)STM32F_BASE_SPI1)
#define STM32F_SPI2 ((struct stm32f_spi *)STM32F_BASE_SPI2)
#define STM32F_I2S2EXT ((struct stm32f_spi *)STM32F_BASE_I2S2EXT)
#define STM32F_SPI3 ((struct stm32f_spi *)STM32F_BASE_SPI3)
#define STM32F_I2S3EXT ((struct stm32f_spi *)STM32F_BASE_I2S3EXT)

#define STM32F_SPI4 ((struct stm32f_spi *)STM32F_BASE_SPI4)

#define STM32F_I2C1 ((struct stm32f_i2c *)STM32F_BASE_I2C1)
#define STM32F_I2C2 ((struct stm32f_i2c *)STM32F_BASE_I2C2)
#define STM32F_I2C3 ((struct stm32f_i2c *)STM32F_BASE_I2C3)

#define STM32F_DMA1 ((struct stm32f_dma *)STM32F_BASE_DMA1)
#define STM32F_DMA2 ((struct stm32f_dma *)STM32F_BASE_DMA2)

#define STM32F_TIM1 ((struct stm32f_tim *)STM32F_BASE_TIM1)
#define STM32F_TIM2 ((struct stm32f_tim *)STM32F_BASE_TIM2)
#define STM32F_TIM3 ((struct stm32f_tim *)STM32F_BASE_TIM3)
#define STM32F_TIM4 ((struct stm32f_tim *)STM32F_BASE_TIM4)
#define STM32F_TIM5 ((struct stm32f_tim *)STM32F_BASE_TIM5)
#define STM32F_TIM6 ((struct stm32f_tim *)STM32F_BASE_TIM6)
#define STM32F_TIM7 ((struct stm32f_tim *)STM32F_BASE_TIM7)
#define STM32F_TIM8 ((struct stm32f_tim *)STM32F_BASE_TIM8)
#define STM32F_TIM9 ((struct stm32f_tim *)STM32F_BASE_TIM9)
#define STM32F_TIM10 ((struct stm32f_tim *)STM32F_BASE_TIM10)
#define STM32F_TIM11 ((struct stm32f_tim *)STM32F_BASE_TIM11)
#define STM32F_TIM12 ((struct stm32f_tim *)STM32F_BASE_TIM12)
#define STM32F_TIM13 ((struct stm32f_tim *)STM32F_BASE_TIM13)
#define STM32F_TIM14 ((struct stm32f_tim *)STM32F_BASE_TIM14)

#define STM32_GPIOA ((struct stm32_gpio *)STM32_BASE_GPIOA)
#define STM32_GPIOB ((struct stm32_gpio *)STM32_BASE_GPIOB)
#define STM32_GPIOC ((struct stm32_gpio *)STM32_BASE_GPIOC)
#define STM32_GPIOD ((struct stm32_gpio *)STM32_BASE_GPIOD)
#define STM32_GPIOE ((struct stm32_gpio *)STM32_BASE_GPIOE)
#define STM32_GPIOF ((struct stm32_gpio *)STM32_BASE_GPIOF)
#define STM32_GPIOG ((struct stm32_gpio *)STM32_BASE_GPIOG)
#define STM32_GPIOH ((struct stm32_gpio *)STM32_BASE_GPIOH)
#define STM32_GPIOI ((struct stm32_gpio *)STM32_BASE_GPIOI)
#define STM32_GPIO(N) ((struct stm32_gpio *)(STM32_BASE_GPIOA + (N)*0x400))

#endif /* __ASSEMBLER__ */

#endif /* __STM32F405_H__ */

