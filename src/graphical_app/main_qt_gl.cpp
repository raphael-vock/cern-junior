#include <QMainWindow>
#include <QApplication>
#include <vector>
#include <cmath>

#include "glwidget.h"

#include "accelerator.h"

using namespace std;

using namespace phcst;
using namespace vctr;

int main(int argc, char* argv[]){
	QApplication a(argc, argv);

	GLWidget w(nullptr);

	/* w.addQuadrupole(Vector3D(3, 2, 0), Vector3D(3, 1, 0), 0.1, 1.2); */
	/* w.addStraightSection(Vector3D(3, 1, 0), Vector3D(3, 0, 0), 0.1); */
	/* w.addQuadrupole(Vector3D(3, 0, 0), Vector3D(3, -1, 0), 0.1, -1.2); */
	/* w.addStraightSection(Vector3D(3, -1, 0), Vector3D(3, -2, 0), 0.1); */
	/* w.addDipole(Vector3D(3, -2, 0), Vector3D(2, -3, 0), 0.1, 1, 5.89158); */
	/* w.addQuadrupole(Vector3D(2, -3, 0), Vector3D(1, -3, 0), 0.1, 1.2); */
	/* w.addStraightSection(Vector3D(1, -3, 0), Vector3D(0, -3, 0), 0.1); */
	/* w.addQuadrupole(Vector3D(0, -3, 0), Vector3D(-1, -3, 0), 0.1, -1.2); */

	/* w.addStraightSection(Vector3D(-1, -3, 0), Vector3D(-2, -3, 0), 0.1); */

	/* w.addDipole(Vector3D(-2, -3, 0), Vector3D(-3, -2, 0), 0.1, 1, 5.89158); */
	/* w.addQuadrupole(Vector3D(-3, -2, 0), Vector3D(-3, -1, 0), 0.1, 1.2); */
	/* w.addStraightSection(Vector3D(-3, -1, 0), Vector3D(-3, 0, 0), 0.1); */
	/* w.addQuadrupole(Vector3D(-3, 0, 0), Vector3D(-3, 1, 0), 0.1, -1.2); */
	/* w.addStraightSection(Vector3D(-3, 1, 0), Vector3D(-3, 2, 0), 0.1); */
	/* w.addDipole(Vector3D(-3, 2, 0), Vector3D(-2, 3, 0), 0.1, 1, 5.89158); */
	/* w.addQuadrupole(Vector3D(-2, 3, 0), Vector3D(-1, 3, 0), 0.1, 1.2); */
	/* w.addStraightSection(Vector3D(-1, 3, 0), Vector3D(0, 3, 0), 0.1); */
	/* w.addQuadrupole(Vector3D(0, 3, 0), Vector3D(1, 3, 0), 0.1, -1.2); */
	/* w.addStraightSection(Vector3D(1, 3, 0), Vector3D(2, 3, 0), 0.1); */
	/* w.addDipole(Vector3D(2, 3, 0), Vector3D(3, 2, 0), 0.1, 1, 5.89158); */

	/* w.addParticle(Vector3D(2.99), Vector3D(0, -2.64754e8, 0), 1.67012416e-27, 1.602e-19, 0.1); */

	/* Une particule : */
	/* position : 2.99 0 0 */
	/* vitesse  : 0 -2.64754e+08 0 */
	/* gamma    : 2.13158 */
	/* energie (GeV) : 2 */
	/* masse   (GeV/c^2) : 0.938272 = 1.67012416e-27 kg*/
	/* charge   : 1.60217653e-19 */
	/* force    : 0 0 0 */

	w.addQuadrupole(Vector3D(0,0,0), Vector3D(4,0,0), 1.0, 1.0);

	w.addDipole(Vector3D(4,0,0), Vector3D(6,2,0), 1.0, -0.5, -0.12);
	w.addDipole(Vector3D(6,2,0), Vector3D(4,4,0), 1.0, -0.5, -0.12);

	/* w.addRadiofrequencyCavity(Vector3D(4,4,0), Vector3D(2,4,0), 1.0, 0.0, 0.05, 0.5, 0.2, 0.0); */
	/* w.addStraightSection(Vector3D(2,4,0), Vector3D(0,4,0), 1.0); */
	w.addQuadrupole(Vector3D(4,4,0), Vector3D(0,4,0), 1.0, 1.0);

	w.addDipole(Vector3D(0,4,0), Vector3D(-2,2,0), 1.0, -0.5, -0.12);
	w.addDipole(Vector3D(-2,2,0), Vector3D(0,0,0), 1.0, -0.5, -0.12);

	w.weld();

	w.addParticle(Vector3D(0,0,0), Vector3D(2,0,0), 0.5, 3.9855, 0.1, RGB::YELLOW);

	w.print(cout);

	w.show();

	return a.exec();
}
