program ctrlflow;
var
	a,b:integer;

begin
	a := 4;
	if a>2 then
		b:=2;
	writeln(b);

	if a<5 then
		b:=3;
	writeln(b);

	if a=4 then
		b:=10;
	writeln(b);

	if a<5 then
		if a>2 then
			if a=4 then
				b:=11;
	writeln(b);

	if a<5 then
		b:=4
	else
		b:=6;
	writeln(b);

	for a:=0 to 10 do
		begin
			for b:=10 downto 0 do
				writeln(a+b);
		end
end.
