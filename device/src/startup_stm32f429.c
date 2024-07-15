#define STACK_SIZE       0x00000200
#define WEAK __attribute__((weak, alias("Default_Handler")))
unsigned long Stack_Pointer[STACK_SIZE];

//system exceptions and interrupts for STM32F42xx_43xx
void Reset_Handler(void);
void NMI_Handler(void) WEAK;
void HardFault_Handler(void) WEAK;
void MemManage_Handler(void) WEAK;
void BusFault_Handler(void) WEAK;
void UsageFault_Handler(void) WEAK;
void SVC_Handler(void) WEAK;
void DebugMon_Handler(void) WEAK;
void PendSV_Handler(void) WEAK;
void SysTick_Handler(void) WEAK;

void WWDG_IRQHandler(void) WEAK;
void PVD_IRQHandler(void) WEAK;
void TAMP_STAMP_IRQHandler(void) WEAK;
void RTC_WKUP_IRQHandler(void) WEAK;
void FLASH_IRQHandler(void) WEAK;
void RCC_IRQHandler(void) WEAK;
void EXTI0_IRQHandler(void) WEAK;
void EXTI1_IRQHandler(void) WEAK;
void EXTI2_IRQHandler(void) WEAK;
void EXTI3_IRQHandler(void) WEAK;
void EXTI4_IRQHandler(void) WEAK;
void DMA1_Stream0_IRQHandler(void) WEAK;
void DMA1_Stream1_IRQHandler(void) WEAK;
void DMA1_Stream2_IRQHandler(void) WEAK;
void DMA1_Stream3_IRQHandler(void) WEAK;
void DMA1_Stream4_IRQHandler(void) WEAK;
void DMA1_Stream5_IRQHandler(void) WEAK;
void DMA1_Stream6_IRQHandler(void) WEAK;
void ADC_IRQHandler(void) WEAK;
void CAN1_TX_IRQHandler(void) WEAK;
void CAN1_RX0_IRQHandler(void) WEAK;
void CAN1_RX1_IRQHandler(void) WEAK;
void CAN1_SCE_IRQHandler(void) WEAK;
void EXTI9_5_IRQHandler(void) WEAK;
void TIM1_BRK_TIM9_IRQHandler(void) WEAK;
void TIM1_UP_TIM10_IRQHandler(void) WEAK;
void TIM1_TRG_COM_TIM11_IRQHandler(void) WEAK;
void TIM1_CC_IRQHandler(void) WEAK;
void TIM2_IRQHandler(void) WEAK;
void TIM3_IRQHandler(void) WEAK;
void TIM4_IRQHandler(void) WEAK;
void I2C1_EV_IRQHandler(void) WEAK;
void I2C1_ER_IRQHandler(void) WEAK;
void I2C2_EV_IRQHandler(void) WEAK;
void I2C2_ER_IRQHandler(void) WEAK;
void SPI1_IRQHandler(void) WEAK;
void SPI2_IRQHandler(void) WEAK;
void USART1_IRQHandler(void) WEAK;
void USART2_IRQHandler(void) WEAK;
void USART3_IRQHandler(void) WEAK;
void EXTI15_10_IRQHandler(void) WEAK;
void RTC_Alarm_IRQHandler(void) WEAK;
void OTG_FS_WKUP_IRQHandler(void) WEAK;
void TIM8_BRK_TIM12_IRQHandler(void) WEAK;
void TIM8_UP_TIM13_IRQHandler(void) WEAK;
void TIM8_TRG_COM_TIM14_IRQHandler(void) WEAK;
void TIM8_CC_IRQHandler(void) WEAK;
void DMA1_Stream7_IRQHandler(void) WEAK;
void FSMC_IRQHandler(void) WEAK;
void SDIO_IRQHandler(void) WEAK;
void TIM5_IRQHandler(void) WEAK;
void SPI3_IRQHandler(void) WEAK;
void UART4_IRQHandler(void) WEAK;
void UART5_IRQHandler(void) WEAK;
void TIM6_DAC_IRQHandler(void) WEAK;
void TIM7_IRQHandler(void) WEAK;
void DMA2_Stream0_IRQHandler(void) WEAK;
void DMA2_Stream1_IRQHandler(void) WEAK;
void DMA2_Stream2_IRQHandler(void) WEAK;
void DMA2_Stream3_IRQHandler(void) WEAK;
void DMA2_Stream4_IRQHandler(void) WEAK;
void ETH_IRQHandler(void) WEAK;
void ETH_WKUP_IRQHandler(void) WEAK;
void CAN2_TX_IRQHandler(void) WEAK;
void CAN2_RX0_IRQHandler(void) WEAK;
void CAN2_RX1_IRQHandler(void) WEAK;
void CAN2_SCE_IRQHandler(void) WEAK;
void OTG_FS_IRQHandler(void) WEAK;
void DMA2_Stream5_IRQHandler(void) WEAK;
void DMA2_Stream6_IRQHandler(void) WEAK;
void DMA2_Stream7_IRQHandler(void) WEAK;
void USART6_IRQHandler(void) WEAK;
void I2C3_EV_IRQHandler(void) WEAK;
void I2C3_ER_IRQHandler(void) WEAK;
void OTG_HS_EP1_OUT_IRQHandler(void) WEAK;
void OTG_HS_EP1_IN_IRQHandler(void) WEAK;
void OTG_HS_WKUP_IRQHandler(void) WEAK;
void OTG_HS_IRQHandler(void) WEAK;
void DCMI_IRQHandler(void) WEAK;
void CRYP_IRQHandler(void) WEAK;
void HASH_RNG_IRQHandler(void) WEAK;
void FPU_IRQHandler(void) WEAK;
void UART7_IRQHandler(void) WEAK;
void UART8_IRQHandler(void) WEAK;
void SPI4_IRQHandler(void) WEAK;
void SPI5_IRQHandler(void) WEAK;
void SPI6_IRQHandler(void) WEAK;
void SAI1_IRQHandler(void) WEAK;
void LTDC_IRQHandler(void) WEAK;
void LTDC_ER_IRQHandler(void) WEAK;
void DMA2D_IRQHandler(void) WEAK;

