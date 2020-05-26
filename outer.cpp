#include "Signal.h"
#include "la.h"

int main()
{
	
	const double PI = 3.141592653589793238463;
	const double PI2 = PI * 2.0;
	
	double framerate = 11025.0;

	Vector<double> ts;
	for( double t=0.0; t <1.0; t += 1.0/framerate)
		 ts.push_back(t);
		
	Vector<double> fs;
	for( double t=0.0; t <1.0; t += 1.0/framerate)
		 fs.push_back(t);
		
	auto args = ts.outer(fs);


	/*
	auto M = args;
	M.func( [&]( double x ){ return std::cos( PI2 * x); } );
	
	auto ys = M * amps;
	*/


	/*
	Wave wav( framerate, 16 );	
	wav.setsignal(ys, 100.0);	
	wav.write( "quad-tone-cpp.wav" );
	*/

}


