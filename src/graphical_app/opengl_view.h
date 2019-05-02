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
		void setShaderPoint(const Vector3D &point);// TODO do we need this?

		// drawing methods, inherited from Canvas
		virtual void draw(const Segment &to_draw) override;
		virtual void draw(const Box &to_draw) override;
		virtual void draw(const Particle &to_draw) override;
		virtual void draw(const Beam &to_draw) override;
		virtual void draw(const Element &to_draw) override;
		virtual void draw(const Accelerator &to_draw) override;

		// initalization methods
		void init(void);
		void initializePosition(void);

		void set_third_person_view(const Particle &p);
		void set_first_person_view(const Particle &p);

		// setters
		void setProjection(QMatrix4x4 const& projection){ prog.setUniformValue("projection", projection); }
		void translate(double x, double y, double z);
		void translate(const Vector3D &x){ translate(x[0], x[1], x[2]); }
		void rotate(double angle, double dir_x, double dir_y, double dir_z);
		void rotate(double angle, const Vector3D &axis){ rotate(angle, axis[0], axis[1], axis[2]); }

		// runtime parameters
		bool matrix_mode = false;
		void toggle_matrix_mode(void){ matrix_mode = !matrix_mode; }

		// drawing
		void drawSphere(const Vector3D &x, double r);

		void drawCylinder(const Vector3D &basepoint, const Vector3D &direction, double radius);

		void drawStraightElement(const Element &E);
		void drawCurvedElement(const Element &E);
};
