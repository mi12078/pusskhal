program pozivfje;
(*poziv funkcije, prosledjivanje povratne vrednosti promenljivoj*)

var
	i:integer;

function sum(a:integer; b:integer) : integer;
begin
	sum := a + b
end;

begin
	i := sum(42, 69);
	writeln(i)
end.

