procedure prn();
	var he: array[10] of integer;
		i,j:integer;
	procedure swap(var i,j:integer);
		var temp:integer;
		begin temp:=i;i:=j;j:=temp end;

	begin
	he[0]:=1;he[1]:=3;he[2]:=2;he[3]:=4;he[4]:=5;
	for i:=0 to 4 do
		for j:=0 to 4 do
			if he[i]>he[j] then swap(he[i],he[j]) ;
	i:=0;
	repeat
	begin
	he[i]:=he[i]+1;
	i:=i+1;
	end
	until he[i]=4;
	for i:=0 to 4 do
		write(he[i]);
	end;
begin prn();  end.

{result: 6}
{result: 4}
{result: 3}
{result: 2}
{result: 1}

