#pragma once

#include <QOpenGLShaderProgram> // shaders
#include <QMatrix4x4>

#include "../color/rgb.h"
#include "../vector3d/vector3d.h"

#include "glsphere.h"
#include "canvas.h"

class OpenGLView : public Canvas{
	private:
		// OpenGL shader in Qt class
		QOpenGLShaderProgram prog;
		GLSphere sphere;

		// Camera
		QMatrix4x4 pov_matrix;
	public:
		// to be a little more efficient
		void setShaderColor(const RGB &color);
		void setShaderPoint(const Vector3D &point);

		// drawing methods, inherited from Canvas
		virtual void draw(const Segment &to_draw) override;
		virtual void draw(const Particle &to_draw) override;
		virtual void draw(const Beam &to_draw) override;
		virtual void draw(const StraightSection &to_draw) override;
		virtual void draw(const MagneticElement &to_draw) override;
		virtual void draw(const ElectricElement &to_draw) override;
		virtual void draw(const Accelerator &to_draw) override;

		// initalization methods
		void init(void);
		void initializePosition(void);

		// setters
		void setProjection(QMatrix4x4 const& projection){ prog.setUniformValue("projection", projection); }
		void translate(double x, double y, double z);
		void rotate(double angle, double dir_x, double dir_y, double dir_z);

		// drawing
		void drawSphere(const Vector3D &x, double r, RGB color);

		void drawCylinder(const Vector3D &basepoint, const Vector3D &direction, double radius, const RGB &color = RGB::WHITE);

		void drawStraightElement(const Element &E, const RGB &color);
		void drawCurvedElement(const Element &E, const RGB &color);

		void drawElement(const Element &E, const RGB &color);
};
