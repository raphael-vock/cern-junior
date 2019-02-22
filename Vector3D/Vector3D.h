#include <array>
#include <string>
#include <memory>

struct Dimension_contents{// defines the struct on which Dimension will point to
	std::string unit = "";// e.g. "m", "m/s", "eV", etc. By default, adimensional.
	double tolerance = 1e-3;// small positive number beneath which objects of this type are considered zero
};

typedef std::shared_ptr<Dimension_contents> Dimension;


class Vector3D{
	private:
		double x;
		double y;
		double z;
		Dimension dimension = default_dim;
	public:
		void setCoords(double a, double b, double c);// intialise instance of Vector3D to the given coords

		std::array<double,3> getCoords(void) const;// return coords in an array

		void print(void) const;// print coords in console

		Vector3D opp(void) const;// returns the additive inverse

		Vector3D operator*(const double &) const;// scalar multiplication. Note that the scalar comes AFTER the vector (i.e. u*lambda). We define lambda*u as a non-member operator

		Vector3D operator+(const Vector3D &) const;// vector addition

		Vector3D operator-(const Vector3D &) const;// vector subtraction

		double operator|(const Vector3D &) const;// dot product

		Vector3D operator^(const Vector3D &) const;// cross product

		double norm2(void) const;// returns square of Euclidian norm

		double norm(void) const;// returns Euclidian norm

		bool is_zero(void) const;// returns true iff square of norm is less than the tolerance specified by the vector's dimension  

		bool operator ==(const Vector3D &) const;// returns true iff argument and "this" differ by a "zero" vector

		Vector3D unitary() const;// returns the unit vector in the same direction
};

Vector3D operator*(const double &, const Vector3D&);// scalar multiplication, with the scalar coming BEFORE

double mixed_prod(const Vector3D &, const Vector3D &, const Vector3D &);// returns mixed product of (u,v,w) i.e. u|(v^w);
