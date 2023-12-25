const a = 1;
var x: integer;
procedure newline(); var nl : char; begin nl := 10; write(nl) end;

begin
   x := a+2+3; write(x); newline();
   write(a+(2+3)); newline();
   write((6-3)-2); newline();
   write(6-(3-2)); newline();
   write((2*3)*5); newline();
   write(2*3*5); newline();
   write(2*(3*5)); newline();
   write(24/6/2); newline();
   write((24/6)/2); newline();
   write(24/(6/2)); newline();
end.
