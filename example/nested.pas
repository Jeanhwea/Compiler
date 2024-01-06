var x: integer;

procedure p1();
  var x: integer;
  procedure p2();
    var x: integer;
    begin
       x := 2
    end;
  begin
     x := 1;
     p2()
  end;

begin
   x := 0;
   p1()
end.
