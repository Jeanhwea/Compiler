var u, v, ans: integer;
function p1(x, y : integer): integer;
  function p2(x, y : integer): integer;
    begin p2 := x + y end;
  begin
     p1 := p2(x, y)
  end;
begin
   ans := p1(u, v)
end.
