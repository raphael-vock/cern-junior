#pragma once

#include <iostream>

#include "element.h"

class Accelerator : public Drawable{
	protected:
		std::vector<std::unique_ptr<Element>> element_list; // (ordered) list of elements that make up the accelerator
		std::shared_ptr<double> time;
	public:
		Accelerator(Canvas* canvas = nullptr) : Drawable(canvas), time(std::make_shared<double>(0.0)){}

		void draw_elements(void) const{ for(auto &e : element_list) e->draw(); }

		void addParticle(Vector3D r, Vector3D v, double mass, double charge, double radius);
		void addStraightSection(Vector3D start, Vector3D end, double radius);
		void addDipole(Vector3D start, Vector3D end, double radius, double curvature, double B_0);
		void addQuadrupole(Vector3D start, Vector3D end, double radius, double curvature, double b);

		virtual void draw(void) override{ canvas->draw(*this); }

		std::ostream& print(std::ostream& output);

		virtual void evolve(double dt) override;
};

std::ostream& operator<<(std::ostream& output, const Accelerator &A);
