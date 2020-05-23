
#ifndef __BS_Matrix_H
#define __BS_Matrix_H

#include <iostream>
#include <fstream>
#include <vector>
#include <complex>
#include <string>
#include <cstring>
#include <cmath>
#include <float.h>
#include <initializer_list>


template <class T> class Vector : public std::vector< T>
{

public:

	Vector< T>() {}
	
	Vector< T>(initializer_list<T> l ) {
		for( auto k : l )
			std::vector<T>::push_back(k);
	}
	
	virtual ~Vector< T>() {}

	

	T dot( const Vector< T>& v )
	{
		if( this->size() != v.size() || v.size() == 0 )
			return nan("NaN");
		
		T ret = 0;
		for( int i=0; i < this->size(); i++ )
			ret += (*this)[i] * v[i];
			
		return ret;
	}

	

};



template <typename T> class Matrix
{

	Vector< Vector< T > > _m;
	
	unsigned int _rs;
	unsigned int _cs;
	
public:
	Matrix(unsigned int rows, unsigned int cols, const T& x) {
		_m.resize(rows);
		
		for ( unsigned int i=0; i < _m.size(); i++ ) 
			_m[i].resize(cols, x);
		
		_rs = rows;
		_cs = cols;
	}

	Matrix(const Matrix<T>& r) {
		_m = r._m;
		_rs = r.nr();
		_cs = r.nc();
	}

	virtual ~Matrix(){}



	// Assignment Operator

	Matrix<T>& operator=(const Matrix<T>& rhs) {
	  if (&rhs == this)
	    return *this;

	  unsigned int new_rows = rhs.get_rows();
	  unsigned int new_cols = rhs.get_cols();

	  _m.resize(new_rows);
	  for (unsigned int i=0; i<_m.size(); i++) {
	    _m[i].resize(new_cols);
	  }

	  for (unsigned int i=0; i<new_rows; i++) {
	    for (unsigned int j=0; j<new_cols; j++) {
	      _m[i][j] = rhs(i, j);
	    }
	  }
	  _rs = new_rows;
	  _cs = new_cols;

	  return *this;
	}


	// Addition

	Matrix<T>& operator+(const Matrix<T>& rhs) {
	  Matrix result(_rs, _cs, 0.0);

	  for (unsigned int i=0; i<_rs; i++) {
	    for (unsigned int j=0; j<_cs; j++) {
	      result(i,j) = this->_m[i][j] + rhs(i,j);
	    }
	  }

	  return result;
	}


	// Cumulative addition of this Matrix and another

	Matrix<T>& operator+=(const Matrix<T>& rhs) {
	  unsigned int _rs = rhs.get_rows();
	  unsigned int _cs = rhs.get_cols();

	  for (unsigned int i=0; i<_rs; i++) {
	    for (unsigned int j=0; j<_cs; j++) {
	      this->_m[i][j] += rhs(i,j);
	    }
	  }

	  return *this;
	}




	// Left multiplication of this Matrix and another

	Matrix<T>& operator*(const Matrix<T>& rhs) {
	  unsigned int _rs = rhs.get_rows();
	  unsigned int _cs = rhs.get_cols();
	  Matrix result(_rs, _cs, 0.0);

	  for (unsigned int i=0; i<_rs; i++) {
	    for (unsigned int j=0; j<_cs; j++) {
	      for (unsigned int k=0; k<_rs; k++) {
		result(i,j) += this->_m[i][k] * rhs(k,j);
	      }
	    }
	  }

	  return result;
	}


	// Cumulative left multiplication of this Matrix and another

	Matrix<T>& operator*=(const Matrix& rhs) {
	  Matrix result = (*this) * rhs;
	  (*this) = result;
	  return *this;
	}


	// Matrix/scalar addition   

	Matrix<T>& operator+(const T& rhs) {
	  Matrix result(_rs, _cs, 0.0);

	  for (unsigned int i=0; i<_rs; i++) {
	    for (unsigned int j=0; j<_cs; j++) {
	      result(i,j) = this->_m[i][j] + rhs;
	    }
	  }

	  return result;
	}

	  

	// Multiply a Matrix with a Vector 

	template< T>
	Vector<T> operator*(const Vector<T>& r) {
	  Vector<T> result(r.size(), 0.0);

	  for (unsigned int i=0; i<_rs; i++) {
	    for (unsigned int j=0; j<_cs; j++) {
	      result[i] = this->_m[i][j] * r[j];
	    }
	  }

	  return result;
	}


	// Obtain a Vector of the diagonal elements


	Vector<T> diag_vec() {
	  Vector<T> result(_rs, 0.0);

	  for (unsigned int i=0; i<_rs; i++) {
	    result[i] = this->_m[i][i];
	  }

	  return result;
	}


	// Access the individual elements
	T& operator()(const unsigned int& row, const unsigned int& col) {
	  return this->_m[row][col];
	}

	// Access the individual elements (const)
	const T& operator()(const unsigned int& row, const unsigned int& col) const {
	  return this->_m[row][col];
	}

	// Get the number of rows of the Matrix  
	unsigned int nr() const {
	  return this->_rs;
	}

	// Get the number of columns of the Matrix 
	unsigned int nc() const {
	  return this->_cs;
	}


};


#endif



