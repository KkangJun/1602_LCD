/* 16 x 2 Character LCD Library
 *
 * Development environment specifics:
 * STM32F407VET6
 * VS Code                  1.96.0
 * STM32 VS Code Extension  2.1.1
 * STM32 CubeMX             6.12.0
 * LL Library (RCC, GPIO)
 */

#include "_CLCD.h"

void CLCD_GPIO_Init(void) {
  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOE);

  LL_GPIO_ResetOutputPin(GPIO_RS, GPIO_PIN_RS);
  LL_GPIO_ResetOutputPin(GPIO_RW, GPIO_PIN_RW);
  LL_GPIO_ResetOutputPin(GPIO_EN, GPIO_PIN_EN);
  LL_GPIO_ResetOutputPin(GPIO_D4, GPIO_PIN_D4);
  LL_GPIO_ResetOutputPin(GPIO_D5, GPIO_PIN_D5);
  LL_GPIO_ResetOutputPin(GPIO_D6, GPIO_PIN_D6);
  LL_GPIO_ResetOutputPin(GPIO_D7, GPIO_PIN_D7);

  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;

  GPIO_InitStruct.Pin = GPIO_PIN_RS;
  LL_GPIO_Init(GPIO_RS, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = GPIO_PIN_RW;
  LL_GPIO_Init(GPIO_RW, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = GPIO_PIN_EN;
  LL_GPIO_Init(GPIO_EN, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = GPIO_PIN_D4;
  LL_GPIO_Init(GPIO_D4, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = GPIO_PIN_D5;
  LL_GPIO_Init(GPIO_D5, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = GPIO_PIN_D6;
  LL_GPIO_Init(GPIO_D6, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = GPIO_PIN_D7;
  LL_GPIO_Init(GPIO_D7, &GPIO_InitStruct);
}

void CLCD_Instruction(uint8_t order) {
  // CLCD Setting mode => RS = 0, RW = 0
  GPIO_RS->ODR &= ~GPIO_PIN_RS;
  GPIO_RW->ODR &= ~GPIO_PIN_RW;
  GPIO_EN->ODR &= ~GPIO_PIN_EN;

  // Higher 4 bits
  GPIO_D7->ODR = (order & 0x80) ? (GPIO_D7->ODR | GPIO_PIN_D7)
                                : (GPIO_D7->ODR & ~GPIO_PIN_D7);
  GPIO_D6->ODR = (order & 0x40) ? (GPIO_D6->ODR | GPIO_PIN_D6)
                                : (GPIO_D6->ODR & ~GPIO_PIN_D6);
  GPIO_D5->ODR = (order & 0x20) ? (GPIO_D5->ODR | GPIO_PIN_D5)
                                : (GPIO_D5->ODR & ~GPIO_PIN_D5);
  GPIO_D4->ODR = (order & 0x10) ? (GPIO_D4->ODR | GPIO_PIN_D4)
                                : (GPIO_D4->ODR & ~GPIO_PIN_D4);

  // Enable Signal
  GPIO_EN->ODR |= GPIO_PIN_EN;
  GPIO_EN->ODR &= ~GPIO_PIN_EN;

  // Lower 4 bits
  GPIO_D7->ODR = (order & 0x08) ? (GPIO_D7->ODR | GPIO_PIN_D7)
                                : (GPIO_D7->ODR & ~GPIO_PIN_D7);
  GPIO_D6->ODR = (order & 0x04) ? (GPIO_D6->ODR | GPIO_PIN_D6)
                                : (GPIO_D6->ODR & ~GPIO_PIN_D6);
  GPIO_D5->ODR = (order & 0x02) ? (GPIO_D5->ODR | GPIO_PIN_D5)
                                : (GPIO_D5->ODR & ~GPIO_PIN_D5);
  GPIO_D4->ODR = (order & 0x01) ? (GPIO_D4->ODR | GPIO_PIN_D4)
                                : (GPIO_D4->ODR & ~GPIO_PIN_D4);

  // Enable Signal
  GPIO_EN->ODR |= GPIO_PIN_EN;
  GPIO_EN->ODR &= ~GPIO_PIN_EN;

  LL_mDelay(1);
}

void CLCD_Write_Data(uint8_t ch) {
  // CLCD Write Data mode => RS = 1, RW = 0
  GPIO_RS->ODR |= GPIO_PIN_RS;
  GPIO_RW->ODR &= ~GPIO_PIN_RW;
  GPIO_EN->ODR &= ~GPIO_PIN_EN;

  // Higher 4 bits
  GPIO_D7->ODR = (ch & 0x80) ? (GPIO_D7->ODR | GPIO_PIN_D7)
                             : (GPIO_D7->ODR & ~GPIO_PIN_D7);
  GPIO_D6->ODR = (ch & 0x40) ? (GPIO_D6->ODR | GPIO_PIN_D6)
                             : (GPIO_D6->ODR & ~GPIO_PIN_D6);
  GPIO_D5->ODR = (ch & 0x20) ? (GPIO_D5->ODR | GPIO_PIN_D5)
                             : (GPIO_D5->ODR & ~GPIO_PIN_D5);
  GPIO_D4->ODR = (ch & 0x10) ? (GPIO_D4->ODR | GPIO_PIN_D4)
                             : (GPIO_D4->ODR & ~GPIO_PIN_D4);

  // Enable Signal
  GPIO_EN->ODR |= GPIO_PIN_EN;
  GPIO_EN->ODR &= ~GPIO_PIN_EN;

  // Lower 4 bits
  GPIO_D7->ODR = (ch & 0x08) ? (GPIO_D7->ODR | GPIO_PIN_D7)
                             : (GPIO_D7->ODR & ~GPIO_PIN_D7);
  GPIO_D6->ODR = (ch & 0x04) ? (GPIO_D6->ODR | GPIO_PIN_D6)
                             : (GPIO_D6->ODR & ~GPIO_PIN_D6);
  GPIO_D5->ODR = (ch & 0x02) ? (GPIO_D5->ODR | GPIO_PIN_D5)
                             : (GPIO_D5->ODR & ~GPIO_PIN_D5);
  GPIO_D4->ODR = (ch & 0x01) ? (GPIO_D4->ODR | GPIO_PIN_D4)
                             : (GPIO_D4->ODR & ~GPIO_PIN_D4);

  // Enable Signal
  GPIO_EN->ODR |= GPIO_PIN_EN;
  GPIO_EN->ODR &= ~GPIO_PIN_EN;

  LL_mDelay(1);
}

void CLCD_Init(void) {
  // wait for CLCD boot
  LL_mDelay(100);

  // Function Set => DB5 = 1 (CLCD 4 bits mode)
  // DB4(DL) : Bits mode
  // DB3(N) = Number of display lines
  // DB2(F) = set Font
  CLCD_Instruction(0x28);
  LL_mDelay(10);

  // Prevention of malfunctions
  CLCD_Instruction(0x28);
  LL_mDelay(10);

  // Display On/off Controll => DB3 = 1
  // DB2(D) = Display on/off
  // DB1(C) = Display Cursor on/off
  // DB0(B) = Set Cursor blinks
  CLCD_Instruction(0x0C);

  // Entry Mode Set => DB2 = 1
  // DB1(I/D) = DDRAM Address increments or decrements
  // DB0(S) = Entire display either to the right or left
  CLCD_Instruction(0x06);

  // Return Home => DB1 = 1
  CLCD_Instruction(0x02);

  // Clear Display
  CLCD_Instruction(0x01);
  CLCD_Instruction(0x01);
}

void CLCD_Cursor_Pos(uint8_t x, uint8_t y) {
  // Set DDRAM Address mode => DB7 = 1
  switch (y) {
    case 0:
      // DDRAM Address = 0x00 + x => DB6 = 0
      CLCD_Instruction(0x80 + x);
      break;
    case 1:
      // DDRAM Address = 0x40 + x => DB6 = 1
      CLCD_Instruction(0xC0 + x);
  }
}

void CLCD_Print(uint8_t x, uint8_t y, uint8_t *str) {
  uint8_t i = 0;

  CLCD_Cursor_Pos(x, y);
  do {
    CLCD_Write_Data(str[i]);
  } while (str[++i] != 0x00);
}

void CLCD_Clear(void) {
  CLCD_Instruction(0x01);
  LL_mDelay(10);
}