#include "../include/sys_init.h"
#include "../include/kmain.h"
#include "../include/kstdio.h"
#include "../arch/stm32f446re/include/sys/stm32_peps.h"
#include "../arch/stm32f446re/include/sys/sys.h"
#include <stdint.h>

/*
void nvicDemo();
USART2_Handler();
kmain();
*/

/***************************************************************/

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

/***************************************************************/

void countFlagTest() {
	uint8_t c;
	kprintf((uint8_t*)"%s",(uint8_t*)"Run COUNTFLAG Test? [Press Enter]");
	kscanf((uint8_t*)"%c", &c);
	kprintf((uint8_t*)"%s",(uint8_t*)"----------------------");
	kprintf((uint8_t*)"%s",(uint8_t*)"[COUNTFLAG Test]");
	kprintf((uint8_t*)"%s",(uint8_t*)"----------------------");

	SysTick_disable();
	SysTick_enable();

	uint32_t countFlag = SysTick_getStatus();
	uint32_t stkVal = SysTick_getCount();
	uint32_t msCount = SysTick_getTime();

	while(1) {
		kprintf((uint8_t*)"%s",(uint8_t*) &"[COUNTFLAG]");
		kprintf((uint8_t*)"%d",(uint8_t*) &countFlag);
		kprintf((uint8_t*)"%s",(uint8_t*) &"[STK->VAL]");
		kprintf((uint8_t*)"%d",(uint8_t*) &stkVal);
		kprintf((uint8_t*)"%s",(uint8_t*) &"[MSCOUNT]");
		kprintf((uint8_t*)"%d",(uint8_t*) &msCount);
		kprintf((uint8_t*)"%s",(uint8_t*)"----------------------");

		if(countFlag==1) {
			kprintf((uint8_t*)"%s",(uint8_t*) &"[Congratulations]");
			kprintf((uint8_t*)"%s",(uint8_t*) &"COUNTFLAG became 1");
			kprintf((uint8_t*)"%s",(uint8_t*) &"Time to call SysTick_Handler\n\n");
			kprintf((uint8_t*)"%s",(uint8_t*)"----------------------");
			break;
		}

		countFlag = SysTick_getStatus();
		stkVal = SysTick_getCount();
		msCount = SysTick_getTime();
	}
}

void timeTrackingTest() {
	uint8_t c;
	kprintf((uint8_t*)"%s",(uint8_t*)"Run Time Tracking Test? [Press Enter]");
	kscanf((uint8_t*)"%c", &c);
	kprintf((uint8_t*)"%s",(uint8_t*)"----------------------");
	kprintf((uint8_t*)"%s",(uint8_t*)"[Time Tracking Test]");
	kprintf((uint8_t*)"%s",(uint8_t*)"----------------------");

	uint32_t time;
	kprintf((uint8_t*)"%s",(uint8_t*)"Time (ms) to Track for:");
	kscanf((uint8_t*)"%d", (uint8_t*)&time);

	SysTick_disable();
	SysTick_enable();
	
	uint32_t countFlag = SysTick_getStatus();
	uint32_t stkVal = SysTick_getCount();
	uint32_t msCount = SysTick_getTime();

	kprintf((uint8_t*)"%s",(uint8_t*)"----------------------");

	while(msCount <= time) {
		kprintf((uint8_t*)"%s",(uint8_t*) &"[COUNTFLAG]");
		kprintf((uint8_t*)"%d",(uint8_t*) &countFlag);
		kprintf((uint8_t*)"%s",(uint8_t*) &"[STK->VAL]");
		kprintf((uint8_t*)"%d",(uint8_t*) &stkVal);
		kprintf((uint8_t*)"%s",(uint8_t*) &"[MSCOUNT]");
		kprintf((uint8_t*)"%d",(uint8_t*) &msCount);
		kprintf((uint8_t*)"%s",(uint8_t*)"----------------------");
		countFlag = SysTick_getStatus();
		stkVal = SysTick_getCount();
		msCount = SysTick_getTime();
	}
	kprintf((uint8_t*)"%s",(uint8_t*) &"[Congratulations]");
	kprintf((uint8_t*)"%d",(uint8_t*) &time);
	kprintf((uint8_t*)"%s",(uint8_t*) &"Tracked successfully.");
	kprintf((uint8_t*)"%s",(uint8_t*)"----------------------");
}

