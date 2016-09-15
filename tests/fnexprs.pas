program fje_u_izrazima;
(*testira dodelu, jedan tip*)
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
end.
