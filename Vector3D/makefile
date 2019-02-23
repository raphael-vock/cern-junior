output: Vector3D_test.o Dimension.o Vector3D.o
	g++ Vector3D_test.o Dimension.o Vector3D.o -o output
	@echo "Compiling executable..."

Vector3D_test.o: Vector3D_test.cpp
	g++ -c Vector3D_test.cpp
	@echo "Building main..."

Dimension.o: Dimension.cpp Dimension.h
	g++ -c Dimension.cpp
	@echo "Building Dimension..."

Vector3D.o: Vector3D.cpp Vector3D.h
	g++ -c Vector3D.cpp
	@echo "Building Vector3D..."

clean:
	rm *.o output
