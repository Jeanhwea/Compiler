var var1 : integer;
begin
read(var1);
if var1 = 0 then  
    write("var1 is 0!")  {No semicolon before an "Else" keyword}
else if var1 = 1 then 
begin
    write("var1 is 1!");
    {More code}
end  {No semicolon before an "Else" keyword}
else if var1 = 2 then 
begin
    write("var1 is 2!");
    {More code}
end  {No semicolon before an "Else" keyword}
else 
begin
    write("var1 is not 0, 1, or 2!");
    {More code}
end; 
end.