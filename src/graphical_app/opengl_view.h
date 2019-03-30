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
		virtual void draw(const Arrow &to_draw) override;
		virtual void draw(const Particle &to_draw) override;
		virtual void draw(const StraightSection &to_draw) override;
		virtual void draw(const Magnetic_element &to_draw) override;
		virtual void draw(const Electric_element &to_draw) override;
		virtual void draw(const Accelerator &to_draw) override;

		// initalization methods
		void init(void);
		void initializePosition(void);

		// setters
		void setProjection(QMatrix4x4 const& projection){
			prog.setUniformValue("projection", projection);
		}
		void translate(double x, double y, double z);
		void rotate(double angle, double dir_x, double dir_y, double dir_z);

		// drawing
		void drawSphere(QMatrix4x4 const& point_de_vue, RGB color = RGB::WHITE);
		void drawDisc(QMatrix4x4 const& pov = QMatrix4x4(), const RGB& color = RGB::WHITE, double radius = 1.0);
		void drawCylinder(QMatrix4x4 const& pov = QMatrix4x4(), const RGB& color = RGB::WHITE, double radius = 1.0, double lenght = 5.0);
		void drawTorus(QMatrix4x4 const& pov = QMatrix4x4(), const RGB& color = RGB::WHITE, int section = 10, double major_radius = 10.0, double minor_radius = 1.0);

                // draws a first model of a simple accelerator
		void drawBasicAccelerator(QMatrix4x4 const& pov = QMatrix4x4(), const RGB& color = RGB::WHITE, double major_radius = 10.0, double minor_radius = 1.0);
};
