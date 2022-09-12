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

    /*
    programming manual - p201
    The processor implements only bits[7:4] of each field, 
    bits[3:0] read as zero and ignore writes.
    */

    if (IRQn >= 0) {
        NVIC->IP[IRQn] = (uint8_t)(priority << 4);
    }

    else {
        /*
        programming manual - p216
        -------------------------------------------------------
        Memory management fault     PRI_4     |     SHPR1
        Bus fault                   PRI_5     |
        Usage fault                 PRI_6     |

        SVCall                      PRI_11    |     SHPR2

        PendSV                      PRI_14    |     SHPR3
        SysTick                     PRI_15    |
        -------------------------------------------------------

        So, IRQn & 15 = PRI
        SHPR[12]
        */

        SCB->SHPR[(IRQn & 15)-4] = (uint8_t)(priority << 4);
    }
}

uint32_t __NVIC_GetPriority(IRQn_Type IRQn) {
    uint32_t priority;
    if (IRQn >= 0) {
        priority = (NVIC->IP[IRQn] >> 4);
    }
    else {
        priority = (SCB->SHPR[(IRQn & 15)-4] >> 4);
    }
    return priority;
}

void __NVIC_EnableIRQn(IRQn_Type IRQn) {
    uint32_t index = IRQn >> 5;
    uint32_t offset = IRQn % 32;
    NVIC->ISER[index] = (1 << offset);
}

void __NVIC_DisableIRQn(IRQn_Type IRQn)  {
    uint32_t index = IRQn >> 5;
    uint32_t offset = IRQn % 32;
    NVIC->ICER[index] = (1 << offset);
}

/*
- The PRIMASK register prevents activation of all exceptions with configurable priority.

- The FAULTMASK register prevents activation of all exceptions except for Non-Maskable
  Interrupt (NMI).

- The BASEPRI register defines the minimum priority for exception processing. When
  BASEPRI is set to a nonzero value, it prevents the activation of all exceptions with same or
  lower priority level as the BASEPRI value.
*/

void __disable_irq(void) {
    __ASM volatile ("cpsie i" : : : "memory");
}

void __set_BASEPRI(uint32_t value) {
    /*
    programming manual - p24
    BASEPRI[7:4] Priority mask bits
    */
    value = (value << 4);
    __ASM volatile("MSR BASEPRI, %0" : : "r" (value) : "memory");
}

void __enable_irq(void) {
    __set_PRIMASK(0);
}

void __unset_BASEPRI(uint32_t value) {
    // cmsis
    __ASM volatile ("MSR BASEPRI, %0" : : "r" (value) : "memory");
}

void __set_PRIMASK(uint32_t priMask) {
    // cmsis
    __ASM volatile ("MSR PRIMASK, %0" : : "r" (priMask) : "memory");
}

uint32_t __get_PRIMASK(void) {
    // cmsis
    uint32_t value;
    __ASM volatile ("MRS %0, PRIMASK" : "=r" (value));
    return value;
}

void __enable_fault_irq(void) {
    // cmsis
    __ASM volatile ("cpsie f" : : : "memory");
}

void __set_FAULTMASK(uint32_t faultMask) {
    // cmsis
    __ASM volatile ("MSR faultmask, %0" : : "r" (faultMask) : "memory");
}

void __disable_fault_irq(void) {
    // cmsis
    __ASM volatile ("cpsid f" : : : "memory");
}

uint32_t __get_FAULTMASK(void) {
    // cmsis
    uint32_t value;
    __ASM volatile ("MRS %0, faultmask" : "=r" (value));
    return value;
}

void __clear_pending_IRQn(IRQn_Type IRQn) {
    uint32_t index = IRQn >> 5;
    uint32_t offset = IRQn % 32;
    NVIC->ICPR[index] |= (uint32_t)(1 << offset);
}

uint32_t __get_pending_IRQn(IRQn_Type IRQn) {
    uint32_t index = IRQn >> 5;
    uint32_t offset = IRQn % 32;
    return ((NVIC->ISPR[index]) & (uint32_t)(1 << offset));
}

uint32_t __NVIC_GetActive(IRQn_Type IRQn) {
    uint32_t index = IRQn >> 5;
    uint32_t offset = IRQn % 32;
    return (NVIC->IABR[index] & (1 << offset));
}