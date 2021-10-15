procedure pri();
function f(n:integer):integer;
begin if n<3 then f:=n else f:=n*f(n-1) end;
begin write(f(5)) end;
begin pri() end.

{result: 120}
