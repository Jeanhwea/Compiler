{ test for multi-level and display region disign}
var vn, out: integer;
function fac(n:integer): integer;
begin
	if n=0 then
	begin
		fac := 1
	end
	else
	begin
		fac := fac(n-1) * n
	end;
end;
begin
	for vn := 0 to 4 do
	write(fac(vn))
end.
