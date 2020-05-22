
#include <iostream>
#include <fstream>
#include <vector>
#include <complex>
#include <string>
#include <cstring>
#include <cmath>
#include <float.h>

using namespace std;


class Signal
{

protected:
	std::vector<unsigned char>  samps8;
	std::vector<short>  samps16;
	std::vector<long>  samps24;
	std::vector<float>  samps32;
	std::vector<long>  samps64;
	
	unsigned int _samprate = 0;
	unsigned int _byterate = 0;
	unsigned short _blockalign = 0;
	unsigned short _bitspersample = 0;
	
	const double PI = 3.141592653589793238463;
	
public:

	unsigned int bitReverse(unsigned int x, int log2n) 
	{
	  int n = 0;
	  int mask = 0x1;
	  for (int i=0; i < log2n; i++) {
	    n <<= 1;
	    n |= (x & 1);
	    x >>= 1;
	  }
	  return n;
	}

	template<class Iter_T>
	void fft(Iter_T a, Iter_T b, int log2n)
	{
	  typedef typename iterator_traits<Iter_T>::value_type complex;
	  const complex J(0, 1);
	  int n = 1 << log2n;
	  for (unsigned int i=0; i < n; ++i) {
	    b[bitReverse(i, log2n)] = a[i];
	  }
	  for (int s = 1; s <= log2n; ++s) {
	    int m = 1 << s;
	    int m2 = m >> 1;
	    complex w(1, 0);
	    complex wm = exp(-J * (PI / m2));
	    for (int j=0; j < m2; ++j) {
	      for (int k=j; k < n; k += m) {
		complex t = w * b[k + m2];
		complex u = b[k];
		b[k] = u + t;
		b[k + m2] = u - t;
	      }
	      w *= wm;
	    }
	  }
	}
	
	Signal( int samprate = 44000, int bits = 24 )
	{
		_samprate = samprate;
		_bitspersample = bits;
		_byterate = _samprate * ( _bitspersample / 8 );
	}	

	void sinwave( double freq, double amp, double duration )
	{
		double ampl;
		
		
		
		if( _bitspersample == 32 )
		{
			float maxval = FLT_MAX/2.0; 
			ampl = ((double)maxval / 100.0 ) * amp;
		}
		else
		{
			long maxval = 1;
			
			maxval <<= (_bitspersample-1);
			maxval--;
			ampl = ((double)maxval / 100.0 ) * amp;
		}
		
		
		
		//std::cout << ampl << std::endl;
		
		int count = duration * _samprate;
		
		for( int i=0; i < count; i++ )
		{
			//double s = std::sin( (((double)i)*(freq)) * 0.03 * (PI/180.0) );
			double s = std::sin( (((double)i)*(freq)) * (360.0/_samprate) * (PI/180.0) );

			double ss = s * ampl;
			
			switch( _bitspersample )
			{
				case 8:
					samps8.push_back( (unsigned char)ss );
					break;
				case 16:
					samps16.push_back( (short)ss );
					break;
				case 24:
					samps24.push_back( (long)ss );
					break;
				case 32:
					samps32.push_back( (float)ss );
					break;
				default:
					;
			}
			//std::cout << s << "  \t  " << ss << std::endl;			
		}
	}
		
};



class Wave : public Signal
{

	
	const char* RIFF = "RIFF";
	const char* RIFX = "RIFX";
	const char* WAVE = "WAVE";
	const char* FMT = "fmt ";
	const char* DATA = "data";

	unsigned int _chunksize;
	unsigned int _subchunksize;
	unsigned short _audioformat = 1;
	unsigned short _numchannels = 1;


	
public:

	Wave( int samprate = 44000, int bits = 24 ) 
		: Signal ( samprate, bits )
	{
	}

