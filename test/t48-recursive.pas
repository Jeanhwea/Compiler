var i: integer;

function fib(x : integer ): integer; begin
   if x <= 2 then
      fib := 1
   else
      fib := fib(x-1) + fib(x-2);
end;

{ procedure newline(); begin writeln('') end; }
procedure newline(); var nl: char; begin nl := 10; write(nl) end;

begin
   for i := 1 to 10 do
   begin
      write(fib(i));
      newline();
   end
end
.
