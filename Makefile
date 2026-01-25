msort.o: msort.cpp
	g++ -c msort.cpp

m3: m3.cpp
	g++ -c m3.cpp

testing_msort: msort.cpp m3.cpp
	g++ testing_msort.cpp msort.cpp m3.cpp -o testing_msort

clean:
	rm -f msort msort.o testing_msort msort3.o msort3
