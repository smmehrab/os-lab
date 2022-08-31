#include "../include/sys/sys.h"
#include "../include/dev/usart.h"
#include "../../../include/kstdio.h"

volatile uint32_t mscount;

// AHB (180 MHz)
uint32_t clockChoice = 1;
uint32_t clockRateMHz = 180;

void SysTick_init(uint32_t tick) {
    SysTick_disable();

    // STK->LOAD 
    // RELOAD [23:0]
    // 0x00000000 - 0x00FFFFFF
    STK->LOAD = ((clockRateMHz * 1000 * tick) - 1);

    // A write of any value clears the field to 0, and also clears the COUNTFLAG 
    // bit in the STK_CTRL register to 0.
    STK->VAL = 0;

    // STK->CTRL [TICKINT]
    // Bit 1
    // 1: Counting down to zero to asserts the SysTick exception request
    STK->CTRL |= (1<<1);

    // STK->CTRL [CLKSOURCE]
    // Bit 2
    // 0: AHB/8
    // 1: Processor clock (AHB)
    STK->CTRL |= (clockChoice<<2);
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
    STK->LOAD = ((clockRateMHz * 1000 * tick) - 1);
    mscount = 0;
}

uint32_t SysTick_getTime(void) {
    return mscount;
}

void SysTick_delay(uint16_t ticks){
    for(int i=0; i<ticks; i++) {
        while(!SysTick_getStatus());
    }
}

uint8_t SysTick_getStatus(void) {
    // STK->CTRL COUNTFLAG
    // Bit 16
    // Returns 1 if timer counted to 0 since last time this was read.
    if(STK->CTRL & (1<<16))
        return 1;
    return 0;
}

// SysTick ISR 
void SysTick_Handler(void) {
    mscount += ((STK->LOAD+1)/(clockRateMHz*1000));
    kprintf((uint8_t*)"%d", (uint8_t*)&mscount);
}