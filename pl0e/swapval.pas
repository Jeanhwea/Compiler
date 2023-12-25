var u, v: integer;

procedure swap(var x, y : integer);
var t :  integer;
begin
   t := x;
   x := y;
   y := t
end;

begin
   u := 1;
   v := 2;
   swap(u, v);
   write("u=", u);
   write("v=", v)
end.
