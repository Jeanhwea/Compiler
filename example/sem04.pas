var u, v, ans: integer;
function f1(): integer;
  begin
     f1 := 3
  end;
function f2(x, y : integer): integer;
  begin
     f2 := x + y
  end;
function f3(var x, y : integer): integer;
  begin
     f3 := x + y
  end;
begin
   u := 1; v := 2;
   ans := f1(u, v);
   ans := f2(u+v, v);
   ans := f3(u+v, v)
end.
