#include <iostream>
#include <vector>
#include <complex>
#include "Signal.h"


int main( int argc, char** argv )
{


	if( atoi(argv[1]) <= 1 )
	{


		float duration = atof(argv[3]);

		Wave wave( atoi(argv[2]), 24 );

		int a=4;

		std::vector<double> freqs;

		for( ; a < argc-atoi(argv[1]); a++ )
		{
			freqs.push_back( atof(argv[a]) );
		}

		wave.sinwave( freqs, 100, duration );

		
		if( atoi(argv[1]) == 0 )
			wave.raw_write();
		else if( atoi(argv[1]) == 1 )
			wave.write( argv[a] );
	}
	else if( atoi(argv[1]) == 2 )
	{
		int min_mag = atoi(argv[3]);
		float start = atof(argv[4]);
		float duration = atof(argv[5]);

		Wave wave( atoi(argv[2]), 24 );

		wave.raw_read( atoi(argv[2]), 24 );
	
		wave.slice( start, duration );

		auto result = wave.makeSpectrogram24Bit( wave.samps24, atoi(argv[2]));

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
	else if( atoi(argv[1]) == 3 )
	{
		int min_mag = atoi(argv[3]);
		float start = atof(argv[4]);
		float duration = atof(argv[5]);

		string inputfile = argv[6];

		Wave wave( atoi(argv[2]), 24 );

		wave.raw_read( inputfile, atoi(argv[2]), 24 );
	
		wave.slice( start, duration );

		auto result = wave.makeSpectrogram24Bit( wave.samps24, atoi(argv[2]));

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
	else if( atoi(argv[1]) == 4 )
	{
		Wave wave;

		wave.raw_read( atoi(argv[2]), 24 );

		std::cout << "\nDuration: " << wave.duration() << std::endl;
	}
	else
	{
		std::cout << "Usage: fft_tone_test [0|1|2|3] samplerate [freq1 freq2 ...] duration outputfile" << std::endl;
		std::cout << "       fft_tone_test 2 samplerate inputfile min_mag start duration" << std::endl;
		std::cout << "       fft_tone_test 3 samplerate inputfile min_mag start duration" << std::endl;
	}


	return 0;

}


