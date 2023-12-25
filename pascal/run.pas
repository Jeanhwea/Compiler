var counter: integer;

function getid(): integer;
begin
   counter := counter + 1;
   getid := counter
end;

{ procedure newline(); var nl: char; begin nl := 10; write(nl) end; }
procedure newline(); begin writeln('') end;


begin
   counter := 0;

   write(getid()); newline();
   write(getid()); newline();
   write(getid()); newline();
   write(getid()); newline();

end.
