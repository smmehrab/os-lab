#include "../include/sys/sys.h"
#include "../include/dev/usart.h"
#include "../../../include/kstdio.h"

/******************************************* SysTick *******************************************/

volatile uint32_t mscount;

// AHB (180 MHz)
uint32_t clockChoice = 1;
uint32_t clockRateMHz = 180;

void SysTick_init(uint32_t tick) {
    SysTick_disable();

    // A write of any value clears the field to 0, and also clears the COUNTFLAG 
    // bit in the STK_CTRL register to 0.
    STK->VAL = 0;

    // STK->LOAD 
    // RELOAD [23:0]
    // 0x00000000 - 0x00FFFFFF
    STK->LOAD = ((clockRateMHz * 1000U * tick) - 1);
    // reload value in this case = 1799999

    // STK->CTRL [CLKSOURCE]
    // Bit 2
    // 0: AHB/8
    // 1: Processor clock (AHB)
    STK->CTRL |= (clockChoice<<2);

    // STK->CTRL [TICKINT]
    // Bit 1
    // 1: Counting down to zero to asserts the SysTick exception request
    STK->CTRL |= (1<<1);

    SysTick_enable();
}

void SysTick_enable(void) {
    // if SysTick is disabled
    if(!(STK->CTRL & (1<<0))) {
        mscount = 0;
        STK->VAL = 0;
    }

    // SYSTICK->CTRL [ENABLE]
    // Bit 0
    // 1: Counter enabled
    STK->CTRL |= (1<<0);
}

void SysTick_disable(void) {
    // SYSTICK->CTRL [ENABLE]
    // Bit 0
    // 0: Counter disabled
    STK->CTRL &= ~(1<<0);
}

uint32_t SysTick_getCount(void) {
    return STK->VAL;
}

void SysTick_update(uint32_t tick) {
    SysTick_disable();
    STK->LOAD = ((clockRateMHz * 1000U * tick) - 1);
    mscount = 0;
    SysTick_enable();
}

uint32_t SysTick_getTime(void) {
    uint32_t alreadyElapsed = (STK->LOAD - SysTick_getCount());
    alreadyElapsed = ((alreadyElapsed)/(clockRateMHz*1000));
    return mscount + alreadyElapsed;
}

void SysTick_delay(uint16_t ticks){
    for(int i=0; i<ticks; i++) {
        while(!SysTick_getStatus());
    }
}

uint32_t SysTick_getStatus(void) {
    // STK->CTRL COUNTFLAG
    // Bit 16
    // Returns 1 if timer counted to 0 since last time this was read.
    if(STK->CTRL & (1<<16)) {
        return 1;
    }
    return 0;
}

// SysTick ISR
void SysTick_Handler(void) {
    mscount += ((STK->LOAD+1)/(clockRateMHz*1000));
    // Debug
    // kprintf((uint8_t*)"%d", (uint8_t*)&mscount);
}

/******************************************* NVIC *******************************************/

void __NVIC_SetPriority (IRQn_Type IRQn, uint32_t priority) {

}

uint32_t __NVIC_GetPriority(IRQn_Type IRQn) {
    uint32_t priority;
    return priority;
}

void __NVIC_EnableIRQn(IRQn_Type IRQn) {

}

void __NVIC_DisableIRQn(IRQn_Type IRQn)  {

}

void __disable_irq(void) {

}

void __set_BASEPRI(uint32_t value) {

}

void __enable_irq(void) {

}

void __unset_BASEPRI(uint32_t value) {

}

void __set_PRIMASK(uint32_t priMask) {

}

uint32_t __get_PRIMASK(void) {
    uint32_t result;
    return result;
}

void __enable_fault_irq(void) {

}

void __set_FAULTMASK(uint32_t faultMask) {

}

void __disable_fault_irq(void) {

}

uint32_t __get_FAULTMASK(void) {
    uint32_t result;
    return result;
}

void __clear_pending_IRQn(IRQn_Type irqn) {

}

uint32_t __get_pending_IRQn(IRQn_Type irqn) {
    uint32_t result;
    return result;
}

uint32_t __NVIC_GetActive(IRQn_Type irqn) {
    uint32_t result;
    return result;
}