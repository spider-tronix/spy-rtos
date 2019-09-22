PRESERVE8
	THUMB
    AREA    |.text|, CODE, READONLY
 
os_get_highest_priority  PROC
	 EXPORT  os_get_highest_priority
		 CLZ R0 , R0
		 BX LR
		 ENDP
END			 
		 