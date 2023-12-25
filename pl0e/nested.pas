var ans, val : integer;
function func01(x : integer ) : integer;
   function func02(y : integer ) : integer;
      function func03(z : integer ) : integer;
      begin
         func03 := z + val
      end;
   begin
      func02 := y + val + func03(3)
   end;
begin
   func01 := x + val + func02(2)
end;
begin
   val := 1;
   ans := func01(1);
   write(ans)
end.
