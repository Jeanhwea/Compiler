var counter: integer;

function inc(x : integer): integer;
begin
   if x < 1 then x := 1;
   counter := counter + x;
   inc := counter;
end;

function id(): integer;
begin
   id := inc(1)
end;

{ procedure newline(); begin writeln('') end; }
procedure newline(); var nl: char; begin nl := 10; write(nl) end;

begin
   counter := 0;
   write(inc(0)); newline();
   write(id()); newline();
   write(inc(3)); newline();
end.
