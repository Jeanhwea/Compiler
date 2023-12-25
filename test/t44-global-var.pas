var ans, counter: integer;

function f1(x : integer): integer;
begin
   f1 := x + counter;
end;

procedure newline(); var nl: char; begin nl := 10; write(nl) end;

begin
   counter := 1;
   ans := f1(1);
   write(ans); newline();

   counter := 2;
   ans := f1(1);
   write(ans); newline();
end.
