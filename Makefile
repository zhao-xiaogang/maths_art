ifndef T
A=-all
endif

run :: math_art
	./math_art $A

math_art : pic.hpp core.hpp body.hpp main.cc
	g++ -Wall main.cc -lm -o math_art

clean ::
	rm -f math_art *.bmp *.ppm
