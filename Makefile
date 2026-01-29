msort.o: msort.cpp
	g++ -c msort.cpp

m3: m3.cpp
	g++ -c m3.cpp

tests: msort.cpp m3.cpp
	g++ testing_msort.cpp msort.cpp m3.cpp -o tests

clean:
	rm -f msort msort.o tests msort3.o msort3