void sysTickUpdateTest() {
	uint8_t c;
	kprintf((uint8_t*)"%s",(uint8_t*)"Run SysTick Update Test? [Press Enter]");
	kscanf((uint8_t*)"%c", &c);
	kprintf((uint8_t*)"%s",(uint8_t*)"----------------------");
	kprintf((uint8_t*)"%s",(uint8_t*)"[SysTick Update Test]");
	kprintf((uint8_t*)"%s",(uint8_t*)"----------------------");

	SysTick_disable();
	SysTick_enable();

	uint32_t tick = 0;

	kprintf((uint8_t*)"%s",(uint8_t*)"Enter A New Tick");
	kscanf((uint8_t*)"%d", (uint8_t*)&tick);
	
	SysTick_update(tick);

	kprintf((uint8_t*)"%s",(uint8_t*)"SysTick Updated with New Tick");
	kprintf((uint8_t*)"%d",(uint8_t*)&tick);
	kprintf((uint8_t*)"%s",(uint8_t*)"----------------------");

	uint32_t time = 1000;
	uint32_t countFlag = SysTick_getStatus();
	uint32_t stkVal = SysTick_getCount();
	uint32_t msCount = SysTick_getTime();

	kprintf((uint8_t*)"%s",(uint8_t*)"----------------------");

	while(msCount <= time) {
		kprintf((uint8_t*)"%s",(uint8_t*) &"[COUNTFLAG]");
		kprintf((uint8_t*)"%d",(uint8_t*) &countFlag);
		kprintf((uint8_t*)"%s",(uint8_t*) &"[STK->VAL]");
		kprintf((uint8_t*)"%d",(uint8_t*) &stkVal);
		kprintf((uint8_t*)"%s",(uint8_t*) &"[MSCOUNT]");
		kprintf((uint8_t*)"%d",(uint8_t*) &msCount);
		kprintf((uint8_t*)"%s",(uint8_t*)"----------------------");
		countFlag = SysTick_getStatus();
		stkVal = SysTick_getCount();
		msCount = SysTick_getTime();
	}
	kprintf((uint8_t*)"%s",(uint8_t*) &"[Congratulations]");
	kprintf((uint8_t*)"%d",(uint8_t*) &time);
	kprintf((uint8_t*)"%s",(uint8_t*) &"Tracked successfully.");
	kprintf((uint8_t*)"%s",(uint8_t*)"----------------------");
}

void sysTickDelayTest() {
	uint8_t c;
	kprintf((uint8_t*)"%s",(uint8_t*)"Run SysTick Delay Test? [Press Enter]");
	kscanf((uint8_t*)"%c", &c);
	kprintf((uint8_t*)"%s",(uint8_t*)"----------------------");
	kprintf((uint8_t*)"%s",(uint8_t*)"[SysTick Delay Test]");
	kprintf((uint8_t*)"%s",(uint8_t*)"----------------------");

	SysTick_disable();
	SysTick_enable();

	uint32_t ticks = 0;

	kprintf((uint8_t*)"%s",(uint8_t*)"Enter Delay Ticks");
	kscanf((uint8_t*)"%d", (uint8_t*)&ticks);
	
	uint32_t countFlag = SysTick_getStatus();
	uint32_t stkVal = SysTick_getCount();
	uint32_t msCount = SysTick_getTime();

	kprintf((uint8_t*)"%s",(uint8_t*)"----------------------");
	kprintf((uint8_t*)"%s",(uint8_t*) &"[COUNTFLAG]");
	kprintf((uint8_t*)"%d",(uint8_t*) &countFlag);
	kprintf((uint8_t*)"%s",(uint8_t*) &"[STK->VAL]");
	kprintf((uint8_t*)"%d",(uint8_t*) &stkVal);
	kprintf((uint8_t*)"%s",(uint8_t*) &"[MSCOUNT]");
	kprintf((uint8_t*)"%d",(uint8_t*) &msCount);
	kprintf((uint8_t*)"%s",(uint8_t*)"----------------------");

	kprintf((uint8_t*)"%s",(uint8_t*)"delay started...");
	SysTick_delay(ticks);
	kprintf((uint8_t*)"%s",(uint8_t*)"delay ended...");

	countFlag = SysTick_getStatus();
	stkVal = SysTick_getCount();
	msCount = SysTick_getTime();

	kprintf((uint8_t*)"%s",(uint8_t*)"----------------------");
	kprintf((uint8_t*)"%s",(uint8_t*) &"[COUNTFLAG]");
	kprintf((uint8_t*)"%d",(uint8_t*) &countFlag);
	kprintf((uint8_t*)"%s",(uint8_t*) &"[STK->VAL]");
	kprintf((uint8_t*)"%d",(uint8_t*) &stkVal);
	kprintf((uint8_t*)"%s",(uint8_t*) &"[MSCOUNT]");
	kprintf((uint8_t*)"%d",(uint8_t*) &msCount);
	kprintf((uint8_t*)"%s",(uint8_t*)"----------------------");
}

void runSysTickTests() {
	countFlagTest();
	timeTrackingTest();
	sysTickUpdateTest();
	sysTickDelayTest();
}

void sysTickDemo() {
	// startTime = SysTick_getTime();
		
	// kprintf((uint8_t*)"%s",(uint8_t*)"Press Enter to Get Time (ms)");
	// kscanf((uint8_t*)"%c", &c);
		
	// endTime = SysTick_getTime();
	// time += (endTime - startTime);
	// kprintf((uint8_t*)"%d",(uint8_t*)&time);

	// runSysTickTests();
}

