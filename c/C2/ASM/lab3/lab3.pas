{$MODE TP}
const 
N: byte = 5;

var 
A:array[1..10] of shortint;
i, r :byte;

begin
	writeln('Vvedite Massiv:');
	for i:=1 to N do	
		read(A[i]);

	r := 0;
	{$ASMMODE intel}
	asm
	MOV BL ,0      { Счетчик положительных чисел }

	XOR RCX, RCX   { Счетчик для цикла}
	MOV CL,N      

	MOV RSI,0      { Смещение в массиве }
	
	LEA RBP, A     { Адрес массива }

	@loop_point:
	MOV AL, [RBP+RSI] 
	INC RSI

	TEST AL, AL
	JS @exit

	INC BL 
	
	LOOP @loop_point
	
	@exit:
	MOV R, BL				
	end;
	
	writeln('Rezultat: ',R);
end.
