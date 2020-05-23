
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






int main()
{

	Vector<double> v1( { 13.0, 12.0, 2.0 } );
	Vector<double> v2( { 14.0, 15.0, -3.0 } );
	
	cout << v1.dot( v2 ) << endl;
	
	
	
	return 0;


}




