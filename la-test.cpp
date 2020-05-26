
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
#include "la.h"



template <typename T> int VectorTest()
{

	const double PI = 3.141592653589793238463;
	const double PI2 = PI * 2.0;
	
	{
		cout << "Vector tests:" << endl;

		Vector<T> v1( { (T)13.0, (T)-12.0, (T)2.0 } );
		Vector<T> v2( { (T)14.0, (T)15.0, (T)-3.0 } );
		T s1 = (T)23.0;
		
		
		cout << v1 << " dot " << v2 << " = " << v1.dot( v2 ) << endl;

		cout << v1 << " mul " << v2 << " = "  << v1.mul( v2 ) << endl;
		cout << v1 << " div " << v2 << " = "  << v1.div( v2 ) << endl;
		cout << v1 << " add " << v2 << " = "  << v1.add( v2 ) << endl;
		cout << v1 << " sub " << v2 << " = "  << v1.sub( v2 ) << endl;
		
		cout << v1 << " mul " << s1 << " = "  << v1.mul( s1 ) << endl;
		cout << v1 << " div " << s1 << " = "  << v1.div( s1 ) << endl;
		cout << v1 << " add " << s1 << " = "  << v1.add( s1 ) << endl;
		cout << v1 << " sub " << s1 << " = "  << v1.sub( s1 ) << endl;
		
		cout << v1 << " * " << v2 << " = "  << v1 * v2 << endl;
		cout << s1 << " * " << v2 << " = "  << s1 * v2 << endl;
		cout << v1 << " * " << s1 << " = "  << v1 * s1 << endl;

		cout << v1 << " / " << v2 << " = "  << v1 / v2 << endl;
		cout << s1 << " / " << v2 << " = "  << s1 / v2 << endl;
		cout << v1 << " / " << s1 << " = "  << v1 / s1 << endl;

		cout << v1 << " + " << v2 << " = "  << v1 + v2 << endl;
		cout << s1 << " + " << v2 << " = "  << s1 + v2 << endl;
		cout << v1 << " + " << s1 << " = "  << v1 + s1 << endl;

		
		cout << v1 << " - " << v2 << " = "  << v1 - v2 << endl;
		cout << s1 << " - " << v2 << " = "  << s1 - v2 << endl;
		cout << v1 << " - " << s1 << " = "  << v1 - s1 << endl;
		cout << v1 << " negated = "  << -v1 << endl;
		
		
		
		Vector<T> v3( 3, (T)1.0 );
		Vector<T> v4( 4, (T)2.0 );
		
		cout << v3.dot( v4 ) << endl;
	}

	{
		
		cout << endl << "Matrix * Matrix tests:" << endl;
		
		Matrix<T> mA( {	{ 5.0, 34.0, -28.0 },
				{ 8.0, -83.4, 71.7 },
				{ 92.6, 23.3, 9.2 } }	
				);
		
		Matrix<T> mB( {	{ 56.0, 26.0, 4.3 },
				{ 6.5, 33.4, 5.6 }, 
				{ 8.4, 1.9, 2.3 } } 
				);
				
		Matrix<T> mC( {	{ 5.0, 34.0, -28.0 },
				{ 8.0, -83.4, 71.7 },
				{ 83.4, 4.3, 71.7 },
				{ 92.6, 23.3, 9.2 } }	
				);

		try{
			cout << mA << " + " << mC << " = " << mA + mC << endl << endl;
		} catch ( linear_algebra_error e )
		{
			cerr << endl << e.what() << endl;
		}
		
		
		Matrix<T> m3( {	{ 5.0, 34.0, -28.0 },
				{ 8.0, -83.4, 71.7 },
				{ 83.4, 4.3, 71.7 },
				{ 92.6, 23.3, 9.2 } }	
				);
		
		Matrix<T> m4( {	{ 56.0, 26.0 },
				{ 6.5, 33.4 }, 
				{ 8.4, 1.9 } } 
				);
				
		cout << m3 << " * " << m4 << " = " << m3 * m4 << endl;


		Matrix<T> m1( {	{ 34.0, -28.0 },
				{ -83.4, 71.7 },
				{ 83.4, 71.7 },
				{ 92.6, 23.3 } }	
				);
		
		Matrix<T> m2( {	{ 56.0, 26.0 },
				{ 8.4, 1.9 } } 
				);
				
		cout << m1 << " * " << m2 << " = " << m1 * m2 << endl;
		
		m3.print() << endl;
		m3.transpose();
		m3.print() << endl;
		
		//cout << m1 << " / " << m2 << " = " << m1 / m2 << endl;
		
		
		
		
		cout << endl << "Matrix * Vector tests:" << endl;
		
		Matrix<T> m5( {	{ 34.0, -28.0 },
				{ -83.4, 71.7 },
				{ 92.6, 23.3 } }	
				);
		
		Vector<T> v1( { 23.4, 45.6 } );
		Vector<T> v2( { 23.4, 45.6, 77.0 } );

		try
		{
			cout << m5 << " * " << v1 << " = " << m5 * v1 << endl << endl;
			
			cout << m5 << " * " << v2 << " = " << m5 * v2 << endl << endl;
		}
		catch( linear_algebra_error e )
		{
			cerr << endl << e.what() << endl;
		}
		
		Matrix<T> a( {{2,3},{4,5},{4,5}} );
		Vector<T> b( {6,7} );
		
		cout << endl << a << " * " << b << " = " << a * b << endl;

		double framerate = 11025.0;
		Vector<T> amps( {0.6,0.25,0.1,0.05} );
		Vector<T> fs( {300.0,400.0,500.0,600.0} );
		Vector<T> ts;
		for( double t=0.0; t <1.0; t += 1.0/framerate)
			 ts.push_back(t);
		
		cout << endl << amps << " * " << fs << " = " << amps * fs << endl;
		//cout << endl << ts << endl;
		//cout << endl << ts << " * " << fs << " = " << ts * fs << endl;
		
		auto args = ts.outer(fs);
		auto M = args;
		M.func( [&]( T x ){ return std::cos( PI2 * x); } );
		cout << endl << M << endl;
		
		auto ys = M * amps;
		cout << endl << ys << endl << ys.size() << endl;
		cout << endl << ys[1000] << endl << endl;
		
		Wave wav( framerate, 16 );
		
		wav.setsignal(ys, 100.0);
		
		wav.write( "quad-tone.wav" );
		
		std::complex<T> c1( 0, 1 );
		
		auto z = std::exp( c1 * 1.5 );
		
		std::cout << z << std::endl;
		
		
	}	
	
	return 0;
	
	
	

}




int main()
{

	VectorTest<double>();
	
	return 0;
}


