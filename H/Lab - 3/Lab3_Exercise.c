#include <MKL25Z4.H>

__asm int my_sqrt(int x) {
	MOVS r4, #0x0			; a = 0
	LDR r5, =0xFFF			; b = 2^16
	LDR r6, =0xFFFFFFF		; c = -1
	
LOOP
	MOVS r7, r6				; c_old = c
	ADDS r6, r4, r5			; c = (a + b)
	LSRS r6, #0x1			; c = c / 2
	MOVS r2, r6				; r2 = c
	MULS r2, r2    			; r2 = c * c
	SUBS r2, r0             ; r2 = c * c - x
	BEQ ENDWHILE			; if(c * c == x) goto ENDWHILE
	BMI ELSEIF				; if(c * c < x) goto ELSEIF
	MOVS r5, r6				; if(c * c > x) b = c

WHILE_COND
	SUBS r1, r6, r7			; c != c_old
	BEQ ENDWHILE
	B LOOP
	
ELSEIF
	MOVS r4, r6				; a = c
	B WHILE_COND
		
ENDWHILE
	MOVS r0, r6             ; r0 = c (return calculated square root)
	BX lr
}

int my__sqrt(int x) {
	int done = 0, a = 0, b = 1<<16, c = -1, c_old;
	do {
		c_old = c;
		c = (a + b) / 2;
		if(c * c == x) done = 1;
		else if(c * c < x) a = c;
		else b = c;
	} while(!done && c != c_old);
	return c;
} 

int main(void) {
	volatile int r, j=0;
	r = my_sqrt(0); 		// should be 0
	r = my_sqrt(25); 		// should be 5
	r = my_sqrt(133); 		// should be 11		
	while (1);
}

// my_sqrt - 19 instructions
// my__sqrt - 30 instructions
