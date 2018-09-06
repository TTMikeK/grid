#include <stdio.h>
#include "grid.h"

int main( int argc, char* argv[] ) {
	printf("Lets Go!\n");

	Grid<float> billy(6, 8);
	Grid<float> robby(billy);


	return 0;
}

