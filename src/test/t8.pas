procedure ge();
var a:array [10] of integer;
b:array [10] of integer;
c:array [10] of integer;
index:integer;

begin for index:=0 to 9 do c[index]:=index;
for index:=0 to 9 do b[c[index]]:=index;
for index:=0 to 9 do a[b[c[index]]]:=index;
for index:=0 to 9  do write(a[index])
end;

begin ge() end.
{0123456789}
