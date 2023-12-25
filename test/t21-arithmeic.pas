const a = 3;
var x, y, z: integer;
procedure newline(); var nl : char; begin nl := 10; write(nl) end;

begin
   write(3+2); newline();
   write(2+3); newline();
   write(3-2); newline();
   write(2-3); newline();
   write(3*2); newline();
   write(2*3); newline();
   write(3/2); newline();
   write(2/3); newline();
   write("------"); newline();

   write(a+2); newline();
   write(2+a); newline();
   write(a-2); newline();
   write(2-a); newline();
   write(a*2); newline();
   write(2*a); newline();
   write(a/2); newline();
   write(2/a); newline();
   write("------"); newline();

   x := 3; y := 2;
   write(x+y); newline();
   write(y+x); newline();
   write(x-y); newline();
   write(y-x); newline();
   write(x*y); newline();
   write(y*x); newline();
   write(x/y); newline();
   write(y/x); newline();
   write("------"); newline();

   x := 3; y := 2;
   z:=x+y; write(z); newline();
   z:=y+x; write(z); newline();
   z:=x-y; write(z); newline();
   z:=y-x; write(z); newline();
   z:=x*y; write(z); newline();
   z:=y*x; write(z); newline();
   z:=x/y; write(z); newline();
   z:=y/x; write(z); newline();
   write("------"); newline();
end.
