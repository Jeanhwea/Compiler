program dupconst;
const a:integer = 1;
procedure p1();
	const a:integer = 2;
	begin writeln(a) end;
begin p1() end.
