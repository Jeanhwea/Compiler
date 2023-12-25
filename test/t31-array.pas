const c = 7;
var x : integer;  a: array[5] of integer;
procedure newline(); var nl: char; begin nl := 10; write(nl) end;

begin
   a[0] := 0;
   a[1] := 1;
   a[2] := 2;
   a[3] := 3;
   a[4] := 4;

   write(a[1]); newline();
   write(a[1]+a[3]); newline();

   x := a[2] * a[3];
   write(x); newline();

   x := a[3];
   a[3] := 0;
   write("x=", x); newline();

   x := a[3];
   write("x=", x); newline();
end.
