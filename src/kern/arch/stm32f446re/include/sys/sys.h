#ifndef __SYS_TICK_H
#define __SYS_TICK_H
#include"stdint.h"

// programming-manual p228-233

// SysTick address to access: 0xE000E010 (Starting Address)
#define STK ((SysTick_TypeDef*) 0xE000E010)

typedef struct {
    volatile uint32_t CTRL;             /*!< Offset: 0x000 (R/W)  SysTick Control and Status Register */
    volatile uint32_t LOAD;             /*!< Offset: 0x004 (R/W)  SysTick Reload Value Register */
    volatile uint32_t VAL;              /*!< Offset: 0x008 (R/W)  SysTick Current Value Register */
    volatile const uint32_t CALIB;      /*!< Offset: 0x00C (R/ )  SysTick Calibration Register */
} SysTick_TypeDef;

void SysTick_init(uint32_t);
void SysTick_enable(void);
void SysTick_disable(void);
uint32_t SysTick_getCount(void);
uint8_t SysTick_getStatus(void);
void SysTick_update(uint32_t newTick);
uint32_t SysTick_getTime(void);

void SysTick_Handler(void);

#endif