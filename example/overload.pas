var ans : integer;
function f(x : integer):integer; begin f := x end;
function f(x, y : integer ):integer; begin f := x + y end;
begin
   ans := f(1);
   write(ans);
   ans := f(3, 4);
   write(ans)
end.
