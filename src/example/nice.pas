program Nice; { bubble sort }
var a:array[0..5] of integer = (9, 4, 5, 2, 7, 0);
	i, j: integer;
procedure swap(var x,y:integer); { pass by address }
	var t: integer;
	begin
		t := x;
		x := y;
		y := t
	end;
begin { main }
	for i := 0 to 5 do
		for j := i to 5 do
			if a[i] > a[j] then
				swap(a[i], a[j]);
	for i := 0 to 5 do
		writeln(a[i])
end.
