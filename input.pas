{ greatest common divisor, recursive }
function gcd(i, j:integer):integer;
begin
   if i=j then gcd:=i;
   if i>j then gcd:=gcd(i-j,j);
   if i<j then gcd:=gcd(i,j-i);
end;

begin
   write(gcd(1,1));
   write(gcd(16,18));
   write(gcd(1,2));
   write(gcd(2,1));
   write(gcd(234,122));
   write(gcd(1,4));
   write(gcd(4,3));
   write(gcd(12,3));
end.
