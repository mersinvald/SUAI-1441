{Y = (1 + C - 2A^2) / 2B^3}
{Y = (1 + 263 - 2*2^2) / 2*4^3}
{Y = (264 - 8) / 128}
{Y = 2}

{$MODE TP}
var A, B, C: byte;

begin
	writeln ('Input A B C');
	readln (A, B, C);
	
	{$ASMMODE intel}
	asm
		MOV AL,A
		MOV BL,B
		MOV CL,C
		
		CMP AL,BL
		JB @A_lower_B
		{ A >= B }
		CMP BL,CL
		JB @B_lower_C
		{ B >= C }
		MOV C,0
		JMP @exit

		@B_lower_C:
		{B < C}
		MOV B,0
		JMP @exit

		@A_lower_B:
		{ A < B }
		CMP AL,CL
                JB @A_lower_C
		{ A >= C }
                MOV C,0
		JMP @exit
		
                @A_lower_C:
		{ A < C }
                MOV A,0

		@exit:
	end;

	writeln ('A: ', A);
	writeln ('B: ', B);
	writeln ('C: ', C);
end.
