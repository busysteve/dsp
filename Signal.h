
#include <iostream>
#include <fstream>
#include <vector>
#include <complex>
#include <string>
#include <cstring>
#include <cmath>



class Wave
{
	std::vector<unsigned char>  samps8;
	std::vector<short>  samps16;
	std::vector<int>  samps32;
	std::vector<long>  samps64;
	
	const char* RIFF = "RIFF";
	const char* RIFX = "RIFX";
	const char* WAVE = "WAVE";
	const char* FMT = "fmt ";
	const char* DATA = "data";

	unsigned int _chunksize;
	unsigned int _subchunksize;
	const unsigned short _audioformat = 1;
	const unsigned short _numchannels = 1;
	unsigned int _samprate = 0;
	unsigned int _byterate = 0;
	unsigned short _blockalign = 0;
	unsigned short _bitspersample = 0;
	
	const double PI = 3.141592653589793238463;
	
public:
	
	
	bool read( std::string filename )
	{
		std::ifstream file;
		
		file.open( filename, std::ios::binary );
		
		// Read Header
		char seg[4];
		file.read( seg, 4 );
		if( std::strncmp( seg, RIFF, 4 ) == 0 )
		{
			unsigned int chunksize = 0;
			file.read( (char*)&chunksize, sizeof(chunksize));
			std::cout << "chunksize = " << chunksize << std::endl;
			
			file.read( seg, 4 );
			if( std::strncmp( seg, WAVE, 4 ) != 0 )
				return false;
			
			file.read( seg, 4 );
			if( std::strncmp( seg, FMT, 4 ) != 0 )
				return false;
			
			unsigned int subchunksize = 0;
			file.read( (char*)&subchunksize, sizeof(subchunksize));
			std::cout << "subchunksize = " << subchunksize << std::endl;

			unsigned short audioformat;
			file.read( (char*)&audioformat, sizeof(audioformat));
			std::cout << "audioformat = " << audioformat << std::endl;
			
			unsigned short numchannels;
			file.read( (char*)&numchannels, sizeof(numchannels));
			std::cout << "numchannels = " << numchannels << std::endl;
			
			unsigned int samprate;
			file.read( (char*)&samprate, sizeof(samprate));
			std::cout << "samprate = " << samprate << std::endl;
			
			unsigned int byterate;
			file.read( (char*)&byterate, sizeof(byterate));
			std::cout << "byterate = " << byterate << std::endl;
			
			unsigned short blockalign;
			file.read( (char*)&blockalign, sizeof(blockalign));
			std::cout << "blockalign = " << blockalign << std::endl;
			
			unsigned short bitspersample;
			file.read( (char*)&bitspersample, sizeof(bitspersample));
			std::cout << "bitspersample = " << bitspersample << std::endl;
			
			file.read( seg, 4 );
			if( std::strncmp( seg, DATA, 4 ) != 0 )
				return false;
			
			unsigned int subchunk2Size;
			file.read( (char*)&subchunk2Size, sizeof(subchunk2Size));
			std::cout << "subchunk2Size = " << subchunk2Size << std::endl;

			if( bitspersample == 8 )
			{
				unsigned char sample;
				while( file >> sample )
					samps8.push_back(sample);
				file.close();
			}
			else if( bitspersample == 16 )
			{
				short sample;
				while( file >> sample )
					samps16.push_back(sample);
				file.close();
			}
			else if( bitspersample == 32 )
			{
				int sample;
				while( file >> sample )
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
			subchunk2size = samps16.size() * sizeof(short);
		}
		else if( _bitspersample == 32 )
		{
			subchunk2size = samps32.size() * sizeof(int);
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
		else if( _bitspersample == 32 )
		{
			for( auto sample : samps32 )
				file << sample;
		}
		
		file.close();
		return true;
	}
	

	void sinwave( double freq, double amp, double duration )
	{
		_samprate = 12000;
		_bitspersample = 16;
		_byterate = _samprate * ( _bitspersample / 8 );
		
		short maxval = ((short)( 65536 / 2 - 1));
		std::cout << maxval << std::endl;
		
		double ampl = ((double)maxval / 100.0 ) * amp;
		std::cout << ampl << std::endl;
		
		int count = duration * _samprate;
		
		for( int i=0; i < count; i++ )
		{
			double s = std::sin( (((double)i)*(freq)) * 0.03 * (PI/180.0) );

			double ss = s * ampl;
			samps16.push_back( (short)ss );
			
			std::cout << s << "  \t  " << ss << std::endl;
			
		}
	}
		
};
