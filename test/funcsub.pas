const a = 1, b = 5;
var ans: integer;

function sub(x, y : integer):integer;
    begin
        sub := x - y
    end;

begin
   ans := sub(a,b);
   write("ans = ", ans)
end.
