{program bubble sort;}
var
   a:array[5] of integer {= (4, 5, 2, 7, 0)};
   i, j: integer;
procedure swap(var x,y:integer);
var
   t: integer;
begin
   t := x;
   x := y;
   y := t
end;
begin { main }
   a[0] := 4;
   a[1] := 5;
   a[2] := 2;
   a[3] := 7;
   a[4] := 0;
   for i := 0 to 4 do
   begin
      for j := i to 4 do
      begin
         if a[i] > a[j] then
         begin
            swap(a[i], a[j])
         end;
      end;
   end;
   for i := 0 to 4 do
   begin
      write(a[i])
   end
end.
