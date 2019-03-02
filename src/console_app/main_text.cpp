#include <iostream>
#include "text_viewer.h"
#include "content.h"
using namespace std;

int main(void){
	TextViewer screen(cout);

	Universe my_universe;
	my_universe.new_particle(0,0,0,0,0,0);

	Content content(&screen, my_universe);

	cout << "Initially:" << endl;
	content.draw();

	content.evolve(0.1);
	cout << "After one step:" << endl;
	content.draw();

	content.evolve(0.1);
	cout << "After two steps:" << endl;
	content.draw();

	return 0;
}
