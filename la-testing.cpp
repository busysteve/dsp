
#include <iostream>
#include <fstream>
#include <vector>
#include <complex>
#include <string>
#include <cstring>
#include <cmath>
#include <float.h>
#include "tnt/tnt.h"
#include <initializer_list>
#include "Signal.h"


using namespace std;


int main()
{

	double framerate = 11025;
	
	TNT::Matrix<double> amps(4,1), fs(4,1), ts(framerate,1);
	
	amps = { 0.6, 0.25, 0.1, 0.05 };
	
	fs = { 100.0, 200.0, 300.0, 400.0 };
	
	for( double i=0; i < framerate; i++ )
		ts[i][0] = i / framerate;
		
	Matrix<double> args = ts * fs;
	
	TNT::Matrix<double> M = args;
	
	for( int j=0; j < M.nr(); j++ )
		M[j][0] = std::cos( M[j][0] );
	
	Matrix<double> ys = matmult( M, amps );
	
	Wave wave( framerate, 16 );
	
	wave.set_sample( ys );
	
	wave.write( "la-sound.wav" );

}
