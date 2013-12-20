const a='a', m='m',z='z',A='A',M='M',Z='Z',w='w',e='e',F='F', II='I';
var c1,c2:char;
    i1,i2,i3:integer;
    ordc1,i:integer;
   
begin
 for i:=1 to 2 do
 begin
   if i=1 then 
     begin
       c1:=w;
       c2:=e;
       i1:=1;
       i2:=2
 {
	
 	read(c1, c2);
 	read(i1, i2)
}
     end;  
   if i=2 then 
     begin
       c1:=F;
       c2:=II;
       i1:=3;
       i2:=5
       {
 		read(c1, c2);
 	read(i1, i2)
 }
     end;
   if c1>=a then
     if c1<=m then
       begin
         ordc1 := c1-a+97;
         write(" The ASCII of c1 is ",ordc1)
       end
     else
       write(" The first letter is after m ")
   else
     if c1>=A then
       if c1<=M then     
         begin 
           ordc1 := c1-A+65;
           write(" The ASCII of c1 is ",ordc1)
         end
       else
         write(" The first letter is after M ")
     else
       write(" The letter you input is invalid ");
   if c1<=c2 then
     i3:=(a*i1+m*i2)/(a+m)
   else
     i3:=(a*i2+m*i1)/(a-m);
   write(" The result is: ",i3)
  end
end.