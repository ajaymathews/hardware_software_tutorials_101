#include "stm32f4xx.h"                  // Device header




/********************** 1ST METHOD **************************/

void systickdelayMs(int n)
{
	SysTick->LOAD=16000; //load with no of clock, ie for 16000max value for 16mhz, 
	                    //thus for each 16000 count takes 1 ms
	SysTick->VAL=0; //clear current value reg
	SysTick->CTRL=0x5;
	 for(int i=0;i<n;i++)
	{
		while((SysTick->CTRL & 0x10000)==0){}  //wait till the count reach  16000, and for that it takes 1 ms
			                                    //0x10000 is equal to 16000 in decimal
	}
	SysTick->CTRL=0;
}




/******************** 2ND METHOD USING INTERRUPT ********************/


volatile uint32_t tick;              //THIS VARIABLE MUSTBE VOLATILE,BCZ, VOLATILE VALUE CAN BE
                                    //CHNGED WITHOUT CHNGING IT IN CODE.ALSO VARIBLES USED IN AN 
									// INTRRPT HANDLER ALSO SHOULB BE A VOLATILE
volatile uint32_t _tick;           //TICK IS USED TO INCREMNT TICK, AND _TICK TO STORE THE TICK AT EACH GET VALUE,
                                   //AND PASSSED THUS I ANYCASE THE ORIGINAL TICK IS NOT AFFECTED


void SysTick_Handler(void){          //THIS FUNCTION EXISTS ON ALL CORTEX M SERIES

	++tick;                           //TICK IS INCREMENTED AT EACH SYSTICK INTERRUPT
}                                  

uint32_t getTick(void){
	
	__disable_irq();                  //INTERRUPT IS DISABLED, BCZ DONT WANT ANY INTERRUPT TO EXECUTE IN THE MIDDLE,
	_tick=tick;                      //USING ANOTHER VARIABLE, SO THAT THE ORIGINAL TICK VARIABLE SHOULDNT BE ALTERED
	__enable_irq();                  //AFTER THE ASSIGNING, 
	
	return _tick;
}

void DelayS(uint32_t sec){
	
  sec*=100;                            //MULTIPLY IT WITH SECONDS TO GET THE MILLISECONDS
	uint32_t temp=getTick();            //GETTING THE VALUE OF TICK AT THE STARTING.
  while((getTick()-temp)<sec);       //THEDIFFRENCE B/W THE STARTING AND CURRENT TICK DIFFERNCE
                                    //	GIVES THE TICK TAKEN AFTER THE DELAY IS CALLED
   		                             //THE WHILE FUN WAIT TILL THE DIFERNCE IS GREATER THAN THE DELAY VALUE
}






/*********************** MAIN *********************/
int main()
{
	
}
