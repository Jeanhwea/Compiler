{ syntax test }
const 
	a = 1, 
	b = -3, 
	c = +28, 
	let = 'c', 
	nuh = '4';
var 
	v : integer;
	head, ch2:char; 
	q, p:integer; 
	Aint:array[3] of integer;
	Achar:array[5] of char;
{ pass by value}
function FunctionName1(funvar1, funvar2:char): integer;
begin
	A[0] := (funvar1 * funvar2 / 6 ) + 4;
	FunctionName1 := a * ( 4 + funvar2)
end;

procedure ProcedureName1();
	{ pass by reference }
	procedure ProcedureName2(var num:integer);
	const silly = -2, foo = 'p';
	begin end;
begin end;

function FunctionName2(var x, y: integer):char;
	var z:integer;
	function FunctionName3(): integer;
	begin { null statement } end;
	begin
		{ array assign }
		A[2] := - x + y;
		FunctionName2 := z - y 
	end;

{ main }
begin
	{ read test }
	read(p);
	read(p, q);
	ProcedureName1();
	{ if test }
	if head > 0 then
		write("yes")
	else
		write(head);
	{ normal assign }
	p := a * 9 / r;
	r := r - 4;
	{ for test }
	for i := 20 downto + 10 * a do
		sum := sum + i + pp;
	FunctionName2(pa,ra);
	for i := 1 to 10 do
		sum := sum * i;
	{ repeate test }
	repeat
		if head <= 4 then
			write (" head = ",head)
	until head <> 7
end.
