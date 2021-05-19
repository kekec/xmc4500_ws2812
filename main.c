/*
 * main.c
 *
 *  Created on: 2021 May 05 13:35:00
 *  Author: wiegelep
 */




#include "light_ws2812_cortex.h"
#include <xmc_gpio.h>
#include <xmc_scu.h>

#define TICKS_PER_SECOND 1000
#define DELAY_MS 2000
unsigned int volatile ticks=0;

typedef struct  { uint8_t g; uint8_t r; uint8_t b; } cRGB;
/**
 * @brief main() - Simple blinky with systick timer
 *
 * <b>Details of function</b><br>
 * This routine is the application entry point. It is invoked by the device startup code. 
 */

int main(void)
{

	XMC_SCU_CLOCK_SetSystemClockDivider(6);
	SystemCoreClockUpdate();
	uint32_t helper = 0;

	cRGB LED;
	cRGB* led = &LED;

	const XMC_GPIO_CONFIG_t pin_cfg = {
	  .mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL,
	  .output_level = XMC_GPIO_OUTPUT_LEVEL_LOW
	};
	XMC_GPIO_Init(P1_2,&pin_cfg);					/* init GPIO pin for WS2812 */
	XMC_GPIO_Init(P1_0,&pin_cfg);					/* init GPIO pin for to drive onboard led */

	SysTick_Config(SystemCoreClock / TICKS_PER_SECOND);

	while(1U)
	{
      if(ticks == DELAY_MS)
      {
        XMC_GPIO_ToggleOutput(P1_0);


        if(helper)
        {
          led[0].r=0;led[0].g=255;led[0].b=0;    // Write red to array
          ws2812_sendarray((uint8_t *)led,3);
        }
        else
        {
          led[0].r=0;led[0].g=0;led[0].b=0;    // Write red to array
          ws2812_sendarray((uint8_t *)led,3);
        }

        helper=~helper;
        ticks=0;
      }

	}
}

void SysTick_Handler(void)
{
	ticks++;
}
