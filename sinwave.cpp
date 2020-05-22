#include <iostream>
#include <vector>
#include <complex>
#include "Signal.h"


int main( int argc, char** argv )
{

	Wave wave( atoi(argv[1]), atoi(argv[2]) );

	wave.sinwave( atof(argv[3]), 100, 3 );

	wave.write( argv[4] );

	return 0;

}


