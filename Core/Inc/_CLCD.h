/* 16 x 2 Character LCD Library
 *
 * Development environment specifics:
 * STM32F407VET6
 * VS Code                  1.96.0
 * STM32 VS Code Extension  2.1.1
 * STM32 CubeMX             6.12.0
 * LL Library (RCC, GPIO)
 */

#ifndef _CLCD_H
#define _CLCD_H

#include "stm32f4xx_ll_bus.h"
#include "stm32f4xx_ll_gpio.h"
#include "stm32f4xx_ll_utils.h"

// Pin setting
#define GPIO_RS GPIOE
#define GPIO_RW GPIOE
#define GPIO_EN GPIOE
#define GPIO_D4 GPIOE
#define GPIO_D5 GPIOE
#define GPIO_D6 GPIOE
#define GPIO_D7 GPIOE

#define GPIO_PIN_RS LL_GPIO_PIN_0
#define GPIO_PIN_RW LL_GPIO_PIN_1
#define GPIO_PIN_EN LL_GPIO_PIN_2
#define GPIO_PIN_D4 LL_GPIO_PIN_4
#define GPIO_PIN_D5 LL_GPIO_PIN_5
#define GPIO_PIN_D6 LL_GPIO_PIN_6
#define GPIO_PIN_D7 LL_GPIO_PIN_7

void CLCD_GPIO_Init(void);
void CLCD_Instruction(uint8_t order);
void CLCD_Write_Data(uint8_t ch);
void CLCD_Init(void);
void CLCD_Cursor_Pos(uint8_t x, uint8_t y);
void CLCD_Print(uint8_t x, uint8_t y, uint8_t *str);
void CLCD_Clear(void);

#endif