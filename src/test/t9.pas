procedure ge();
var a:array [10] of integer;
b:array [10] of integer;
c:array [10] of integer;
index:integer;
final:integer;
begin 
for index:=0 to 9 do c[index]:=index;
for index:=0 to 9 do b[c[index]]:=index;
for index:=0 to 9 do a[b[c[index]]]:=index;
final:=c[5]*b[c[1]]+(a[b[c[2]]*c[2]])-b[2];
for index:=0 to 9  do write(a[index]);
write(final);
end;
begin ge() end.

{01234567897}
