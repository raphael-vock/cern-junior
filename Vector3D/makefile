output: Vector3D_test.o Dimension.o Vector3D.o
	g++ Vector3D_test.o Dimension.o Vector3D.o -o output

Vector3D_test.o: Vector3D_test.cpp
	g++ -c Vector3D_test.cpp

Dimension.o: Dimension.cpp Dimension.h
	g++ -c Dimension.cpp

Vector3D.o: Vector3D.cpp Vector3D.h
	g++ -c Vector3D.cpp

clean:
	rm *.o output
