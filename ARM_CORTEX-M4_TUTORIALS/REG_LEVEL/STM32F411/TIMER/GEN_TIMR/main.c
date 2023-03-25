/*

 TIMER3 & TIMER4(16-BIT) ,TIMER2 & TIMER5 [32-BIT] ARE THE GENERAL PURPOSE TIMERS,


THESE TIMERS ARE CONNECTED BY APB1 BUS, LETS USE TIMER5,
PRESCALAR IS 16 BIT, IE IT CAN BE SET AS A MAX OF 2^16, thus to get a 1 ms delay we use prescalr of 1600 =>10,000
AFTER THAT WE DIVIDE IT BY AUTO RELOAD REGISTER TO 10,000
*/


#include "stm32f4xx.h"                  // Device header

void timer_init(void)
{
	//	TIM5->CR1=(1<<0);
	TIM5->CR1=1;     //ENABLES THE COUNTER, IT IS NECESSARY TO MAKE THE COUNT	
}

void timer5_init(void)
{
	RCC->APB1ENR = 1<<3;// PROVIDES THE CLOCK TO TIMER5
	
	TIM5->PSC = 1600-1;   // THUS 16000000/1600 -> 10,000
	
	TIM5->ARR = 10000-1;//(10000-1) IS CORECT VALUE, SINCE START IS FROM ZERO  
                      // THIS REG 'ARR' ALSO ACT AS SIMLAR FUNCTION TO PRESCALAR, REFFER DATASHEET
	                      // 10000/10000 ->1 HZ ( 1 COUNT FOR 1 SEC)
	
	TIM5->CNT = 0;       //COUNT START ON ZERO
}

void delayS(int n)
{
	while(n)
	{
	while(!(TIM5->SR&0x0001)){} //WAIT TILL COUNT IS COMPLETE
		//??
		
	TIM5->SR&=(~1); //RESETTING THE FLAG TO ZERO,	
	n--;
	}
}
void gpio_init()
{
	
	RCC->AHB1ENR |= 1<<3;         //ENABLING D PORT(BY PROVIDING CLOCK)
	//AHB1ENR:REGISTER TO ENBLE PORTS 
 
  GPIOD->MODER |= 1<<28;             //SETTING THE CONFIGURATION 01, FOR OUTPUT.
	//MODER:REGISTER TO SET THE PINS AS OUTPUT
	
}	
 
int main(){
	
	timer5_init();
	timer_init();
	gpio_init();
	
	while(1)
	{
	GPIOD->ODR ^= 1<<14;
		
	delayS(1)	;
		
	}
}