/***************************************************************/

uint32_t interruptCount;

bool flag;
int index;
char temp;
char input[100];

char mask_all[] = "mask_all\n";
char unmask_all[] = "unmask_all\n";

char set_primask[] = "set_primask\n";
char set_basepri[] = "set_basepri\n";
char set_faultmask[] = "set_faultmask\n";

char disable_nvic[] = "disable_nvic\n";

void nvicDemo() {
	uint8_t c;
	uint32_t priority;
	
	kprintf((uint8_t*)"%s",(uint8_t*)"[NVIC Demo]\n");
	kprintf((uint8_t*)"%s",(uint8_t*)"Enable USART2_IRQn? [Press Enter]");
	kscanf((uint8_t*)"%c", &c);

	// RXNEIE = 1
	USART2->CR1 |= (1 << 5);

	kprintf((uint8_t*)"%s",(uint8_t*)"");

	__enable_irq();
	kprintf((uint8_t*)"%s",(uint8_t*)"__enable_irq() [Called]");

	__NVIC_EnableIRQn(USART2_IRQn);
	kprintf((uint8_t*)"%s",(uint8_t*)"__NVIC_EnableIRQn(USART2_IRQn) [Called]");

	index = 0;
	flag = false;
	interruptCount = 0;
	kprintf((uint8_t*)"%s",(uint8_t*)"USART2_IRQn [Enabled]");

	kprintf((uint8_t*)"%s",(uint8_t*)"");
	priority = __NVIC_GetPriority(USART2_IRQn);
	kprintf((uint8_t*)"%s",(uint8_t*)"__NVIC_GetPriority(USART2_IRQn) [Called]");
	kprintf((uint8_t*)"%s",(uint8_t*)"[Priority Received]");
	kprintf((uint8_t*)"%d",(uint8_t*)&priority);

	kprintf((uint8_t*)"%s",(uint8_t*)"");
	__NVIC_SetPriority(USART2_IRQn, 2);
	kprintf((uint8_t*)"%s",(uint8_t*)"__NVIC_SetPriority(USART2_IRQn, 2) [Called]");
	kprintf((uint8_t*)"%s",(uint8_t*)"[Priority Set 2]");

	kprintf((uint8_t*)"%s",(uint8_t*)"");
	priority = __NVIC_GetPriority(USART2_IRQn);
	kprintf((uint8_t*)"%s",(uint8_t*)"__NVIC_GetPriority(USART2_IRQn) [Called]");
	kprintf((uint8_t*)"%s",(uint8_t*)"[Priority Received]");
	kprintf((uint8_t*)"%d",(uint8_t*)&priority);

	kprintf((uint8_t*)"%s",(uint8_t*)"");
}

bool isEqual(char a[], char b[], int len){
	for (int i=0; i<=len; i++) {
		if(a[i]!=b[i]) {
			return false;
		}
	}
	return true;
}

void USART2_Handler(void){
	// RXNEIE == 1
	if(USART2->SR & (1<<5)) {
		// reset RXNEIE
		USART2->SR &= ~(1<<5);

		interruptCount++;
		
		kprintf((uint8_t*)"%s",(uint8_t*)"USART2_Handler [Called]");
		kprintf((uint8_t *)"%d", (uint8_t *)&interruptCount);

		if(flag){
			flag = false;
			index = 0;
		}
		
		if(!flag){
			temp = USART2->DR;

			if(temp == '\r') {
				flag = true;
				input[index] = '\n';

				kprintf((uint8_t*)"%s",(uint8_t*)&input);

				if(isEqual(input, disable_nvic, index)) {
					__NVIC_DisableIRQn(USART2_IRQn);
				}
				else if(isEqual(input, mask_all, index)) {
					__disable_irq();
				}
				else if(isEqual(input, set_basepri, index)) {
					// __disable_irq();
				}
				
			}

			else{
				input[index++] = temp;
			}
		}
	}
}

void kmain(void) {
	__sys_init();

	// OS Title
	kprintf((uint8_t*)"%s",(uint8_t*)"###########################################\n");
	kprintf((uint8_t*)"%s",(uint8_t*)"Booting OS CSE: ");
	kprintf((uint8_t*)"%s",(uint8_t*)"Version: 1.0\n");
	kprintf((uint8_t*)"%s",(uint8_t*)"###########################################\n");
	kprintf((uint8_t*)"%s",(uint8_t*)"Welcome ...");

	// SysTick Demo
	// int startTime = 0;
	// int endTime= 0;
	// int time = 0;
	// uint8_t c;

	// SysTick_enable();

	nvicDemo();

	// Program Loop
	while(1) {
		
		//you can change the following line by replacing a delay function
		for(uint32_t i=0;i<1000000;i++){}
	}
}