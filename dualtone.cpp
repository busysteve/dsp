#include <iostream>
#include <vector>
#include <complex>
#include "Signal.h"


int main( int argc, char** argv )
{

	Wave wave( atoi(argv[1]), atoi(argv[2]) );

	int a=3;

	std::vector<double> freqs;

	for( ; a < argc-1; a++ )
	{
		freqs.push_back( atof(argv[a]) );
	}

	wave.sinwave( freqs, 100, 2 );

	wave.write( argv[a] );

	return 0;

}


