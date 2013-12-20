const	a='A',
	z='z';
var i: char;
begin
	{test for char}
	for i := a to z do
	begin
		write("ascii code -> ", i+0);
		write("symbol     -> ", i  );
	end;
	read(i);
	write(i);
	read(i);
	write(i)
end.