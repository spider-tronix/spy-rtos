    PRESERVE8
	THUMB
    AREA    |.text|, CODE, READONLY
 
int_disable  PROC
	 EXPORT  int_disable
		 MRS R0,PRIMASK	       ; Save old status
		 CPSID I    		       ; mask all(except faults)
		 BX LR 
         ENDP

int_enable  PROC
	 EXPORT  int_enable
		 MSR PRIMASK,R0
         BX LR 
		 ENDP
		 END	 