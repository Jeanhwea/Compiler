{ test for multi-level and display region disign}
var vn, out: integer;
procedure outter(y:integer);
	procedure foo(y:integer);
		procedure pcd(x:integer);
			var t: integer;
			function sum(var x:integer):integer;
				var t: integer;
				begin
					t := x-1;
					if x = 1 then 
						sum := 1
					else
						sum := sum(t)+x;
				end;
			begin
				t := x;
				out := sum(t)
			end;
		begin
			pcd(y)
		end;
	begin
		foo(y)
	end;
begin
	vn := 100;
	outter(vn);
	write(out) {expect output a number: 5050}
end.

