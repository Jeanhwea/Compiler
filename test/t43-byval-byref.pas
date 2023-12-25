var x, y: integer;
procedure newline(); var nl: char; begin nl := 10; write(nl) end;
procedure swap1(x, y :integer); var t: integer; begin t := x; x := y; y := t end;
procedure swap2(var x, y :integer); var t: integer; begin t := x; x := y; y := t end;

begin
   x := 1; y := 2;
   swap1(x,y);
   write(x); newline();
   write(y); newline();

   x := 1; y := 2;
   swap2(x,y);
   write(x); newline();
   write(y); newline();
end.
