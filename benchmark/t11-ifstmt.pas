var x: integer;

procedure newline();
var newline : char;
begin
   newline := 10;
   write(newline)
end;

begin

   x := 0;
   if x =  1 then writeln(0) else writeln(1); { 1 }
   if x <> 1 then writeln(2) else writeln(0); { 2 }
   if x >  1 then writeln(0) else writeln(3); { 3 }
   if x <  1 then writeln(4) else writeln(0); { 4 }
   if x >= 1 then writeln(0) else writeln(5); { 5 }
   if x <= 1 then writeln(6) else writeln(0); { 6 }

   newline();

   x := 1;
   if x =  1 then writeln(1) else writeln(0); { 1 }
   if x <> 1 then writeln(0) else writeln(2); { 2 }
   if x >  1 then writeln(0) else writeln(3); { 3 }
   if x <  1 then writeln(0) else writeln(4); { 4 }
   if x >= 1 then writeln(5) else writeln(0); { 5 }
   if x <= 1 then writeln(6) else writeln(0); { 6 }

end.
