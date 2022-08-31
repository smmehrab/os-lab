#include "../include/sys_init.h"
#include "../include/kmain.h"
#include "../include/kstdio.h"
#include "../arch/stm32f446re/include/sys/stm32_peps.h"
#include "../arch/stm32f446re/include/sys/sys.h"
#include <stdint.h>

void demo_kprintf_kscanf() {
	uint8_t inputString[200];
	uint8_t inputCharacter;
	uint32_t inputDecimal;
	uint32_t inputHexadecimal;
	float inputFloat1;
	float inputFloat2;
	float sumFloat;

	kprintf((uint8_t*)"%s",(uint8_t*)"[DEMO] kscanf() & kprintf()\n");
	kprintf((uint8_t*)"%s",(uint8_t*)"[INPUT]");

	kprintf((uint8_t*)"%s",(uint8_t*)"Enter A String");
	kscanf((uint8_t*)"%s", inputString);
	kprintf((uint8_t*)"%s",(uint8_t*)"[STRING]");
	kprintf((uint8_t*)"%s",(uint8_t*)&inputString);

	kprintf((uint8_t*)"%s",(uint8_t*)"Enter A Character");
	kscanf((uint8_t*)"%c", (uint8_t*)&inputCharacter);
	kprintf((uint8_t*)"%s",(uint8_t*)"[CHARACTER]");
	kprintf((uint8_t*)"%c",(uint8_t*)&inputCharacter);

	kprintf((uint8_t*)"%s",(uint8_t*)"Enter A Decimal Number");
	kscanf((uint8_t*)"%d", (uint8_t*)&inputDecimal);
	kprintf((uint8_t*)"%s",(uint8_t*)"[DECIMAL]");
	kprintf((uint8_t*)"%d",(uint8_t*)&inputDecimal);

	kprintf((uint8_t*)"%s",(uint8_t*)"Enter A Hexadecimal Number");
	kscanf((uint8_t*)"%x", (uint8_t*)&inputHexadecimal);
	kprintf((uint8_t*)"%s",(uint8_t*)"[HEXADECIMAL]");
	kprintf((uint8_t*)"%x",(uint8_t*)&inputHexadecimal);

	kprintf((uint8_t*)"%s",(uint8_t*)"Enter A Floating Point Number");
	kscanf((uint8_t*)"%f", (uint8_t*)&inputFloat1);
	kprintf((uint8_t*)"%s",(uint8_t*)"[FLOAT]");
	kprintf((uint8_t*)"%f",(uint8_t*)&inputFloat1);
		
	kprintf((uint8_t*)"%s",(uint8_t*)"Enter Another Floating Point Number");
	kscanf((uint8_t*)"%f", (uint8_t*)&inputFloat2);
	kprintf((uint8_t*)"%s",(uint8_t*)"[FLOAT]");
	kprintf((uint8_t*)"%f",(uint8_t*)&inputFloat2);

	// float addition
	kprintf((uint8_t*)"%s",(uint8_t*)"[FPU]");
	kprintf((uint8_t*)"%s",(uint8_t*)"Input Float 1:");
	kprintf((uint8_t*)"%f",(uint8_t*)&inputFloat1);
	kprintf((uint8_t*)"%s",(uint8_t*)"Input Float 2:");
	kprintf((uint8_t*)"%f",(uint8_t*)&inputFloat2);

	sumFloat = inputFloat1 + inputFloat2;

	kprintf((uint8_t*)"%s",(uint8_t*)"Summation:");
	kprintf((uint8_t*)"%f",(uint8_t*)&sumFloat);

	float divFloat = inputFloat1 / inputFloat2;

	kprintf((uint8_t*)"%s",(uint8_t*)"Division:");
	kprintf((uint8_t*)"%f",(uint8_t*)&divFloat);

	kprintf((uint8_t*)"%s",(uint8_t*)"-------------------------------------------\n");
}


void kmain(void) {
	__sys_init();

	// title
	kprintf((uint8_t*)"%s",(uint8_t*)"###########################################\n");
	kprintf((uint8_t*)"%s",(uint8_t*)"> Booting OS CSE: ");
	kprintf((uint8_t*)"%s",(uint8_t*)"Version: 1.0\n");
	kprintf((uint8_t*)"%s",(uint8_t*)"###########################################\n");
	kprintf((uint8_t*)"%s",(uint8_t*)"\n> ... Welcome ... \n");

	SysTick_enable();
	int startTime = 0;
	int endTime= 0;
	uint8_t stopCharacter;

	// loop
	while(1){
		// demo_kprintf_kscanf();

		startTime = SysTick_getTime();

		kprintf((uint8_t*)"%s",(uint8_t*)"Timer Running...");
		kscanf((uint8_t*)"%c", &stopCharacter);
		
		endTime = SysTick_getTime();

		//you can change the following line by replacing a delay function
		for(uint32_t i=0;i<1000000;i++){}	
	}
}