	bool read( std::string filename )
	{
		std::ifstream file;
		
		file.open( filename, std::ios::binary );
		
		// Read Header
		char seg[4];
		file.read( seg, 4 );
		if( std::strncmp( seg, RIFF, 4 ) == 0 )
		{
			_chunksize = 0;
			file.read( (char*)&_chunksize, sizeof(_chunksize));
			std::cout << "chunksize = " << _chunksize << std::endl;
			
			file.read( seg, 4 );
			if( std::strncmp( seg, WAVE, 4 ) != 0 )
				return false;
			
			file.read( seg, 4 );
			if( std::strncmp( seg, FMT, 4 ) != 0 )
				return false;
			
			_subchunksize = 0;
			file.read( (char*)&_subchunksize, sizeof(_subchunksize));
			std::cout << "subchunksize = " << _subchunksize << std::endl;

			_audioformat = 0;
			file.read( (char*)&_audioformat, sizeof(_audioformat));
			std::cout << "audioformat = " << _audioformat << std::endl;
			
			_numchannels = 0;
			file.read( (char*)&_numchannels, sizeof(_numchannels));
			std::cout << "numchannels = " << _numchannels << std::endl;
			
			_samprate = 0;
			file.read( (char*)&_samprate, sizeof(_samprate));
			std::cout << "samprate = " << _samprate << std::endl;
			
			_byterate = 0;
			file.read( (char*)&_byterate, sizeof(_byterate));
			std::cout << "byterate = " << _byterate << std::endl;
			
			_blockalign = 0;
			file.read( (char*)&_blockalign, sizeof(_blockalign));
			std::cout << "blockalign = " << _blockalign << std::endl;
			
			_bitspersample = 0;
			file.read( (char*)&_bitspersample, sizeof(_bitspersample));
			std::cout << "bitspersample = " << _bitspersample << std::endl;
			
			file.read( seg, 4 );
			if( std::strncmp( seg, DATA, 4 ) != 0 )
				return false;
			
			unsigned int _subchunk2Size = 0;
			file.read( (char*)&_subchunk2Size, sizeof(_subchunk2Size));
			std::cout << "subchunk2Size = " << _subchunk2Size << std::endl;

			if( _bitspersample == 8 )
			{
				unsigned char sample;
				while( file >> sample )
					samps8.push_back(sample);
				file.close();
			}
			else if( _bitspersample == 16 )
			{
				long sample = 0;
				while( file.read( (char*)&sample, 2 ) )
					samps16.push_back(sample);
				file.close();
			}
			else if( _bitspersample == 24 )
			{
				long sample = 0;
				while( file.read( (char*)&sample, 3 ) )
					samps24.push_back(sample);
				file.close();
			}
			else if( _bitspersample == 32 )
			{
				float sample;
				while( file.read( (char*)&sample, 4 ) )
					samps32.push_back(sample);
				file.close();
			}
			
			return true;
		}
		else
			return false;
			
	    return false;
		
	}
	
	
	bool write( std::string filename )
	{
		std::ofstream file;
		
		file.open( filename, std::ios::binary );
		
		// Write Header
		unsigned int subchunksize = 16;
		unsigned int subchunk2size;
		
		if( _bitspersample == 8 )
		{
			subchunk2size = samps8.size();
		}
		else if( _bitspersample == 16 )
		{
			subchunk2size = samps16.size() * 2;
		}
		else if( _bitspersample == 24 )
		{
			subchunk2size = samps24.size() * 3;
		}
		else if( _bitspersample == 32 )
		{
			subchunk2size = samps32.size() * sizeof(float);
		}

		unsigned int chunksize = subchunk2size + 36;
		
		file.write( RIFF, 4 );

		file.write( (char*)&chunksize, sizeof(chunksize));
		std::cout << "chunksize = " << chunksize << std::endl;
		
		file.write( WAVE, 4 );
		file.write( FMT, 4 );
		
		file.write( (char*)&subchunksize, sizeof(subchunksize));
		std::cout << "subchunksize = " << subchunksize << std::endl;

		file.write( (char*)&_audioformat, sizeof(_audioformat));
		std::cout << "audioformat = " << _audioformat << std::endl;
		
		file.write( (char*)&_numchannels, sizeof(_numchannels));
		std::cout << "numchannels = " << _numchannels << std::endl;
		
		file.write( (char*)&_samprate, sizeof(_samprate));
		std::cout << "samprate = " << _samprate << std::endl;
		
		file.write( (char*)&_byterate, sizeof(_byterate));
		std::cout << "byterate = " << _byterate << std::endl;
		
		unsigned short blockalign = ( ( _numchannels * _bitspersample ) / 8);
		
		file.write( (char*)&blockalign, sizeof(blockalign));
		std::cout << "blockalign = " << blockalign << std::endl;
		
		file.write( (char*)&_bitspersample, sizeof(_bitspersample));
		std::cout << "bitspersample = " << _bitspersample << std::endl;
		
		file.write( DATA, 4 );		
		
		file.write( (char*)&subchunk2size, sizeof(subchunk2size));
		std::cout << "subchunk2size = " << subchunk2size << std::endl;
		
		if( _bitspersample == 8 )
		{
			for( auto sample : samps8 )
				file << sample;
		}
		else if( _bitspersample == 16 )
		{
			for( auto sample : samps16 )
				//file << sample;
				file.write( (char*)&sample, 2 );
		}
		else if( _bitspersample == 24 )
		{
			for( auto sample : samps24 )
				//file << sample;
				file.write( (char*)&sample, 3 );
		}
		else if( _bitspersample == 32 )
		{
			for( auto sample : samps32 )
			{
				file.write( (char*)&sample, 4 );
			}
		}
		
		file.close();
		return true;
	}

		
};



