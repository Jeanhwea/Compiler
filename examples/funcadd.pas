const a = 1, b = 3;
var sum: integer;

function add(x, y : integer):integer;
    begin
        add := x + y
    end;

begin
   sum := add(a,b);
   write(sum)
end.
