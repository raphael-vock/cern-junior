#pragma once

#include <iostream>

#include "element.h"

class Accelerator : public Drawable, private std::vector<std::unique_ptr<Element>>{
	protected:
		std::shared_ptr<double> time;

		const Vector3D origin;

		double length = 0.0;
	public:
		Accelerator(Canvas* canvas, Vector3D my_origin) : Drawable(canvas), time(std::make_shared<double>(0.0)), origin(my_origin){}

		Canvas* getCanvas(void) const{ return canvas; }

		// Prohibiting copies:
		Accelerator(const Accelerator &to_copy) = delete;
		Accelerator& operator=(const Accelerator &to_copy) = delete;

		// Masking the "deletion" operators to guarantee data integrity:
		void erase(iterator a) const{ throw excptn::ILLEGAL_ACCESS; }
		void erase(iterator a, iterator b) const{ throw excptn::ILLEGAL_ACCESS; }
		void clear(void){ throw excptn::ILLEGAL_ACCESS; }

		void weld(void);

		void draw_elements(void) const{ for(auto &e : *this) e->draw(); }

		double getLength() const{ return length; }

		void addParticle(Vector3D r, Vector3D v, double mass, double charge, double radius, const RGB &color = RGB::WHITE);

		void addStraightSection(double radius, const Vector3D &end);
		void addDipole(double radius, double curvature, double B_0, const Vector3D &end);
		void addQuadrupole(double radius, double b, const Vector3D &end);
		void addRadiofrequencyCavity(double radius, double curvature, double E_0, double omega, double kappa, double phi, const Vector3D &end);

		void addStraightSection(double radius){ addStraightSection(radius, origin); }
		void addDipole(double radius, double curvature, double B_0){ addDipole(radius, curvature, B_0, origin); }
		void addQuadrupole(double radius, double b){ addQuadrupole(radius, b, origin); }
		void addRadiofrequencyCavity(double radius, double curvature, double E_0, double omega, double kappa, double phi){ addRadiofrequencyCavity(radius, curvature, E_0, omega, kappa, phi, origin); }

		virtual void draw(void) override{ canvas->draw(*this); }

		void stitch(void);

		std::ostream& print(std::ostream& output, bool print_elements = false) const;

		virtual void evolve(double dt) override;

		Vector3D inverse_curvilinear_coord(double s) const;
};

std::ostream& operator<<(std::ostream& output, const Accelerator &A);
