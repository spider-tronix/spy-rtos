    PRESERVE8
	THUMB
    AREA    |.text|, CODE, READONLY
os_leading_zeros  PROC
	EXPORT  os_leading_zeros
    CLZ R0 , R0
	BX LR
	ENDP		 
os_dummy  PROC 
	EXPORT  os_dummy
	NOP
	BX LR
	ENDP
	END	