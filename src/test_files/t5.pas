procedure sa();
procedure pri();
var he: array [10] of integer;
pe:array [10] of integer;
i,j:integer;

function f(n:integer):integer;
begin if n<3 then f:=n else f:=n*f(n-1) end;

procedure prr();
begin he[1]:=2;he[he[1]]:=2;pe[he[1]]:=he[he[1]]; write(pe[he[1]]);i:=i+j end;

begin prr();write(f(6) / pe[he[1]]); end;
begin pri() end;

procedure prn();
var he:integer;
procedure fe(var i:integer);
begin i:=22; end;
begin fe(he); write(he) end;

begin sa(); prn() end.

{result: 2}
{result: 360}
{result: 22}
