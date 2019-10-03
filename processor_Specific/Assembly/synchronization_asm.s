    PRESERVE8
	THUMB
    AREA    |.text|, CODE, READONLY
 
os_start_critical  PROC
	 EXPORT  os_start_critical
		 MRS R0,PRIMASK	       ; Save old status
		 CPSID I    		       ; mask all(except faults)
		 BX LR 
         ENDP

os_end_critical  PROC
	 EXPORT  os_end_critical
		 MSR PRIMASK,R0
         BX LR 
		 ENDP
		 END	 