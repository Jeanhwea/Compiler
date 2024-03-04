const a = 3;
var a, x, y :integer;
begin
   x := 1;
   y := 2;
   if x > 5 then
   begin
      y := y + 1;
      write(x);
   end
   else
   begin
      y := y + 2;
   end
   y := 2 * y;
   write(y);
end.
