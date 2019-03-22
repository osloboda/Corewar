.name "Banana killer"
.comment "Am I?"

start:	sti r1, %:live, %1	;change live by the right value
		sti r1, %:live2, %1	;change live by the right value
		sti r1, %:live3, %1	;change live by the right value
		ld	%0, r2			;set r2 to 0
		ld	%4, r3			;load step into r3

read:
live:	live %1
		ldi	%:start, r2, r4	;load code into r4
		add	r2, r3, r2		;increment r2
		sti	r4, %:end, r2	;put code ahead
		and	r2, %128, r5    ;if (!r5) {carry = 1}
		zjmp %:read			;if (carry)
live2:	live %1

		xor	r6, %0, r6		;if (!r6) {carry = 1}
		zjmp %:fork			;if (carry)
		ld	%0, r5			;carry = 1
live3:	live %1
		zjmp %:start		;if (carry)

fork:	fork %8
		ld	%1, r6			;disable fork
		ld	%0, r5			;carry = 1
        zjmp %:start		;if (carry)
end:	aff	r2
