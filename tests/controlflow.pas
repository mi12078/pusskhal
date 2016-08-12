program fibonaci;
(*stampa prvih dvadeset clanova fibonacijevog niza*)

var
	i:integer;
	first,second,third:integer;

begin
	first := 1;
	second := 1;
	writeln(first);
	writeln(second);
	for i:=0 to 20 do
		begin
			third := first + second;
			first := second;
			second := third;
			writeln(third);
			if i=10-3 then
				writeln('10th element reached')
		end
end.
