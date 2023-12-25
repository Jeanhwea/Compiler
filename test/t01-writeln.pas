const a = 1, b = 2, c = 3;

procedure writeln(x : integer);
var newline : char;
begin
   write(x);
   newline := 10;
   write(newline)
end;

begin
   writeln(a);
   writeln(b);
   writeln(c)
end.
