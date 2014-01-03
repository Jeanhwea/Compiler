const a1 = 1, u1 = '4', b1 = 3;
var x, y,g:integer; m:integer;
    i:integer;
    a,b:integer;
procedure swap();
  var temp:integer;
  begin
    temp:=x;
    x:=y;
    y:=temp
  end;
function mod(var fArg1,fArg2:integer):integer;
  begin
    fArg1:=fArg1-fArg1/fArg2*fArg2;
    mod:=fArg1
  end;
begin
  for i:=3 downto 1 do
  begin
   write("input x: ");
   read(x);
   write("input y: ");
   read(y);  
  
   x:=mod(x,y);
   write("x mod y = ",x);
   write("choice 1 2 3: ");
   read(g);
   if g = 1 then
        write("good ")
   else if g = 2 then
        write("better ")
   else  if g = 3 then
   		 write("best ")
  end
end.