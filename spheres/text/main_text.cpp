#include <iostream>
#include "text_viewer.h"
#include "content.h"
using namespace std;

int main(void){
	TextViewer screen(cout);
	Content c(&screen);
	c.draw();

	return 0;
}
