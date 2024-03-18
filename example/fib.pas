function fib(n : integer ): integer; begin
   if n <= 2 then
      fib := 1
   else
      fib := fib(n-1) + fib(n-2);
end;

begin
   write(fib(4));
end
.
