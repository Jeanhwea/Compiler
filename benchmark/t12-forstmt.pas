var i, j: integer;

procedure newline();
var nl : char;
begin
   nl := 10;
   write(nl)
end;

begin

   i := 999;
   for i := 1 to 3 do write(i);
   write(i);
   newline();

   i := 999;
   for i := 3 downto 1 do write(i);
   write(i);
   newline();

   i := 999;
   for i := 1 to 1 do write(i);
   newline();

   i := 999;
   for i := 3 downto 3 do write(i);
   newline();

   i := 999;
   for i := 3 to 1 do write(i);
   newline();

   i := 999;
   for i := 1 downto 3 do write(i);
   newline();

   for i := 1 to 3 do
   begin
      write('x');
      write('y')
   end;
   newline();

   for i := 1 to 3 do
   begin
      for j := 1 to 3 do
        begin
            write(i+j);
        end;
   end;
   newline();

end.
