#ifndef __SYS_TICK_H
#define __SYS_TICK_H
#include"stdint.h"


/******************************************* SysTick *******************************************/

/************************* Data Structures *************************/

// programming-manual p228-233
// SysTick address to access: 0xE000E010 (Starting Address)
#define STK ((SysTick_TypeDef*) 0xE000E010)

typedef struct {
    volatile uint32_t CTRL;             /*!< Offset: 0x000 (R/W)  SysTick Control and Status Register */
    volatile uint32_t LOAD;             /*!< Offset: 0x004 (R/W)  SysTick Reload Value Register */
    volatile uint32_t VAL;              /*!< Offset: 0x008 (R/W)  SysTick Current Value Register */
    volatile const uint32_t CALIB;      /*!< Offset: 0x00C (R/ )  SysTick Calibration Register */
} SysTick_TypeDef;

/************************* Function Definitions *************************/

// 9 Functions

void SysTick_init(uint32_t);
void SysTick_enable(void);
void SysTick_disable(void);
uint32_t SysTick_getCount(void);
void SysTick_update(uint32_t tick);
uint32_t SysTick_getTime(void);
void SysTick_delay(uint16_t ticks);
uint32_t SysTick_getStatus(void);
void SysTick_Handler(void);

/******************************************* SCB *******************************************/

/************************* Data Structures *************************/

// programming-manual p206

// SCB address to access: 0xE000ED00 (Starting Address)
#define SCB ((SCB_TypeDef*) 0xE000ED00)

typedef struct {
    volatile uint32_t CPUID;    // CPUID Base Register 0x0
    volatile uint32_t ICSR;     // Interrupt Control and State Register 0x4
    volatile uint32_t VTOR;     // Vector Table Offset Register 0x8
    volatile uint32_t AIRCR;    // Application Interrupt and Reset Control Register 0xC
    volatile uint32_t SCR;      // System Control Register 0x10
    volatile uint32_t CCR;      // Configuration and Control Register 0x14
    volatile uint8_t SHPR[12];  // Exception priority setting for system exceptions
    volatile uint32_t SHCSR;    // System Handler Control and State Register 0x24
    volatile uint32_t CFSR;     // Configurable Fault Status Register combined of MemManage
    // Fault Status Register, BusFault Status Register, UsageFault Status Register 0x28
    volatile uint32_t HFSR;     // HardFault Status Register 0x2C
    volatile uint32_t DFSR;     //Hint information for causes of debug events
    volatile uint32_t MMFAR;    // MemManage Fault Address Register 0x34
    volatile uint32_t BFAR;     // BusFault Address Register 0x38
    volatile uint32_t AFSR;     // Auxiliary Fault Status Register 0x3C
    volatile uint32_t PFR[2];   // Read only information on available processor features
    volatile uint32_t DFR;      // Read only information on available debug features
    volatile uint32_t AFR;      // Read only information on available auxiliary features
    volatile uint32_t MMFR[3];  // Read only information on available memory model features
    volatile uint32_t ISAR[5];  //
    uint32_t RESERVED1[5];      //
    volatile uint32_t CPACR;    // Coprocessor access control register 0x88
} SCB_TypeDef;


// cmsis_armclang
// typedef struct {

//   volatile const  uint32_t CPUID;                  /*!< Offset: 0x000 (R/ )  CPUID Base Register */

//   volatile uint32_t ICSR;                   /*!< Offset: 0x004 (R/W)  Interrupt Control and State Register */

//   volatile uint32_t VTOR;                   /*!< Offset: 0x008 (R/W)  Vector Table Offset Register */

//   volatile uint32_t AIRCR;                  /*!< Offset: 0x00C (R/W)  Application Interrupt and Reset Control Register */

//   volatile uint32_t SCR;                    /*!< Offset: 0x010 (R/W)  System Control Register */

//   volatile uint32_t CCR;                    /*!< Offset: 0x014 (R/W)  Configuration Control Register */

//   volatile uint8_t  SHP[12U];               /*!< Offset: 0x018 (R/W)  System Handlers Priority Registers (4-7, 8-11, 12-15) */

//   volatile uint32_t SHCSR;                  /*!< Offset: 0x024 (R/W)  System Handler Control and State Register */

//   volatile uint32_t CFSR;                   /*!< Offset: 0x028 (R/W)  Configurable Fault Status Register */

//   volatile uint32_t HFSR;                   /*!< Offset: 0x02C (R/W)  HardFault Status Register */

//   volatile uint32_t DFSR;                   /*!< Offset: 0x030 (R/W)  Debug Fault Status Register */

//   volatile uint32_t MMFAR;                  /*!< Offset: 0x034 (R/W)  MemManage Fault Address Register */

