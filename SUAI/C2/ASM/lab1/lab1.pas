{Y = (1 + C - 2A^2) / 2B^3}
{Y = (1 + 263 - 2*2^2) / 2*4^3}
{Y = (264 - 8) / 128}
{Y = 2}

{$MODE TP}
var A, B: byte;
var Y, C: word;

begin
	writeln ('Input A B C');
	readln (A, B, C);
	
	{$ASMMODE intel}
	asm
		MOV AL,A
		MUL AL
		SHL AX,1
		MOV BX,C
		INC BX
		SUB BX,AX
		MOV AX,BX
	
		MOV BL,B

		DIV BL
		CBW 
		XOR BH,BH

		DIV BL	
		CBW
		XOR BH,BH

		DIV BL
		CBW
		XOR BH,BH
		SHR AX,1

		MOV Y,AX	
	end;

	writeln (Y);
	
end.
