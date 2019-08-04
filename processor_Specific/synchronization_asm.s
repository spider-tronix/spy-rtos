    PRESERVE8
	THUMB
    AREA    |.text|, CODE, READONLY
 
start_critical  PROC
	 EXPORT  start_critical
		 MRS R0,PRIMASK	       ; Save old status
		 CPSID I    		       ; mask all(except faults)
		 BX LR 
         ENDP

end_critical  PROC
	 EXPORT  end_critical
		 MSR PRIMASK,R0
         BX LR 
		 ENDP
		 END	 