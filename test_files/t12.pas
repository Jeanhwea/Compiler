var i:integer;
procedure h1(var i:integer);
	procedure h2(var i:integer);
		procedure h3(var i:integer);
		begin i:=9 end;
	begin h3(i) end;
begin h2(i) end;
begin h1(i); write(i) end.

{result: 9}
