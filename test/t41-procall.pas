procedure newline(); var nl: char; begin nl := 10; write(nl) end;

procedure say();
begin
   write("hello");
   newline();
end;

procedure sayx(x: char);
begin
   write("x = ", x);
   newline();
end;

begin
   say();
   sayx('b');
end.
