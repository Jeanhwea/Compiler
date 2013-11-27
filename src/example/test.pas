program ProgramName;
var vn, out: integer;
procedure pcd(x:integer);
	function sum( x:integer):integer;
		var t: integer;
		begin
			t := x-1;
			writeln(t);
			if x = 1 then 
				sum := 1
			else
				sum := sum(t)+x;
		end;
	begin
		out := sum(x);
		writeln(out)
	end;
begin
	vn := 3;
	pcd(vn);
	writeln(out)
end.

