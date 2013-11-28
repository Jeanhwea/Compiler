var k:integer;
procedure TestCase09(var k:integer);
var a,b:integer;
e, f:array [10] of integer;
begin	
	a:= 1;
	b:= 2;
	e[a]:=1;
	f[b]:=2;
	if e[a]>a then write(1) else write(2);
	if f[b]>=e[a] then write(3) else write(4);
	if e[a]=a then write(6) else write(7);
	if f[b]<>a then write(8) else write(9);
	if f[b]<a then write(10) else write(11);
	if b<=e[a] then write(12) else write(13);
	if e[a]<>a then write(13) else write(14);

end;
begin TestCase09(k) end.

{2368111314}
