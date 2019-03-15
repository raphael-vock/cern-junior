#ifndef OPENGL_VIEW
#define OPENGL_VIEW

#include <QOpenGLShaderProgram> // shaders
#include <QMatrix4x4>

#include "../general/color.h"
#include "../vector3d/vector3d.h"
#include "glsphere.h"
#include "canvas.h"

class OpenGLView : public Canvas{
	public:
		// drawing methods, inherited from Canvas
		virtual void draw(const Content &to_draw) override;

		// initalization methods
		void init();
		void initializePosition();

		// setters
		void setProjection(QMatrix4x4 const& projection){
			prog.setUniformValue("projection", projection);
		}
		void translate(double x, double y, double z);
		void rotate(double angle, double dir_x, double dir_y, double dir_z);

		// some useful methods
		void drawAxes(QMatrix4x4 const& pov, bool is_in_color = true);
		void drawCube(QMatrix4x4 const& pov = QMatrix4x4(), RGB color = WHITE);
		void drawSphere(QMatrix4x4 const& point_de_vue, RGB color = WHITE);

	private:
		// OpenGL shader in Qt class
		QOpenGLShaderProgram prog;
		GLSphere sphere;

		// Camera
		QMatrix4x4 pov_matrix;
};

#endif
