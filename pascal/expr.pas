const a = 1;
var x, y, z: integer;
procedure newline(); begin writeln('') end;

begin
   x := a + 2 + 3; write(x); newline();
   write(x+a); newline();
   write(a+x); newline();
   y := 2 + a - 9; write(y); newline();
   write(3*x); newline();
end.
