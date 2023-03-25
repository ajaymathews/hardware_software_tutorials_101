		AREA |.text|, CODE, READONLY, ALIGN=2  ;DEFINING CODE AREA WHICH IS READONLY
		THUMB                               ;THUMB DIRECTIVE
		PRESERVE8                         ;directive, used to preserve8 by its alignment
		EXTERN currentptr                   ;DECLARING CURRENTPTR AS EXTERN
		EXPORT SysTick_Handler
		EXPORT SchedulerLaunch
		IMPORT schedular_round_robin     ;to chnge the current ptr assembly code into c code



;SYSTICK IS A PERIODIC INTERRUPT WITH PERIOD DETERMINED BY THE QUANTA
						    ;NEED TO SAVE 16 REGISTERS TO STACK BEFORE HANDLING SYSTICK EXCEPTION
SysTick_Handler             ;INVOKING SYSTICK HANDLER, SAVING R0,R1,R2,R3,R12,LR,PC,PSR [CONTEXT OF THREAD IS IN THESE REG]
	CPSID	I               ;DISBALING INTERRUPT
	PUSH	{R4-R11}        ;SAVING R4,R5,R6,R7,R8,R9,R10,R11
	LDR		R0,=currentptr  ;LOAD CURRENT POINTER IN .C FILE POINTING TO CURRENT TCB INTO R0
	LDR 	R1,[R0]         ;FROM R0 POINTING TO R1, R1=CURRENT_PTR
                            ;THUS WE HAVE SAVED ALL 16 EGISTERS, BUT NOT STACK POINTER REG
	STR		SP,[R1]         ;SAVING SP OF M-CORTEX TO SP OF THREAD
						    ;R1 = STACK POINTER WHICH ALSO HAS VALUE OF CURRENT PTR  
	
	;WE WANT TO IMPLEMENT THE BELOW LINE IN C LNG, THE THREAD SWITCHING TAKES PLACE THERE
	
	;LDR		R1,[R1,#4]      ;NEXT THREAD IS NEEDED FOR SCHEDULAR THUS 
						        ;#4 IS FOR 2ND ENTRY OF TCB, R1 = CURRENTPTR->NEXT
	;STR		R1,[R0]		    ;CURRENTPTR = R1	
	
	
	
	PUSH	{R0,LR}               ;RO TO LR
	BL		schedular_round_robin ;branch to roudrobin fun
	
	POP		{R0,LR} ;these lines are only in the code, not video
	LDR		R1,[R0] ;these lines are only in the code, not video
	
	LDR		SP,[R1]			;TO LAUNCH NEW THREAD SP NEDES TO BE UPDATED, SP =CURRENTPTR->STACKPTR
	POP     {R4-R11}        ;RESTORE ALL R4-R11
	CPSIE   I               ;ENABLED THE INTERRUPT
	
	BX      LR              ;SAVED 8 REGISTERS ARE RESTORED AUTOMATICALLY WHEN EXITING


SchedulerLaunch
	LDR		R0,=currentptr
	LDR		R2,[R0]  		;R2=currentptr
	LDR 	SP,[R2]	 		;SP=currentptr->stackptr
	POP		{R4-R11}        ;RESTORING REGISTERS
	POP		{R0-R3}
	POP		{R12}
	
	ADD		SP,SP,#4
	POP		{LR}
	ADD		SP,SP,#4
	CPSIE	I
	BX 		LR
	
		ALIGN
		END
	
	
	
	
	
	
	
	