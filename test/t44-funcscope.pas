var ans, counter: integer;

function f1(x : integer): integer;
begin
   f1 := x + counter;
end;

begin
   counter := 1;
   ans := f1(1);
   write(ans)
end.
