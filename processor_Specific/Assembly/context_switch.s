    PRESERVE8
	THUMB
    AREA    |.text|, CODE, READONLY
	EXTERN current_tcb
	EXTERN new_high_tcb
os_first_task PROC
	EXPORT os_first_task
    CPSID   I                                                   
    LDR   R0, =0xE000ED22                                  
    LDR   R1, =0xFF
    STRB    R1, [R0]

    MOV32   R5, current_tcb
    MOV32   R1, new_high_tcb                                 
    LDR     R2, [R1]
    STR     R2, [R5]

    LDR     R0, [R2]                                            
    MSR     PSP, R0                                             

    MRS     R0, CONTROL
    ORR     R0, R0, #2
    MSR     CONTROL, R0
    ISB                                                         

    LDMFD    SP!, {R4-R11}                                      
    LDMFD    SP!, {R0-R3}                                       
    LDMFD    SP!, {R12, LR}                                     
    LDMFD    SP!, {R1, R2}                                      
    CPSIE    I
    BX       R1
	ENDP

		
os_context_switch PROC
	EXPORT os_context_switch
    LDR     R0, =0xE000ED04
    LDR     R1, =0x10000000   
    STR     R1, [R0]
    BX      LR
	ENDP

PendSV_Handler PROC
	EXPORT PendSV_Handler
    CPSID   I                                                   ; Prevent interruption during context switch
    MRS     R0, PSP                                             ; PSP is process stack pointer
    STMFD   R0!, {R4-R11}                                       ; Save remaining regs r4-11 on process stack

    MOV32   R5, current_tcb                                     ; OSTCBCurPtr->OSTCBStkPtr = SP;
    LDR     R6, [R5]
    STR     R0, [R6]                                            ; R0 is SP of process being switched out

                                                                ; At this point, entire context of process has been saved      

    MOV32   R1, new_high_tcb                                 ; OSTCBCurPtr = OSTCBHighRdyPtr;
    LDR     R2, [R1]
    STR     R2, [R5]
    LDR     R0, [R2]                                            ; R0 is new process SP; SP = OSTCBHighRdyPtr->StkPtr;
    LDMFD   R0!, {R4-R11}                                       ; Restore r4-11 from new process stack
    MSR     PSP, R0                                             ; Load PSP with new process SP
    CPSIE   I
    BX      LR 
    ENDP
    NOP		
    END
