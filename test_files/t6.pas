var i0:integer;
procedure h1(var i:integer);
	var i1:integer;
	procedure h2(var j:integer);
		var i2:integer;
		procedure h3(var k:integer);
			var i3:integer;
			procedure h4(var x:integer);
				var i4:integer;
				procedure h5(var y:integer);
					var i5:integer;
					procedure h6(var z:integer);
					var i6:integer;
					begin i1:=6;i2:=6;i3:=6;i4:=6;i5:=6;i6:=6;write(i1);write(i2);write(i3);write(i4);write(i5);write(i6); end;
				begin i1:=5;i2:=5;i3:=5;i4:=5;i5:=5;write(i1);write(i2);write(i3);write(i4);write(i5); h6(i5) end;
			begin i1:=4;i2:=4;i3:=4;i4:=4; write(i1);write(i2);write(i3);write(i4); h5(i4)  end;
		begin i1:=3;i2:=3;i3:=3;write(i1);write(i2);write(i3);h4(i3);end;
	begin i1:=2;i2:=2;write(i1);write(i2); h3(i2); end;
begin  i1:=1; write(i1); h2(i1); end;
begin h1(i0) end.
{122333444455555666666}
