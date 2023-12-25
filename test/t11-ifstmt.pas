var x, y: integer;
procedure newline(); var nl : char; begin nl := 10; write(nl) end;

begin

   x := 0;
   if 1 =  x then write(0) else write(1);
   if 1 <> x then write(2) else write(0);
   if 1 >  x then write(3) else write(0);
   if 1 <  x then write(0) else write(4);
   if 1 >= x then write(5) else write(0);
   if 1 <= x then write(0) else write(6);
   newline();

   x := 0;
   if x =  1 then write(0) else write(1);
   if x <> 1 then write(2) else write(0);
   if x >  1 then write(0) else write(3);
   if x <  1 then write(4) else write(0);
   if x >= 1 then write(0) else write(5);
   if x <= 1 then write(6) else write(0);
   newline();

   x := 1;
   if x =  1 then write(1) else write(0);
   if x <> 1 then write(0) else write(2);
   if x >  1 then write(0) else write(3);
   if x <  1 then write(0) else write(4);
   if x >= 1 then write(5) else write(0);
   if x <= 1 then write(6) else write(0);
   newline();

   x := 2;
   if x =  1 then write(0) else write(1);
   if x <> 1 then write(2) else write(0);
   if x >  1 then write(3) else write(0);
   if x <  1 then write(0) else write(4);
   if x >= 1 then write(5) else write(0);
   if x <= 1 then write(0) else write(6);
   newline();

   x := 0; y := 1;
   if x =  y then write(0) else write(1);
   if x <> y then write(2) else write(0);
   if x >  y then write(0) else write(3);
   if x <  y then write(4) else write(0);
   if x >= y then write(0) else write(5);
   if x <= y then write(6) else write(0);
   newline();

   x := 1; y := 1;
   if x =  y then write(1) else write(0);
   if x <> y then write(0) else write(2);
   if x >  y then write(0) else write(3);
   if x <  y then write(0) else write(4);
   if x >= y then write(5) else write(0);
   if x <= y then write(6) else write(0);
   newline();

   x := 2; y := 1;
   if x =  y then write(0) else write(1);
   if x <> y then write(2) else write(0);
   if x >  y then write(3) else write(0);
   if x <  y then write(0) else write(4);
   if x >= y then write(5) else write(0);
   if x <= y then write(0) else write(6);
   newline();

end.
