# Compilador y flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

# Regla por defecto
all: AR.o bt.o comparador.o tests_unitarios_AR tests_unitarios_BT tiempos_AR tiempos_BT

AR.o: AR.cpp AR.h
	$(CXX) $(CXXFLAGS) -c AR.cpp -o AR.o

bt.o: bt.cpp bt.h
	$(CXX) $(CXXFLAGS) -c bt.cpp -o bt.o

comparador.o: comparador.cpp
	$(CXX) $(CXXFLAGS) -c comparador.cpp -o comparador.o

# Ejecutables de medición de tiempos
tiempos_AR: tiempos_AR.cpp AR.o
	$(CXX) $(CXXFLAGS) tiempos_AR.cpp AR.o -o tiempos_AR

tiempos_BT: tiempos_BT.cpp bt.o
	$(CXX) $(CXXFLAGS) tiempos_BT.cpp bt.o -o tiempos_BT

# Limpiar archivos compilados
clean:
	rm -f *.o tests_unitarios_AR tests_unitarios_BT tiempos_AR tiempos_BT
