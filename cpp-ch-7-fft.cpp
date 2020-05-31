//#include <iostream>
//#include <fstream>
//#include <vector>
//#include <complex>
//#include <string>
//#include <cstring>
//#include <cmath>
//#include <float.h>
//#include "tnt/tnt.h"
//#include <initializer_list>
#include "Signal.h"
#include "la.h"


typedef std::complex<double> cx;


Matrix<cx> synthmatrix( double N )
{

	Vector<cx> ts, fs;
	
	ts.range( 0.0, N );
	ts /= N;
	
	fs.range( 0.0, N );
	
	Matrix<cx> M = ts.outer( fs );
	
	M.func( [=]( cx x )->cx { return std::exp( cx(0,1) * PI * x  ); }  );

	return M;

}

Vector<cx> dft( Vector<cx> &ys )
{
	double N = ys.size();
	Matrix<cx> M = synthmatrix(N);
	Vector<cx> amps;
	
	try
	{
		amps = M.func( [&]( cx x )-> cx { return std::conj( x); } ).transpose() * ys;
	}
	catch(linear_algebra_error e)
	{
		cout << e.what() << " in dtf()" << endl;
		throw e;
	}
		
		

	return amps;
}


Vector<double> synthtone( double framerate, double duration, Vector<double> &freqs, Vector<double> &amps )
{
	Vector<double> ts;
	for( double t=0.0; t < duration; t += duration/framerate)
		 ts.push_back(t);
		
	auto args = ts.outer(freqs);
	auto M = args;
	M.func( [&]( double x ){ return std::cos( PI2 * x); } );
	
	Vector<double> ys = M * amps;
	
	return ys;
}


int main()
{
	
	double N=4;
	
	Vector<double>  ts;
	Vector<double>  freqs;
	
	std::cout.precision(1);
	std::cout.setf( std::ios::fixed, std::ios::floatfield );
	
	
	ts.range( N );
	ts /= N;
	std::cout << ts << std::endl;
	
	
	freqs.range(N);
	std::cout << freqs << std::endl;
	
	auto args = ts.outer( freqs );
	//auto args = freqs.outer( ts );
	std::cout << args << std::endl;
	
	
	Matrix<cx> M;
	
	convert_matrix_copy< double, cx >( args, M );
	std::cout << M << std::endl;
	
	M.func( [&]( cx x )->cx { return std::exp( cx(0,1) * PI2 * x  ); }  );
	
	auto X = M;
	
	M = M.func( [&]( cx x )-> cx { return std::conj( x ); } ).transpose().mul( X );
	M.print() << std::endl;
	
	M.func( [=]( cx x )->cx { return x / N; } );
	M.print() << std::endl;
	

}




/*  Out put 

{0.0,0.2,0.5,0.8}
{0.0,1.0,2.0,3.0}
{{0.0,0.0,0.0,0.0},{0.0,0.2,0.5,0.8},{0.0,0.5,1.0,1.5},{0.0,0.8,1.5,2.2}}
{{(0.0,0.0),(0.0,0.0),(0.0,0.0),(0.0,0.0)},{(0.0,0.0),(0.2,0.0),(0.5,0.0),(0.8,0.0)},{(0.0,0.0),(0.5,0.0),(1.0,0.0),(1.5,0.0)},{(0.0,0.0),(0.8,0.0),(1.5,0.0),(2.2,0.0)}}
|(4.0,0.0)	(-0.0,0.0)	(0.0,0.0)	(0.0,0.0)|
|(-0.0,-0.0)	(4.0,0.0)	(-0.0,0.0)	(0.0,0.0)|
|(0.0,-0.0)	(-0.0,-0.0)	(4.0,0.0)	(-0.0,0.0)|
|(0.0,-0.0)	(0.0,-0.0)	(-0.0,-0.0)	(4.0,0.0)|

|(1.0,0.0)	(-0.0,0.0)	(0.0,0.0)	(0.0,0.0)|
|(-0.0,-0.0)	(1.0,0.0)	(-0.0,0.0)	(0.0,0.0)|
|(0.0,-0.0)	(-0.0,-0.0)	(1.0,0.0)	(-0.0,0.0)|
|(0.0,-0.0)	(0.0,-0.0)	(-0.0,-0.0)	(1.0,0.0)|



*/