/*----------Symbols defined in linker script----------------------------------*/
extern unsigned long __text_end__;    /*!< Start address for the initialization
                                            values of the .data section.*/
extern unsigned long __data_start__;   /*!< Start address for the .data section*/
extern unsigned long __data_end__;     /*!< End address for the .data section */
extern unsigned long __bss_start__;    /*!< Start address for the .bss section*/
extern unsigned long __bss_end__;      /*!< End address for the .bss section  */
extern void __end__;                   /*!< End address for ram               */


/*----------Function prototypes-----------------------------------------------*/
extern int main(void);           /*!< The entry point for the application.    */
extern void SystemInit(void);    /*!< Setup the microcontroller system(CMSIS) */
void Reset_Handler(void);   /*!< Default reset handler                */
static void Default_Handler(void);  /*!< Default exception handler            */


__attribute__((section(".vectors")))
void (* const vectors[])(void) =
{
  /*----------Core Exceptions------------------------------------------------ */
  (void *)&Stack_Pointer[STACK_SIZE],     /*!< The initial stack pointer         */
  Reset_Handler,             /*!< Reset Handler                               */
  NMI_Handler,               /*!< NMI Handler                                 */
  HardFault_Handler,         /*!< Hard Fault Handler                          */
  MemManage_Handler,         /*!< MPU Fault Handler                           */
  BusFault_Handler,          /*!< Bus Fault Handler                           */
  UsageFault_Handler,        /*!< Usage Fault Handler                         */
  0,0,0,0,                   /*!< Reserved                                    */
  SVC_Handler,               /*!< SVCall Handler                              */
  DebugMon_Handler,          /*!< Debug Monitor Handler                       */
  0,                         /*!< Reserved                                    */
  PendSV_Handler,            /*!< PendSV Handler                              */
  SysTick_Handler,           /*!< SysTick Handler                             */
  
  /*----------External Exceptions---------------------------------------------*/
  WWDG_IRQHandler,           /*!<  0: Window WatchDog                         */
  PVD_IRQHandler,            /*!<  1: PVD through EXTI Line detection         */
  TAMP_STAMP_IRQHandler,     /*!<  2: Tamper and TimeStamps through the EXTI line*/
  RTC_WKUP_IRQHandler,       /*!<  3: RTC Wakeup through the EXTI line        */
  FLASH_IRQHandler,          /*!<  4: FLASH                                   */
  RCC_IRQHandler  ,          /*!<  5: RCC                                     */
  EXTI0_IRQHandler,          /*!<  6: EXTI Line0                              */
  EXTI1_IRQHandler,          /*!<  7: EXTI Line1                              */
  EXTI2_IRQHandler,          /*!<  8: EXTI Line2                              */
  EXTI3_IRQHandler,          /*!<  9: EXTI Line3                              */
  EXTI4_IRQHandler,          /*!< 10: EXTI Line4                              */
  DMA1_Stream0_IRQHandler,   /*!< 11: DMA1 Stream 0                           */
  DMA1_Stream1_IRQHandler,   /*!< 12: DMA1 Stream 1                           */
  DMA1_Stream2_IRQHandler,   /*!< 13: DMA1 Stream 2                           */
  DMA1_Stream3_IRQHandler,   /*!< 14: DMA1 Stream 3                           */
  DMA1_Stream4_IRQHandler,   /*!< 15: DMA1 Stream 4                           */
  DMA1_Stream5_IRQHandler,   /*!< 16: DMA1 Stream 5                           */
  DMA1_Stream6_IRQHandler,   /*!< 17: DMA1 Stream 6                           */
  ADC_IRQHandler,            /*!< 18: ADC1, ADC2 and ADC3s                    */
  CAN1_TX_IRQHandler,        /*!< 19: CAN1 TX                                 */
  CAN1_RX0_IRQHandler,       /*!< 20: CAN1 RX0                                */
  CAN1_RX1_IRQHandler,       /*!< 21: CAN1 RX1                                */
  CAN1_SCE_IRQHandler,       /*!< 22: CAN1 SCE                                */
  EXTI9_5_IRQHandler,        /*!< 23: External Line[9:5]s                     */
  TIM1_BRK_TIM9_IRQHandler,  /*!< 24: TIM1 Break and TIM9                     */
  TIM1_UP_TIM10_IRQHandler,  /*!< 25: TIM1 Update and TIM10                   */
  TIM1_TRG_COM_TIM11_IRQHandler,/*!< 26: TIM1 Trigger and Commutation and TIM11*/
  TIM1_CC_IRQHandler,        /*!< 27: TIM1 Capture Compare                    */
  TIM2_IRQHandler,           /*!< 28: TIM2                                    */
  TIM3_IRQHandler,           /*!< 29: TIM3                                    */
  TIM4_IRQHandler,           /*!< 30: TIM4                                    */
  I2C1_EV_IRQHandler,        /*!< 31: I2C1 Event                              */
  I2C1_ER_IRQHandler,        /*!< 32: I2C1 Error                              */
  I2C2_EV_IRQHandler,        /*!< 33: I2C2 Event                              */
  I2C2_ER_IRQHandler,        /*!< 34: I2C2 Error                              */
  SPI1_IRQHandler,           /*!< 35: SPI1                                    */
  SPI2_IRQHandler,           /*!< 36: SPI2                                    */
  USART1_IRQHandler,         /*!< 37: USART1                                  */
  USART2_IRQHandler,         /*!< 38: USART2                                  */
  USART3_IRQHandler,         /*!< 39: USART3                                  */
  EXTI15_10_IRQHandler,      /*!< 40: External Line[15:10]s                   */
  RTC_Alarm_IRQHandler,      /*!< 41: RTC Alarm (A and B) through EXTI Line   */
  OTG_FS_WKUP_IRQHandler,    /*!< 42: USB OTG FS Wakeup through EXTI line     */
  TIM8_BRK_TIM12_IRQHandler, /*!< 43: TIM8 Break and TIM12                    */
  TIM8_UP_TIM13_IRQHandler,  /*!< 44: TIM8 Update and TIM13                   */
  TIM8_TRG_COM_TIM14_IRQHandler,/*!< 45:TIM8 Trigger and Commutation and TIM14*/
  TIM8_CC_IRQHandler,        /*!< 46: TIM8 Capture Compare                    */
  DMA1_Stream7_IRQHandler,   /*!< 47: DMA1 Stream7                            */
  FSMC_IRQHandler,           /*!< 48: FSMC                                    */
  SDIO_IRQHandler,           /*!< 49: SDIO                                    */
  TIM5_IRQHandler,           /*!< 50: TIM5                                    */
  SPI3_IRQHandler,           /*!< 51: SPI3                                    */
  UART4_IRQHandler,          /*!< 52: UART4                                   */
  UART5_IRQHandler,          /*!< 53: UART5                                   */
  TIM6_DAC_IRQHandler,       /*!< 54: TIM6 and DAC1&2 underrun errors         */
  TIM7_IRQHandler,           /*!< 55: TIM7                                    */
  DMA2_Stream0_IRQHandler,   /*!< 56: DMA2 Stream 0                           */
  DMA2_Stream1_IRQHandler,   /*!< 57: DMA2 Stream 1                           */
  DMA2_Stream2_IRQHandler,   /*!< 58: DMA2 Stream 2                           */
  DMA2_Stream3_IRQHandler,   /*!< 59: DMA2 Stream 3                           */
  DMA2_Stream4_IRQHandler,   /*!< 60: DMA2 Stream 4                           */
  ETH_IRQHandler,            /*!< 61: Ethernet                                */
  ETH_WKUP_IRQHandler,       /*!< 62: Ethernet Wakeup through EXTI line       */
  CAN2_TX_IRQHandler,        /*!< 63: CAN2 TX                                 */
  CAN2_RX0_IRQHandler,       /*!< 64: CAN2 RX0                                */
  CAN2_RX1_IRQHandler,       /*!< 65: CAN2 RX1                                */
  CAN2_SCE_IRQHandler,       /*!< 66: CAN2 SCE                                */
  OTG_FS_IRQHandler,         /*!< 67: USB OTG FS                              */
  DMA2_Stream5_IRQHandler,   /*!< 68: DMA2 Stream 5                           */
  DMA2_Stream6_IRQHandler,   /*!< 69: DMA2 Stream 6                           */
  DMA2_Stream7_IRQHandler,   /*!< 70: DMA2 Stream 7                           */
  USART6_IRQHandler,         /*!< 71: USART6                                  */
  I2C3_EV_IRQHandler,        /*!< 72: I2C3 event                              */
  I2C3_ER_IRQHandler,        /*!< 73: I2C3 error                              */
  OTG_HS_EP1_OUT_IRQHandler, /*!< 74: USB OTG HS End Point 1 Out              */
  OTG_HS_EP1_IN_IRQHandler,  /*!< 75: USB OTG HS End Point 1 In               */
  OTG_HS_WKUP_IRQHandler,    /*!< 76: USB OTG HS Wakeup through EXTI          */
  OTG_HS_IRQHandler,         /*!< 77: USB OTG HS                              */
  DCMI_IRQHandler,           /*!< 53: DCMI                                    */
  CRYP_IRQHandler,           /*!< 53: CRYP crypto                             */
  HASH_RNG_IRQHandler,       /*!< 53: Hash and Rng                            */
  FPU_IRQHandler,            /*!< 53: FPU                                     */
  UART7_IRQHandler,
  UART8_IRQHandler,
  SPI4_IRQHandler,
  SPI5_IRQHandler,
  SPI6_IRQHandler,
  SAI1_IRQHandler,
  LTDC_IRQHandler,
  LTDC_ER_IRQHandler,
  DMA2D_IRQHandler
};


