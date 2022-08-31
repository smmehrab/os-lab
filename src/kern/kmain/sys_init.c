#include "../include/sys_init.h"
#include "../arch/stm32f446re/include/dev/clock.h"
#include "../arch/stm32f446re/include/dev/usart.h"
#include "../arch/stm32f446re/include/dev/gpio.h"
#include "../arch/stm32f446re/include/sys/stm32_peps.h"
#include "../arch/stm32f446re/include/sys/sys.h"

// turn on the fpu
void DRV_FPU_ACTIVE(void){
    SCB->CPACR |= ((3UL << 10*2) |  (3UL << 11*2));
}

void __sys_init(void) {
	DRV_CLOCK_INIT(); //configure system clock 180 MHz
	// For the SysTick Exception Handler to be called, every 10ms
	SysTick_init(10);
	DRV_GPIO_INIT(GPIOA);
	DRV_USART_INIT(USART2); //configure as standard input and output 
	DRV_FPU_ACTIVE();
}