//   volatile uint32_t BFAR;                   /*!< Offset: 0x038 (R/W)  BusFault Address Register */

//   volatile uint32_t AFSR;                   /*!< Offset: 0x03C (R/W)  Auxiliary Fault Status Register */

//   volatile const  uint32_t PFR[2U];                /*!< Offset: 0x040 (R/ )  Processor Feature Register */

//   volatile const  uint32_t DFR;                    /*!< Offset: 0x048 (R/ )  Debug Feature Register */

//   volatile const  uint32_t ADR;                    /*!< Offset: 0x04C (R/ )  Auxiliary Feature Register */

//   volatile const  uint32_t MMFR[4U];               /*!< Offset: 0x050 (R/ )  Memory Model Feature Register */

//   volatile const  uint32_t ISAR[5U];               /*!< Offset: 0x060 (R/ )  Instruction Set Attributes Register */

//   uint32_t RESERVED0[5U];

//   volatile uint32_t CPACR;                  /*!< Offset: 0x088 (R/W)  Coprocessor Access Control Register */

// } SCB_TypeDef;


/******************************************* NVIC *******************************************/

/************************* Data Structures *************************/

// programming-manual p194

// NVIC address to access: 0xE000E100 (Starting Address)
#define NVIC  ((NVIC_TypeDef*) 0xE000E100)

typedef struct {
    //define NVIC register compenenets -- use volatile data type
    volatile uint32_t ISER[8];  /*!< Offset: 0x000 addr: 0xE000E100 Interrupt Set Enable Register*/
    uint32_t RESERVED0[24];
    volatile uint32_t ICER[8];  /*!< Offset: 0x080 addr: 0xE000E180 Interrupt Clear Enable Register*/
    uint32_t RSERVED1[24];
    volatile uint32_t ISPR[8];  /*!< Offset: 0x100 addr: 0xE000E200 Interrupt Set Pending Register*/
    uint32_t RESERVED2[24];
    volatile uint32_t ICPR[8];  /*!< Offset: 0x180 addr: 0xE000E280 Interrupt Clear Pending Register*/
    uint32_t RESERVED3[24];
    volatile uint32_t IABR[8];  /*!< Offset: 0x200 addr: 0xE000E300 Interrupt Active bit Register*/
    uint32_t RESERVED4[56];
    volatile uint8_t IP[240];   /*!< Offset: 0x300 addr: 0xE000E400 Interrupt Priority Register (8Bit wide) */
    uint32_t RESERVED5[644];
    volatile uint32_t STIR;     /*!< Offset: 0xE00 addr: 0xE000EF00 Software Trigger Interrupt Register*/
} NVIC_TypeDef;

