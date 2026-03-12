all: test_unitarios test_oraculo tiempos

tiempos: tiempos.cpp dyv.o
	g++ -g -O2 tiempos.cpp dyv.o -o tiempos

test_unitarios: test_unitarios.cpp dyv.o
	g++ -g -Wall -O2 test_unitarios.cpp dyv.o -o test_unitarios

test_oraculo: test_oraculo.cpp dyv.o
	g++ -g -Wall -O2 test_oraculo.cpp dyv.o -o test_oraculo

dyv.o: dyv.cpp dyv.hpp
	g++ -g -Wall -O2 -c dyv.cpp

clean:
	rm -f *.o test_unitarios test_oraculo tiempos *.pdf resultados.csv