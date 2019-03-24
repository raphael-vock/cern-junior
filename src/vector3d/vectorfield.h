#include <functional>

#include "../general/drawable.h"
#include "../general/canvas.h"
#include "vector3d.h"

typedef std::function<Vector3D(const Vector3D &)> vector_function;

class VectorField : Drawable{
	private:
		vector_function F;
	public:
		VectorField(Canvas* display, vector_function f) : Drawable(display), F(f){}
		virtual void draw(void) override{ canvas->draw(*this); }

		// overload of call operator
		Vector3D operator()(const Vector3D &x) const;
		
		std::ostream& print(std::ostream &stream) const;
};