typedef enum IRQn_Type {
/******  Cortex-M4 Processor Exceptions Numbers ****************************************************************/
  NonMaskableInt_IRQn         = -14,    /*!< 2 Non Maskable Interrupt                                          */
  MemoryManagement_IRQn       = -12,    /*!< 4 Cortex-M4 Memory Management Interrupt                           */
  BusFault_IRQn               = -11,    /*!< 5 Cortex-M4 Bus Fault Interrupt                                   */
  UsageFault_IRQn             = -10,    /*!< 6 Cortex-M4 Usage Fault Interrupt                                 */
  SVCall_IRQn                 = -5,     /*!< 11 Cortex-M4 SV Call Interrupt                                    */
  DebugMonitor_IRQn           = -4,     /*!< 12 Cortex-M4 Debug Monitor Interrupt                              */
  PendSV_IRQn                 = -2,     /*!< 14 Cortex-M4 Pend SV Interrupt                                    */
  SysTick_IRQn                = -1,     /*!< 15 Cortex-M4 System Tick Interrupt                                */
/******  STM32 specific Interrupt Numbers **********************************************************************/
  WWDG_IRQn                   = 0,      /*!< Window WatchDog Interrupt                                         */
  PVD_IRQn                    = 1,      /*!< PVD through EXTI Line detection Interrupt                         */
  TAMP_STAMP_IRQn             = 2,      /*!< Tamper and TimeStamp interrupts through the EXTI line             */
  RTC_WKUP_IRQn               = 3,      /*!< RTC Wakeup interrupt through the EXTI line                        */
  FLASH_IRQn                  = 4,      /*!< FLASH global Interrupt                                            */
  RCC_IRQn                    = 5,      /*!< RCC global Interrupt                                              */
  EXTI0_IRQn                  = 6,      /*!< EXTI Line0 Interrupt                                              */
  EXTI1_IRQn                  = 7,      /*!< EXTI Line1 Interrupt                                              */
  EXTI2_IRQn                  = 8,      /*!< EXTI Line2 Interrupt                                              */
  EXTI3_IRQn                  = 9,      /*!< EXTI Line3 Interrupt                                              */
  EXTI4_IRQn                  = 10,     /*!< EXTI Line4 Interrupt                                              */
  DMA1_Stream0_IRQn           = 11,     /*!< DMA1 Stream 0 global Interrupt                                    */
  DMA1_Stream1_IRQn           = 12,     /*!< DMA1 Stream 1 global Interrupt                                    */
  DMA1_Stream2_IRQn           = 13,     /*!< DMA1 Stream 2 global Interrupt                                    */
  DMA1_Stream3_IRQn           = 14,     /*!< DMA1 Stream 3 global Interrupt                                    */
  DMA1_Stream4_IRQn           = 15,     /*!< DMA1 Stream 4 global Interrupt                                    */
  DMA1_Stream5_IRQn           = 16,     /*!< DMA1 Stream 5 global Interrupt                                    */
  DMA1_Stream6_IRQn           = 17,     /*!< DMA1 Stream 6 global Interrupt                                    */
  ADC_IRQn                    = 18,     /*!< ADC1, ADC2 and ADC3 global Interrupts                             */
  CAN1_TX_IRQn                = 19,     /*!< CAN1 TX Interrupt                                                 */
  CAN1_RX0_IRQn               = 20,     /*!< CAN1 RX0 Interrupt                                                */
  CAN1_RX1_IRQn               = 21,     /*!< CAN1 RX1 Interrupt                                                */
  CAN1_SCE_IRQn               = 22,     /*!< CAN1 SCE Interrupt                                                */
  EXTI9_5_IRQn                = 23,     /*!< External Line[9:5] Interrupts                                     */
  TIM1_BRK_TIM9_IRQn          = 24,     /*!< TIM1 Break interrupt and TIM9 global interrupt                    */
  TIM1_UP_TIM10_IRQn          = 25,     /*!< TIM1 Update Interrupt and TIM10 global interrupt                  */
  TIM1_TRG_COM_TIM11_IRQn     = 26,     /*!< TIM1 Trigger and Commutation Interrupt and TIM11 global interrupt */
  TIM1_CC_IRQn                = 27,     /*!< TIM1 Capture Compare Interrupt                                    */
  TIM2_IRQn                   = 28,     /*!< TIM2 global Interrupt                                             */
  TIM3_IRQn                   = 29,     /*!< TIM3 global Interrupt                                             */
  TIM4_IRQn                   = 30,     /*!< TIM4 global Interrupt                                             */
  I2C1_EV_IRQn                = 31,     /*!< I2C1 Event Interrupt                                              */
  I2C1_ER_IRQn                = 32,     /*!< I2C1 Error Interrupt                                              */
  I2C2_EV_IRQn                = 33,     /*!< I2C2 Event Interrupt                                              */
  I2C2_ER_IRQn                = 34,     /*!< I2C2 Error Interrupt                                              */
  SPI1_IRQn                   = 35,     /*!< SPI1 global Interrupt                                             */
  SPI2_IRQn                   = 36,     /*!< SPI2 global Interrupt                                             */
  USART1_IRQn                 = 37,     /*!< USART1 global Interrupt                                           */
  USART2_IRQn                 = 38,     /*!< USART2 global Interrupt                                           */
  USART3_IRQn                 = 39,     /*!< USART3 global Interrupt                                           */
  EXTI15_10_IRQn              = 40,     /*!< External Line[15:10] Interrupts                                   */
  RTC_Alarm_IRQn              = 41,     /*!< RTC Alarm (A and B) through EXTI Line Interrupt                   */
  OTG_FS_WKUP_IRQn            = 42,     /*!< USB OTG FS Wakeup through EXTI line interrupt                     */
  TIM8_BRK_TIM12_IRQn         = 43,     /*!< TIM8 Break Interrupt and TIM12 global interrupt                   */
  TIM8_UP_TIM13_IRQn          = 44,     /*!< TIM8 Update Interrupt and TIM13 global interrupt                  */
  TIM8_TRG_COM_TIM14_IRQn     = 45,     /*!< TIM8 Trigger and Commutation Interrupt and TIM14 global interrupt */
  TIM8_CC_IRQn                = 46,     /*!< TIM8 Capture Compare global interrupt                             */
  DMA1_Stream7_IRQn           = 47,     /*!< DMA1 Stream7 Interrupt                                            */
  FMC_IRQn                    = 48,     /*!< FMC global Interrupt                                              */
  SDIO_IRQn                   = 49,     /*!< SDIO global Interrupt                                             */
  TIM5_IRQn                   = 50,     /*!< TIM5 global Interrupt                                             */
  SPI3_IRQn                   = 51,     /*!< SPI3 global Interrupt                                             */
  UART4_IRQn                  = 52,     /*!< UART4 global Interrupt                                            */
  UART5_IRQn                  = 53,     /*!< UART5 global Interrupt                                            */
  TIM6_DAC_IRQn               = 54,     /*!< TIM6 global and DAC1&2 underrun error  interrupts                 */
  TIM7_IRQn                   = 55,     /*!< TIM7 global interrupt                                             */
  DMA2_Stream0_IRQn           = 56,     /*!< DMA2 Stream 0 global Interrupt                                    */
  DMA2_Stream1_IRQn           = 57,     /*!< DMA2 Stream 1 global Interrupt                                    */
  DMA2_Stream2_IRQn           = 58,     /*!< DMA2 Stream 2 global Interrupt                                    */
  DMA2_Stream3_IRQn           = 59,     /*!< DMA2 Stream 3 global Interrupt                                    */
  DMA2_Stream4_IRQn           = 60,     /*!< DMA2 Stream 4 global Interrupt                                    */
  CAN2_TX_IRQn                = 63,     /*!< CAN2 TX Interrupt                                                 */
  CAN2_RX0_IRQn               = 64,     /*!< CAN2 RX0 Interrupt                                                */
  CAN2_RX1_IRQn               = 65,     /*!< CAN2 RX1 Interrupt                                                */
  CAN2_SCE_IRQn               = 66,     /*!< CAN2 SCE Interrupt                                                */
  OTG_FS_IRQn                 = 67,     /*!< USB OTG FS global Interrupt                                       */
  DMA2_Stream5_IRQn           = 68,     /*!< DMA2 Stream 5 global interrupt                                    */
  DMA2_Stream6_IRQn           = 69,     /*!< DMA2 Stream 6 global interrupt                                    */
  DMA2_Stream7_IRQn           = 70,     /*!< DMA2 Stream 7 global interrupt                                    */
  USART6_IRQn                 = 71,     /*!< USART6 global interrupt                                           */
  I2C3_EV_IRQn                = 72,     /*!< I2C3 event interrupt                                              */
  I2C3_ER_IRQn                = 73,     /*!< I2C3 error interrupt                                              */
  OTG_HS_EP1_OUT_IRQn         = 74,     /*!< USB OTG HS End Point 1 Out global interrupt                       */
  OTG_HS_EP1_IN_IRQn          = 75,     /*!< USB OTG HS End Point 1 In global interrupt                        */
  OTG_HS_WKUP_IRQn            = 76,     /*!< USB OTG HS Wakeup through EXTI interrupt                          */
  OTG_HS_IRQn                 = 77,     /*!< USB OTG HS global interrupt                                       */
  DCMI_IRQn                   = 78,     /*!< DCMI global interrupt                                             */
  FPU_IRQn                    = 81,     /*!< FPU global interrupt                                              */
  SPI4_IRQn                   = 84,     /*!< SPI4 global Interrupt                                             */
  SAI1_IRQn                   = 87,     /*!< SAI1 global Interrupt                                             */
  SAI2_IRQn                   = 91,     /*!< SAI2 global Interrupt                                             */
  QUADSPI_IRQn                = 92,     /*!< QuadSPI global Interrupt                                          */
  CEC_IRQn                    = 93,     /*!< CEC global Interrupt                                              */
  SPDIF_RX_IRQn               = 94,     /*!< SPDIF-RX global Interrupt                                          */
  FMPI2C1_EV_IRQn             = 95,     /*!< FMPI2C1 Event Interrupt                                           */
  FMPI2C1_ER_IRQn             = 96      /*!< FMPI2C1 Error Interrupt                                           */  
} IRQn_Type;

/************************* Function Definitions *************************/

// 17 Functions

void __NVIC_SetPriority (IRQn_Type IRQn, uint32_t priority);
uint32_t __NVIC_GetPriority(IRQn_Type IRQn);
void __NVIC_EnableIRQn(IRQn_Type IRQn);
void __NVIC_DisableIRQn(IRQn_Type IRQn);
void __disable_irq(void);
void __set_BASEPRI(uint32_t value);
void __enable_irq(void);
void __unset_BASEPRI(uint32_t value);
void __set_PRIMASK(uint32_t);
uint32_t __get_PRIMASK(void);
void __enable_fault_irq(void);
void __set_FAULTMASK(uint32_t);
void __disable_fault_irq(void);
uint32_t __get_FAULTMASK(void);
void __clear_pending_IRQn(IRQn_Type);
uint32_t __get_pending_IRQn(IRQn_Type);
uint32_t __NVIC_GetActive(IRQn_Type);

/***************************************************************************/

#endif