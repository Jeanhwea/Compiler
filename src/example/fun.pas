{program bubble sort;}
var
	a:array[5] of integer {= (4, 5, 2, 7, 0)};
	i, j: integer;
function swap(var x:integer;var y:integer):integer;
	var
		t: integer;
	begin
		t := x + y;
		x := y;
		y := t;
		swap := t;
	end;
begin { main }
	for i := 1 to 5 do
	begin
		for j := i to 5 do
		begin
			if a[i] > a[j] then
			begin
				a[1] := swap(a[i], a[j])
			end;
		end;
	end;
	for i := 1 to 5 do
	begin
		write(a[i])
		{write(' ')}
	end
	{writeln()}
end.