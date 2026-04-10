/*
FROM THE 11 TIMERS IN ARM, SYSTICK TIMER IS A SEPERATE TIMER WHICH IS 24 BIT COUNTER. ie, FROM 0 TO 
(2^24)-1  [(2^24=16777215)], AND TIMER COUNTS FROM VALUETO ZERO, UPON REACHING ZERO INTERRUPT IS CALLED.
EACH TIMER VALUE IS INCREMNTED UPON EACH CLOCK. 

count value increments as the prescalar value and thus, when each count reaches a certain value
  led is toggled each task of different colour led is hndled simultaneously 
	*/

#include "kernel.h"
#define quanta 3                        //MEANS each 3 mS,systick interrupt is called
#include "stm32f4xx.h"                  // Device header

uint32_t count0,count1,count2;

#define dely 550000
#define RED (1<<14)               
#define RED_BIT (1<<28)          
#define GREEN (1<<12)
#define GREEN_BIT (1<<24)
#define BLUE (1<<15)
#define BLUE_BIT (1<<30)
#define GPIOD_CLOCK (1<<3)           

void GPIO_Init(){	
	RCC->AHB1ENR |= GPIOD_CLOCK;         
  GPIOD->MODER |= RED_BIT|GREEN_BIT|BLUE_BIT; 
} 
	                                 
void task0(void){
	while(1){	
	count0++;
																															
																															   if(count0>dely)
												
																																 {	count0=0;
																																		GPIOD->ODR ^= GREEN;}
																																	
	}
		                                                                
}

void task1(void){
while(1)
{	count1++;
																																									if(count1>dely)
																																										{	count1=0;
																																											GPIOD->ODR ^= BLUE;}
																																									
	}
}

void task2(void){
while(1)
{	count2++;
																																											if(count2>dely)
																																												{ count2=0;
																																													GPIOD->ODR ^= RED;  }
																																												
  }
}

int main(){
	GPIO_Init();
	kernelinit();
	kerneladdthreads(&task0,&task1,&task2);
	kernellaunch(quanta);
}
