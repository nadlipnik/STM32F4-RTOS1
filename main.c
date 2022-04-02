/***************************************************************************//**
*  \file       main.c
*
*  \details    LED Blinking using RTX CMSIS V2 RTOS 
*
*  \author     EmbeTronicX
*
*  \Tested with Proteus
*
* *****************************************************************************/ 
#include "RTE_Components.h"
#include  CMSIS_device_header
#include "cmsis_os2.h"
#include "stm32f4xx.h"

 
/*
** This thread will turns ON and turns OFF the PORT-D LEDs with 1second delay.
**
**  Arguments:
**      arg  -> Argument of this thread. osThreadNew()'s 2nd arg has to come here. 
**   
*/
__NO_RETURN static void LED_Blink_PortD( void *arg ) 
{
  (void)arg;                            //unused variable
  //set Port D as output
	__HAL_RCC_GPIOD_CLK_ENABLE();
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pin = GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
  
  for (;;)                              //infinite for loop
  {
    //Turn ON the first LED
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);
    osDelay(1000);                      //1sec delay
    //Turn ON the second LED
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_SET);
    osDelay(1000); 
		//Turn ON the third LED
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);
    osDelay(1000); 
		//Turn ON the fourth LED
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);
    osDelay(1000); 
		//Turn OFF the all LED
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15, GPIO_PIN_RESET);
    osDelay(1000);
  }
}

/*
** This thread will turns ON and turns OFF the PORT-E LEDs with 3second delay.
**
**  Arguments:
**      arg  -> Argument of this thread. osThreadNew()'s 2nd arg has to come here. 
**   
*/
__NO_RETURN static void LED_Blink_PortE( void *arg ) 
{
  (void)arg;                            //unused variable
  //set Port E as output
  GPIOE->MODER = 0x55555555;
  for (;;)                              //infinite for loop
  {
    //Turn ON the LED of Port-E
    GPIOE->BSRR = 0x0000FFFF;
    osDelay(10000);                      //3sec delay
    //Turn OFF the LED of Port-E
    GPIOE->BSRR = 0xFFFF0000;
    osDelay(10000);                      //3sec delay
  }
}

/*
** main function
**
**  Arguments:
**      none
**   
*/ 
int main (void) 
{
  //Enable the AHB clock all GPIO Port-D
  SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIODEN);
  //Enable the AHB clock all GPIO Port-E
  SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOEEN);
  
  // System Initialization
  SystemCoreClockUpdate();
 
  osKernelInitialize();                       // Initialize CMSIS-RTOS
  osThreadNew(LED_Blink_PortD, NULL, NULL);   // Create application main thread
  osThreadNew(LED_Blink_PortE, NULL, NULL);   // Create application main thread
  osKernelStart();                            // Start thread execution
  for (;;) 
  {
    //Dummy infinite for loop.
  }
}
