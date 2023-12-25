var x, y, z: integer;
procedure newline(); var nl: char; begin nl := 10; write(nl) end;
function add(x, y : integer): integer; begin add := x + y; end;
function sub(x, y : integer): integer; begin sub := x - y; end;

begin
   x := 1; y := 2;
   write(add(x,y)); newline();
   write(sub(x,y)); newline();

   z := add(x,y);
   write(z); newline();
   z := sub(x,y);
   write(z); newline();
end.
