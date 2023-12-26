var x, y, z : integer;

procedure f11(); var x : integer; begin x := 99 end;

procedure f12(); begin x := 99 end;

procedure f13();
   procedure f21(); begin y := 99 end;
   procedure f22(); begin f21() end;
begin
   f22()
end;

procedure f14();
   procedure f21(); var y : integer; begin y := 99 end;
   procedure f22(); begin f21() end;
begin
   f22()
end;

procedure f15();
   procedure f21(); begin y := 99 end;
   procedure f22(); begin f21() end;
begin
   f21()
end;

procedure f16();
   procedure f21(); begin z := 88 end;
   procedure f22();
      procedure f31(); begin z := 99 end;
      procedure f32(); begin f21() end;
   begin f32() end;
   procedure f23(); begin f22() end;
begin
   f23()
end;

procedure f17();
   procedure f21(); begin z := 88 end;
   procedure f22();
      procedure f31(); begin z := 99 end;
      procedure f32(); begin f31() end;
   begin f32() end;
   procedure f23(); begin f22() end;
begin
   f23()
end;

procedure f18();
   procedure f21(); begin z := 88 end;
   procedure f22();
      procedure f31(); begin z := 99 end;
      procedure f32(); var z : integer; begin f21() end;
   begin f32() end;
   procedure f23(); begin f22() end;
begin
   f23()
end;

procedure f19();
   procedure f21(); var z : integer; begin z := 88 end;
   procedure f22();
      procedure f31(); begin z := 99 end;
      procedure f32(); begin f21() end;
   begin f32() end;
   procedure f23(); begin f22() end;
begin
   f23()
end;

{ procedure newline(); begin writeln('') end; }
procedure newline(); var nl: char; begin nl := 10; write(nl) end;

begin
   x:=11; y:=22; z:=33; f11(); write(x); write(y); write(z); newline();
   x:=11; y:=22; z:=33; f12(); write(x); write(y); write(z); newline();
   x:=11; y:=22; z:=33; f13(); write(x); write(y); write(z); newline();
   x:=11; y:=22; z:=33; f14(); write(x); write(y); write(z); newline();
   x:=11; y:=22; z:=33; f15(); write(x); write(y); write(z); newline();
   x:=11; y:=22; z:=33; f16(); write(x); write(y); write(z); newline();
   x:=11; y:=22; z:=33; f17(); write(x); write(y); write(z); newline();
   x:=11; y:=22; z:=33; f18(); write(x); write(y); write(z); newline();
   x:=11; y:=22; z:=33; f19(); write(x); write(y); write(z); newline();
end
.
