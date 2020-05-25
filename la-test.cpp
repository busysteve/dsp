
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
			cerr << e.what() << endl;
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

		cout << m5 << " * " << v1 << " = " << m5 * v1 << endl << endl;
		
		cout << m5 << " * " << v2 << " = " << m5 * v2 << endl << endl;
		
		//cout << m1 << " + " << v1 << " = " << m1 + v1 << endl;
		
		

		
	}	
	
	return 0;
	
	
	

}




int main()
{

	VectorTest<double>();
	
	return 0;
}


