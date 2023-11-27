{greatest common divisor , recursive}
var i,j:integer;
function gcd(i,j:integer):integer;
begin
if i=j then gcd:=i;
if i>j then gcd:=gcd(i-j,j);
if i<j then gcd:=gcd(i,j-i);
end;
begin read(i,j); write(gcd(i,j)) end.