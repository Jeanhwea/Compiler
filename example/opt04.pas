const a = 3;
var x, y, z :integer;
begin
   x := 1;
   y := 2;

   if x > a then
   begin
      y := y + 1;
      z := a;
      write(x);
   end
   else y := y + 2;

   y := 2 * y;
   write(y);
end.
