program ProgramName;
var vn, out: integer;
function fac(n:integer): integer;
begin
	if n=1 then
	begin
		fac := 1
	end
	else
	begin
		fac := fac(n-1) * n
	end;
end;
begin
	vn := 3;
	write(fac(vn))
end.

