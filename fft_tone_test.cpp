#include <iostream>
#include <vector>
#include <complex>
#include "Signal.h"


int main( int argc, char** argv )
{

	int min_mag = atoi(argv[2]);

	float duration = atof(argv[3]);

	Wave wave( atoi(argv[1]), 24 );

	int a=4;

	std::vector<double> freqs;

	for( ; a < argc-1; a++ )
	{
		freqs.push_back( atof(argv[a]) );
	}

	wave.sinwave( freqs, 100, duration );

	wave.write( argv[a] );


	auto result = wave.makeSpectrogram24Bit( wave.samps24, atoi(argv[1]) );
	

	{
		for( int i=0; i < result.frames.size(); i++ )
		{
			if( result.frames[i].binsDbFS.size() < 1 )
				continue;

			for( int j=0; j < result.frames[i].binsDbFS.size(); j++ )
			{
				if( result.frames[i].binsDbFS[j] > min_mag )
					std::cout << result.frequenciesHz[j] << " " << result.frames[i].binsDbFS[j] << std::endl;
			}

		}
		std::cout << std::endl;
	}


	return 0;

}


