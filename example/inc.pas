var counter: integer;

procedure inc1(x: integer); begin x := x + 1 end;
procedure inc2(var x: integer); begin x := x + 1 end;

begin
   counter := 0;
   inc1(counter);
   write(counter);
   inc2(counter);
   write(counter);
end.