/**
  * @brief  This is the code that gets called when the processor first
  *         starts execution following a reset event. Only the absolutely
  *         necessary set is performed, after which the application
  *         supplied main() routine is called.
  * @param  None
  * @retval None
  */
void Reset_Handler(void)
{
  //Copy .data section from FLASH to SRAM
  unsigned long *pSrc, *pDst;
  
  pSrc = &__text_end__;

  for(pDst = &__data_start__; pDst < &__data_end__; )
  {
    *(pDst++) = *(pSrc++);
  }
  
  /* Zero fill the bss segment.  This is done with inline assembly since this
     will clear the value of pulDest if it is not kept in a register. */
  __asm("  ldr     r0, =__bss_start__\n"
        "  ldr     r1, =__bss_end__\n"
        "  mov     r2, #0\n"
        "  .thumb_func\n"
        "zero_loop:\n"
        "    cmp     r0, r1\n"
        "    it      lt\n"
        "    strlt   r2, [r0], #4\n"
        "    blt     zero_loop");
#ifdef __FPU_USED
  /* Enable FPU.*/ 
  __asm("  LDR.W R0, =0xE000ED88\n"
        "  LDR R1, [R0]\n"
        "  ORR R1, R1, #(0xF << 20)\n"
        "  STR R1, [R0]");
#endif	

  /* Call the application's entry point.*/
  main();
}

/**
  * @brief  This is the code that gets called when the processor receives an
  *         unexpected interrupt.  This simply enters an infinite loop,
  *         preserving the system state for examination by a debugger.
  * @param  None
  * @retval None
  */
static void Default_Handler(void)
{
	/* Go into an infinite loop. */
	while (1)
	{
	}
}

/*********************** (C) COPYRIGHT 2009 Coocox ************END OF FILE*****/
