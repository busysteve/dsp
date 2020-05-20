#include <iostream>
#include <vector>
#include <complex>
#include "Signal.h"


int main( int argc, char** argv )
{

	Wave wave;

	wave.sinwave( atof(argv[1]), 100, 5 );

	wave.write( argv[2] );

	return 0;

}


