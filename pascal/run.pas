var x: integer;

procedure newline(); begin writeln('') end;
{ procedure newline(); var nl: char; begin nl := 10; write(nl) end; }

begin
   x := 1;
   if x > 0 then
      ;
   write(x);

   if x > 0 then
      x := 2;

   write(x)
end
.
