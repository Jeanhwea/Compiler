var vn: integer;
    A:array[3] of integer;
procedure pcd(x,y:integer);
	var
		vn1, vn2, vn3: integer;
	procedure sec();
		procedure thr();
			begin

			end;
		begin
		end;
	procedure sec1();
		begin
			sec()
		end;
	begin
		vn2 := vn;
		vn2 := x;
		vn3 := 5;
		vn := vn2 + vn3;
		sec1();
		write(y);
	end;
begin
	vn := 1;
	A[1] := 8;
	write(A[vn]);
	pcd(4,vn)
end.

