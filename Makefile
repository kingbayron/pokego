all: pokestop3v2menospesosin3opt
%: %.cc
	g++ -std=gnu++11 $< -o $@

%: %.c
	gcc $< -o  $@ -lm

