
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
	
	return 0;
	
	
	

}




int main()
{

	VectorTest<double>();
	
	return 0;
}


