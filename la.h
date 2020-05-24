
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
	
	Vector<T>( int s, T x = (T)(0.0) ) {
		std::vector<T>::resize( s, x );
	}
	
	Vector<T>( const Vector<T>& r ) {
		for( auto k : r )
			std::vector<T>::push_back(k);
	}
	
	Vector<T>( initializer_list<T> l ) {
		for( auto k : l )
			std::vector<T>::push_back(k);
	}
	
	Vector<T>( initializer_list< initializer_list<T> >& ll ) {
		for( auto l : ll )
			std::vector<T>::push_back( T(l) );
	}
	
	Vector<T>( Vector< Vector<T> > ll ) {
		for( auto l : ll )
			std::vector<T>::push_back( T(l) );
	}
	
	virtual ~Vector<T>() {}

	// Vector | Vector Arithmetic section
	
	T dot( const Vector<T>& v ) const 
	{
		if( this->size() != v.size() || v.size() == 0 )
			return nan("NaN");
		
		T ret = 0;
		for( int i=0; i < this->size(); i++ )
			ret += (*this)[i] * v[i];
			
		return ret;
	}

	Vector<T>  mul( const Vector<T>& v ) const 
	{
		if( this->size() != v.size() || v.size() == 0 )
			return nan("NaN");
		
		Vector<T> vret( v.size(), (T)0.0 );
		for( int i=0; i < v.size(); i++ )
			vret[i] = (*this)[i] * v[i];
			
		return vret;
	}

	Vector<T>  div( const Vector<T>& v ) const 
	{
		if( this->size() != v.size() || v.size() == 0 )
			return nan("NaN");
		
		Vector<T> vret( v.size(), (T)0.0 );
		for( int i=0; i < v.size(); i++ )
			vret[i] = (*this)[i] / v[i];
			
		return vret;
	}

	Vector<T>  add( const Vector<T>& v ) const 
	{
		if( this->size() != v.size() || v.size() == 0 )
			return nan("NaN");
		
		Vector<T> vret( v.size(), (T)0.0 );
		for( int i=0; i < v.size(); i++ )
			vret[i] = (*this)[i] + v[i];
			
		return vret;
	}

	Vector<T>  sub( const Vector<T>& v ) const 
	{
		if( this->size() != v.size() || v.size() == 0 )
			return nan("NaN");
		
		Vector<T> vret( v.size(), (T)0.0 );
		for( int i=0; i < v.size(); i++ )
			vret[i] = (*this)[i] - v[i];
			
		return vret;
	}


	// Vector | Scalar Arithmetic section

	Vector<T>  mul( T s ) const 
	{
		if( this->size() == 0 )
			return nan("NaN");
		
		Vector<T> vret( std::vector<T>::size(), (T)0.0 );
		for( int i=0; i < std::vector<T>::size(); i++ )
			vret[i] = (*this)[i] * s;
			
		return vret;
	}

	Vector<T>  div( T s ) const 
	{
		if( this->size() == 0 )
			return nan("NaN");
		
		Vector<T> vret( std::vector<T>::size(), (T)0.0 );
		for( int i=0; i < std::vector<T>::size(); i++ )
			vret[i] = (*this)[i] / s;
			
		return vret;
	}

	Vector<T>  add( T s ) const 
	{
		if( this->size() == 0 )
			return nan("NaN");
		
		Vector<T> vret( std::vector<T>::size(), (T)0.0 );
		for( int i=0; i < std::vector<T>::size(); i++ )
			vret[i] = (*this)[i] + s;
			
		return vret;
	}

	Vector<T>  sub( T s ) const 
	{
		if( this->size() == 0 )
			return nan("NaN");
		
		Vector<T> vret( std::vector<T>::size(), (T)0.0 );
		for( int i=0; i < std::vector<T>::size(); i++ )
			vret[i] = (*this)[i] - s;
			
		return vret;
	}

	// Vector Operator Overloading
	Vector<T>  operator-( ) const
	{
		Vector<T> ret( (*this).mul((T)-1.0) );
		
		return ret;
	}
	
	Vector<T>  operator-( const Vector<T>& r ) const 
	{
		return sub(r);
	}
	
	Vector<T>  operator-( const T& r ) const 
	{
		return sub(r);
	}
	
	
	Vector<T>  operator+( const Vector<T>& r ) const 
	{
		return add(r);
	}
	
	Vector<T>  operator+( const T& r ) const 
	{
		return add(r);
	}
	
	
	Vector<T>  operator*( const Vector<T>& r ) const 
	{
		return mul(r);
	}
	
	Vector<T>  operator*( const T& r ) const 
	{
		return mul(r);
	}
	
	
	Vector<T>  operator/( const Vector<T>& r ) const 
	{
		return div(r);
	}
	
	Vector<T>  operator/( const T& r ) const 
	{
		return div(r);
	}
	
	

	friend Vector<T> operator-( const T& l, const Vector<T> & v)
	{
		return (-v).sub(l);
	}
	
	friend Vector<T> operator/( const T& l, const Vector<T> & v)
	{
		return ( (v).div( (T)1.0 / (T)l ) );
	}
	
	friend Vector<T> operator*( const T& l, const Vector<T> & v)
	{
		return (v).mul(l);
	}
	
	friend Vector<T> operator+( const T& l, const Vector<T> & v)
	{
		return (v).add(l);
	}
	
	//T& operator[](unsigned int i)  { return (*this)[i]; }
	
	
	friend std::ostream& operator<<(std::ostream& os, const Vector<T> & v)
	{
	
		os << "{";
		
		if( v.size() > 0 )
		{
			os << v[0];
			for( int i=1; i < v.size(); i++ )
				os << "," << v[i];
		}
			
		os << "}";

		return os;
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

	//Matrix( initializer_list< initializer_list<T> > il ) 
	Matrix( Vector< Vector< T > > vl ) 
		//: _m(il) 
	{		
		for ( auto l : vl ) 
			_m.push_back(l);
		
		_rs = _m.size();
		_cs = 0;
			
		if( _rs > 0 )
			_cs = _m[0].size();
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

	  unsigned int new_rows = rhs.nr();
	  unsigned int new_cols = rhs.nc();

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
	  unsigned int _rs = rhs.nr();
	  unsigned int _cs = rhs.nc();

	  for (unsigned int i=0; i<_rs; i++) {
	    for (unsigned int j=0; j<_cs; j++) {
	      this->_m[i][j] += rhs(i,j);
	    }
	  }

	  return *this;
	}




	// Left multiplication of this Matrix and another

	Matrix<T> operator*(const Matrix<T>& rhs) {
	  unsigned int rs = nr();
	  unsigned int cs = rhs.nc();
	  
	  cout << rs << "x" << cs << endl;
	  
	  Matrix result(rs, cs, 0.0);

	  for (unsigned int i=0; i<rs; i++) {
	    for (unsigned int j=0; j<cs; j++) {
	      for (unsigned int k=0; k<rhs.nr(); k++) {
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


	Vector<T> operator*(const Vector<T>& r) const {
	  Vector<T> result(_rs, 0.0);

	  for (unsigned int i=0; i<_rs; i++) {
	    for (unsigned int j=0; j<_cs; j++) {
	      result[i] += this->_m[i][j] * r[j];
	    }
	  }

	  return result;
	}

	Vector<T> operator+(const Vector<T>& r) const {
	  Vector<T> result(_rs, 0.0);

	  for (unsigned int i=0; i<_rs; i++) {
	    for (unsigned int j=0; j<_cs; j++) {
	      result[i] += this->_m[i][j] + r[j];
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

	
	Vector<T> operator[](unsigned int i) const {
	  return _m[i];
	}

	Vector<T>& operator[](unsigned int i)  {
	  return _m[i];
	}

	friend std::ostream& operator<<(std::ostream& os, const Matrix<T> & m)  
	{
	
		os << "{";
		
		if( m.nr() > 0 )
		{
			os << m[0];
			for( int i=1; i < m.nr(); i++ )
				os << "," << m[i];
		}
			
		os << "}";

		return os;
	}


};


#endif



