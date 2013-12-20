var i, j, N , t:integer;A:array[20] of integer;
	blank:char;
begin
	N := 5;
	for i:= 0 to N do
	begin
		write("enter a number -> ");
		read(j);
		A[i] := j
	end;
	for i:= 0 to N do 
		for j:= i to N do 
			if A[i] > A[j] then
			begin
				t := A[i];
				A[i] := A[j];
				A[j] := t
			end;
	blank := 20;
	write("after sorted");
	write(blank);
	for i:= 0 to N do
	begin
		write(A[i])
	end;	
end.