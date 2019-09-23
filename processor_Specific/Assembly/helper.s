PRESERVE8
	THUMB
    AREA    |.text|, CODE, READONLY
 
os_get_highest_priority  PROC
	 EXPORT  os_leading_zeros
		 CLZ R0 , R0
		 BX LR
		 ENDP
END			 
		 