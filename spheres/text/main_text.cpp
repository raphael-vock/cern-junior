#include <iostream>
#include "text_viewer.h"
#include "content.h"
using namespace std;

int main(void){
	TextViewer screen(cout);
	Content c(&screen);

	cout << "Initially:" << endl;
	c.draw();

	c.evolve(0.1);
	cout << "After one step:" << endl;
	c.draw();

	c.evolve(0.1);
	cout << "After two steps:" << endl;
	c.draw();

	return 0;
}
