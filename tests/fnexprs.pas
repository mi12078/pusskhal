program fje_u_izrazima;
var
	a,b,c,d:integer;

function f(a:integer) : integer;
begin
	f := a+a
end;

begin
	a:=1;b:=1;c:=1;d:=2;
	writeln(a+f(b+f(c+f(d))));
	writeln(f(f(f(d)+c)+b)+a);
	(*Izraz ispod ne prolazi, nedovoljan broj registara*)
	(*writeln(a+f(b+f(c+f(d+d))));*)
end.
