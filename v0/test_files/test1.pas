
{ *** todo
var i:integer;
procedure h1(var i:integer);
	procedure h2(var i:integer);
		procedure h3(var i:integer);
		begin i:=9 end;
	begin h3(i) end;
begin h2(i) end;
begin h1(i); write(i) end.
}
{result: 9}

{  *** todo
const ch='2';
var h:integer;
procedure he(var i:integer);
begin read(i) end;
begin he(h); h:=ch+1; write("h is:", h) end.
}

{greatest common divisor , recursive}
{ *** pass
var i,j:integer;
function gcd(i,j:integer):integer;
begin
if i=j then gcd:=i;
if i>j then gcd:=gcd(i-j,j);
if i<j then gcd:=gcd(i,j-i);
end;
begin i:=132; j:=1632; write(gcd(i,j)) end.
}
{result: 12}

{ *** todo
/////qsort
var a: array [10] of integer;
index,num,temp:integer;
procedure qsort(l,h:integer);
var i,j,t,m:integer;
	procedure swap(var i, j:integer);
	var temp:integer;
	begin temp:=i;i:=j;j:=temp end;

begin
	i:=l;
	j:=h;
	m:=a[(i+j) / 2];
	repeat
	begin
		if a[i]<m then repeat i:=i+1 until a[i]>=m;
		if m<a[j] then repeat j:=j-1 until m>=a[j];

		if i<=j then
		begin
		swap(a[i],a[j]);
		i:=i+1;
		j:=j-1;
		end;
	end
	until i>j;

	if j>l then qsort(l,j);
	if i<h then qsort(i,h);
end;

begin
write("please input num <10");
read(num);
write("please input number");
for index:=1 to num do begin read(temp); a[index-1]:=temp end;

qsort(0, num-1);
for index:=0 to num-1 do write(a[index]);
end.
}


