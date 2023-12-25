const a = 1, b = -4;
var x, y, z: integer;
procedure newline(); var nl : char; begin nl := 10; write(nl) end;

begin
   write(a); newline();
   write(b); newline();
   write(a+b); newline();

   x := 3; y := 4;
   z := (x + y) + (x + y);
   write(z); newline();
end.
