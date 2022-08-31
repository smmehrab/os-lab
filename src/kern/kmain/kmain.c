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

void test(void){
	/** Test Case: print countVal and countFlag until it is set **/

	SysTick_disable();
	SysTick_enable();
	
	uint8_t outputLine[200];
	uint8_t stkValString[200];
	uint8_t msCountString[200];

	uint8_t countFlag = SysTick_getStatus();
	uint32_t stkVal = SysTick_getCount();
	uint32_t msCount = SysTick_getTime();

	while(1) {
		intToString(stkValString, stkVal);
		intToString(msCountString, msCount);

		outputLine[0] = '';
		concatString(outputLine[1], )


		kprintf((uint8_t *)"%s",(uint8_t *) &"SysTick VAl : ");
		kprintf((uint8_t *)"%d",(uint8_t *) &tickCount);
		kprintf((uint8_t *)"%s",(uint8_t *) &"  ");
		kprintf((uint8_t *)"%s",(uint8_t *) &"mscount : ");
		kprintf((uint8_t *)"%d",(uint8_t *) &timeMS);
		kprintf((uint8_t *)"%s",(uint8_t *) &"  ");
		kprintf((uint8_t *)"%s",(uint8_t *) &"COUNTFLAG : 0");
		kprintf((uint8_t *)"%s",(uint8_t *) &"\n");

		if(countFlag==1) {
			kprintf((uint8_t *)"%s",(uint8_t *) &"\n");
			break;
		}

		countFlag = SysTick_getStatus();
		stkVal = SysTick_getCount();
		msCount = SysTick_getTime();
	}
}

void test2(uint32_t setTimeMS){
	/** Count upto TimeMS **/

	SysTick_Disable();
	SysTick_Enable();
	
	uint8_t stat = SysTick_GetStatus() + '0';
	uint32_t tickCount = SysTick_GetCount();		// Expected to start from LOAD VALUE
	uint32_t timeMS = SysTickGetTime();				// Expected to start from 0
	// systick delay
	while(timeMS <= setTimeMS){
		kprintf((uint8_t *)"%s",(uint8_t *) &"SysTick VAl : ");
		kprintf((uint8_t *)"%d",(uint8_t *) &tickCount);
		kprintf((uint8_t *)"%s",(uint8_t *) &"  ");
		kprintf((uint8_t *)"%s",(uint8_t *) &"mscount : ");
		kprintf((uint8_t *)"%d",(uint8_t *) &timeMS);
		kprintf((uint8_t *)"%s",(uint8_t *) &"  ");
		kprintf((uint8_t *)"%s",(uint8_t *) &"COUNTFLAG : ");
		kprintf((uint8_t *)"%c",(uint8_t *) &stat);
		kprintf((uint8_t *)"%s",(uint8_t *) &"\n");
		stat = SysTick_GetStatus() + '0';
		tickCount = SysTick_GetCount();
		timeMS = SysTickGetTime();
	}	
	kprintf((uint8_t *)"%s",(uint8_t *) &"\n");
}

void kmain(void) {
	__sys_init();

	// title
	kprintf((uint8_t*)"%s",(uint8_t*)"###########################################\n");
	kprintf((uint8_t*)"%s",(uint8_t*)"Booting OS CSE: ");
	kprintf((uint8_t*)"%s",(uint8_t*)"Version: 1.0\n");
	kprintf((uint8_t*)"%s",(uint8_t*)"###########################################\n");
	kprintf((uint8_t*)"%s",(uint8_t*)"Welcome ...");

	SysTick_enable();
	int startTime = 0;
	int endTime= 0;
	int time = 0;
	uint8_t c;

	// loop
	while(1){
		// demo_kprintf_kscanf();
		// demo_systick();

		startTime = SysTick_getTime();

		kprintf((uint8_t*)"%s",(uint8_t*)"Press Enter to Get Time (ms)");
		kscanf((uint8_t*)"%c", &c);
		
		endTime = SysTick_getTime();
		time += endTime - startTime;

		kprintf((uint8_t*)"%d",(uint8_t*)&time);

		//you can change the following line by replacing a delay function
		for(uint32_t i=0;i<1000000;i++){}
	}
}