#include <iostream>
#include <vector>
#include <complex>
#include "Signal.h"


int main( int argc, char** argv )
{

	//Wave wave( atoi(argv[1]), atoi(argv[2]) );
	Wave wave;

	//wave.sinwave( atof(argv[3]), 100, 3 );

	wave.read( argv[1] );

	wave.write( argv[2] );

	return 0;

}


