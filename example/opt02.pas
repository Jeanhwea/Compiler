var x, y, z, i :integer;
begin
   x := 1;
   y := x;

   for i := 1 to 10 do
   begin
      z := z * i + x + y
   end;

   z := z / 2
end
.
