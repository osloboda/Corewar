.name "Banana killer"
.comment "Am I?"

start:	sti r1, %:live, %1	;change live by the right value
		ld	%4, r3			;load step into r3

read:
live:	live %1
		ldi	%:start, r2, r4	;load code into r4
		add	r2, r3, r2		;increment r2
		sti	r4, %:end, r2	;put code ahead
		and	r2, %64, r5	    ;if (!r5) {carry = 1}
		zjmp %:read			;if (carry)
		fork %17
		ld	%0, r2			;reset r2, carry = 1
		zjmp %:start		;if (carry)
end:	aff	r2
