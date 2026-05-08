# Compilador y flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

# Regla por defecto: quitamos bt_sin_poda.o de aquí
all: AR.o bt.o tests_unitarios_AR tests_unitarios_BT tiempos_AR tiempos_BT

# Archivos objeto
AR.o: AR.cpp AR.h
	$(CXX) $(CXXFLAGS) -c AR.cpp -o AR.o

# bt.o ahora contiene tanto la versión con poda como sin poda
bt.o: bt.cpp bt.h
	$(CXX) $(CXXFLAGS) -c bt.cpp -o bt.o

# Ejecutables de tests unitarios
tests_unitarios_AR: tests_unitarios_AR.cpp AR.o
	$(CXX) $(CXXFLAGS) tests_unitarios_AR.cpp AR.o -o tests_unitarios_AR

# CORREGIDO: tests_unitarios_BT ahora solo depende de bt.o (que tiene todo) y AR.o
tests_unitarios_BT: tests_unitarios_BT.cpp bt.o AR.o
	$(CXX) $(CXXFLAGS) tests_unitarios_BT.cpp bt.o AR.o -o tests_unitarios_BT

# Ejecutables de medición de tiempos
tiempos_AR: tiempos_AR.cpp AR.o
	$(CXX) $(CXXFLAGS) tiempos_AR.cpp AR.o -o tiempos_AR

# CORREGIDO: tiempos_BT ahora solo depende de bt.o y AR.o
tiempos_BT: tiempos_BT.cpp bt.o AR.o
	$(CXX) $(CXXFLAGS) tiempos_BT.cpp bt.o AR.o -o tiempos_BT

# Limpiar archivos compilados
clean:
	rm -f *.o tests_unitarios_AR tests_unitarios_BT tiempos_AR tiempos_BT