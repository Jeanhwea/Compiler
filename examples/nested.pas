var ans : integer;
function func01(x : integer ) : integer;
   function func02(y : integer ) : integer;
      function func03(z : integer ) : integer;
      begin
         func03 := z + 3
      end;
   begin
      func02 := func03(y) + 2
   end;
begin
   func01 := func02(x) + 1
end;
begin
   ans := func01(0);
   write(ans)
end.
