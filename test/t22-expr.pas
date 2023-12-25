const a = 1;
var x, y, z: integer;
procedure newline(); var nl : char; begin nl := 10; write(nl) end;

begin
   x := a + 2 + 3; write(x); newline();
   write(x+a); newline();
   write(a+x); newline();
   write(1+a+x); newline();
   y := 2 + a - 9; write(y); newline();
   write(3*x); newline();
   z := a + 2 * 3; write(z); newline();
   z := 2 * 3 + 4; write(z); newline();
   write(z*z); newline();
end.
