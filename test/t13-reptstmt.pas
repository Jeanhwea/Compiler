var x, y: integer;
procedure newline(); var nl : char; begin nl := 10; write(nl) end;

begin

   x := 1;
   repeat x := x*2 until x > 100;
   write(x);
   newline();

   y := 1;
   repeat y := y + 1 until y > 0;
   write(y);
   newline();


   x := 1; y := 10;
   repeat
   begin
      x := 2 * x;
      y := y + 1
   end
   until x > y;
   write(x);
   newline();
   write(y);
   newline();

end.
