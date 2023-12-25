var ans, base : integer;

function f1(x : integer ) : integer;
   function f2(y : integer ) : integer;
      function f3(z : integer ) : integer;
      begin
         f3 := z + base
      end;
   begin
      f2 := y + base + f3(3)
   end;
begin
   f1 := x + base + f2(2)
end;

procedure newline(); var nl: char; begin nl := 10; write(nl) end;

begin
   base := 1;
   ans := f1(1);
   write(ans); newline();

   base := 2;
   write(f1(1)); newline();

   base := 2;
   write(f1(2)); newline();
end.
