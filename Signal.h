
#include <iostream>
#include <fstream>
#include <vector>
#include <complex>
#include <string>
#include <cstring>
#include <cmath>
#include <float.h>

#include <algorithm>
#include <cmath>
#include <complex>
#include <cstdint>
#include <iterator>
#include <limits>
#include <stdexcept>
#include <vector>

constexpr double PI = 3.14159265358979323846;

using namespace std;


class Signal
{

public:
	std::vector<unsigned char>  samps8;
	std::vector<short>  samps16;
	std::vector<std::int32_t>  samps24;
	std::vector<float>  samps32;
	std::vector<long>  samps64;
	
	unsigned int _samprate = 0;
	unsigned int _byterate = 0;
	unsigned short _blockalign = 0;
	unsigned short _bitspersample = 0;
	
	//const double PI = 3.141592653589793238463;
	//constexpr double PI = 3.14159265358979323846;
	
public:
/*
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

	*/	


	Signal( int samprate = 44000, int bits = 24 )
	{
		_samprate = samprate;
		_bitspersample = bits;
		_byterate = _samprate * ( _bitspersample / 8 );
	}	



	void sinwave( std::vector<double> freqs, double amp, double duration )
	{
		double ampl;
		
		double freq = 0.0;
		
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
					if( samps8.size() < count ) samps8.resize( count );
					samps8[i] = ( samps8[i] + ( (unsigned char)ss ) ) / 2;
					break;
				case 16:
					if( samps16.size() < count ) samps16.resize( count );
					samps16[i] = ( samps16[i] + ( (short)ss ) ) / 2;
					break;
				case 20:
					if( samps24.size() < count ) samps24.resize( count );
					samps24[i] = ( samps24[i] + ( (long)ss ) ) / 2;
					break;
				case 24:
					if( samps24.size() < count ) samps24.resize( count );
					for( int j=0; j < freqs.size(); j++ )
					{
						s = std::sin((((double)i)*(freqs[j]))*(360.0/_samprate)*(PI/180.0))*ampl;
						ss += s;
					}
					samps24[i] += (long)( ss / (double)freqs.size() );
					break;
				case 32:
					if( samps32.size() < count ) samps32.resize( count );
					samps32[i] = ( samps32[i] + ( (float)ss ) ) / 2.0;
					break;
				default:
					;
			}
			//std::cout << s << "  \t  " << ss << std::endl;			
		}
	}



// -----------------------------------------------------------------------------
// FFT helpers
// -----------------------------------------------------------------------------

unsigned int bitReverse(unsigned int x, int log2n)
{
    unsigned int result = 0;

    for (int i = 0; i < log2n; ++i) {
        result <<= 1U;
        result |= x & 1U;
        x >>= 1U;
    }

    return result;
}

template<class Iter_T>
void fft(Iter_T input, Iter_T output, int log2n)
{
    using Complex =
        typename std::iterator_traits<Iter_T>::value_type;

    const Complex J(0.0, 1.0);
    const int n = 1 << log2n;

    // Copy samples into bit-reversed order.
    for (unsigned int i = 0;
         i < static_cast<unsigned int>(n);
         ++i) {
        output[bitReverse(i, log2n)] = input[i];
    }

    // Iterative radix-2 Cooley-Tukey FFT.
    for (int stage = 1; stage <= log2n; ++stage) {
        const int blockSize = 1 << stage;
        const int halfBlock = blockSize >> 1;

        Complex w(1.0, 0.0);

        const Complex wm =
            std::exp(-J * (PI / static_cast<double>(halfBlock)));

        for (int j = 0; j < halfBlock; ++j) {
            for (int k = j; k < n; k += blockSize) {
                const Complex t =
                    w * output[k + halfBlock];

                const Complex u = output[k];

                output[k] = u + t;
                output[k + halfBlock] = u - t;
            }

            w *= wm;
        }
    }
}

// -----------------------------------------------------------------------------
// Spectrogram structures
// -----------------------------------------------------------------------------

struct SpectrogramFrame
{
    // Time at the center of this FFT frame.
    double timeSeconds = 0.0;

    // 1,024 values corresponding to:
    // 1, 5, 9, ..., 4093 Hz.
    std::vector<float> binsDbFS;
};

struct Spectrogram
{
    // Frequency represented by each bin position.
    std::vector<double> frequenciesHz;

    // One bin vector for every time frame.
    std::vector<SpectrogramFrame> frames;
};

// -----------------------------------------------------------------------------
// Utility functions
// -----------------------------------------------------------------------------

bool isPowerOfTwo(std::size_t value)
{
    return value != 0 && (value & (value - 1)) == 0;
}

int powerOfTwoLog2(std::size_t value)
{
    if (!isPowerOfTwo(value)) {
        throw std::invalid_argument(
            "FFT frame size must be a power of two.");
    }

    int result = 0;

    while (value > 1) {
        value >>= 1U;
        ++result;
    }

    return result;
}

std::size_t nextPowerOfTwo(std::size_t value)
{
    if (value <= 1) {
        return 1;
    }

    --value;

    for (std::size_t shift = 1;
         shift < sizeof(std::size_t) * 8;
         shift <<= 1U) {
        value |= value >> shift;
    }

    return value + 1;
}

// -----------------------------------------------------------------------------
// Main spectrogram function
// -----------------------------------------------------------------------------

Spectrogram makeSpectrogram24Bit(
    std::vector<std::int32_t>& waveform,
    double sampleRate,
    std::size_t frameSize = 0,
    std::size_t hopSize = 0,
    float minimumDbFS = -120.0F)
{
    constexpr std::int32_t PCM24_MIN = -8388608;
    constexpr std::int32_t PCM24_MAX =  8388607;

    constexpr double FIRST_FREQUENCY = 10.0;
    constexpr double FREQUENCY_STEP = 10.0;
    constexpr std::size_t BIN_COUNT = 256;

    if (!std::isfinite(sampleRate) || sampleRate <= 0.0) {
        throw std::invalid_argument(
            "Sample rate must be positive.");
    }

    // Highest returned bin is 4093 Hz.
    constexpr double HIGHEST_FREQUENCY =
        FIRST_FREQUENCY +
        FREQUENCY_STEP * static_cast<double>(BIN_COUNT - 1);

    if (sampleRate / 2.0 < HIGHEST_FREQUENCY) {
        throw std::invalid_argument(
            "Sample rate is too low. Nyquist frequency must "
            "be at least 4093 Hz.");
    }

    /*
        For approximately 1 Hz FFT spacing, use a frame containing
        roughly one second of audio, rounded upward to a power of two.

        Examples:
            8,000 Hz  -> 8,192 samples
            44,100 Hz -> 65,536 samples
            48,000 Hz -> 65,536 samples
    */
    if (frameSize == 0) {
        frameSize = nextPowerOfTwo(
            static_cast<std::size_t>(std::ceil(sampleRate)));
    }

    if (!isPowerOfTwo(frameSize)) {
        throw std::invalid_argument(
            "frameSize must be a power of two.");
    }

    if (frameSize < 2) {
        throw std::invalid_argument(
            "frameSize must contain at least two samples.");
    }

    // Default to 75% overlap.
    if (hopSize == 0) {
        hopSize = std::max<std::size_t>(1, frameSize / 4);
    }

    if (hopSize > frameSize) {
        throw std::invalid_argument(
            "hopSize cannot exceed frameSize.");
    }

    const int log2n = powerOfTwoLog2(frameSize);
    const std::size_t positiveBinCount = frameSize / 2 + 1;

    Spectrogram result;

    result.frequenciesHz.resize(BIN_COUNT);

    for (std::size_t i = 0; i < BIN_COUNT; ++i) {
        result.frequenciesHz[i] =
            FIRST_FREQUENCY +
            FREQUENCY_STEP * static_cast<double>(i);
    }

    if (waveform.empty()) {
        return result;
    }

    // Create a Hann window.
    std::vector<double> window(frameSize);
    double windowSum = 0.0;

    for (std::size_t i = 0; i < frameSize; ++i) {
        window[i] =
            0.5 -
            0.5 * std::cos(
                2.0 * PI * static_cast<double>(i) /
                static_cast<double>(frameSize - 1));

        windowSum += window[i];
    }

    if (windowSum <= 0.0) {
        throw std::runtime_error(
            "Invalid window normalization.");
    }

    std::vector<std::complex<double>> fftInput(frameSize);
    std::vector<std::complex<double>> fftOutput(frameSize);
    std::vector<double> fftPower(positiveBinCount);

    const double dbFloorAmplitude =
        std::pow(10.0, static_cast<double>(minimumDbFS) / 20.0);

    for (std::size_t frameStart = 0;
         frameStart < waveform.size();
         frameStart += hopSize) {

        // Fill and window this frame. Samples beyond the input are
        // zero-padded.
        for (std::size_t i = 0; i < frameSize; ++i) {
            const std::size_t sourceIndex = frameStart + i;

            double normalizedSample = 0.0;

            if (sourceIndex < waveform.size()) {
                const std::int32_t rawSample =
                    waveform[sourceIndex];

                if (rawSample < PCM24_MIN ||
                    rawSample > PCM24_MAX) {
                    throw std::out_of_range(
                        "Waveform contains a sample outside "
                        "the signed 24-bit range.");
                }

                // Signed 24-bit PCM becomes approximately [-1, 1).
                normalizedSample =
                    static_cast<double>(rawSample) / 8388608.0;
            }

            fftInput[i] = std::complex<double>(
                normalizedSample * window[i],
                0.0);
        }

        fft(
            fftInput.begin(),
            fftOutput.begin(),
            log2n);

        // Store power for the positive-frequency half.
        for (std::size_t k = 0;
             k < positiveBinCount;
             ++k) {
            fftPower[k] = std::norm(fftOutput[k]);
        }

        SpectrogramFrame frame;

        frame.timeSeconds =
            (static_cast<double>(frameStart) +
             static_cast<double>(frameSize) / 2.0) /
            sampleRate;

        frame.binsDbFS.resize(BIN_COUNT);

        for (std::size_t outputBin = 0;
             outputBin < BIN_COUNT;
             ++outputBin) {

            const double targetFrequency =
                result.frequenciesHz[outputBin];

            /*
                Convert the requested physical frequency to a fractional
                FFT index:

                    FFT index = frequency * frameSize / sampleRate
            */
            const double fractionalIndex =
                targetFrequency *
                static_cast<double>(frameSize) /
                sampleRate;

            const std::size_t lowerIndex =
                static_cast<std::size_t>(
                    std::floor(fractionalIndex));

            const std::size_t upperIndex =
                std::min(
                    lowerIndex + 1,
                    positiveBinCount - 1);

            const double interpolation =
                fractionalIndex -
                static_cast<double>(lowerIndex);

            // Interpolate power between adjacent FFT bins.
            const double interpolatedPower =
                fftPower[lowerIndex] * (1.0 - interpolation) +
                fftPower[upperIndex] * interpolation;

            /*
                Convert FFT power into a one-sided, full-scale-relative
                amplitude.

                Hann-window scaling uses the sum of window coefficients.
                Non-DC positive frequencies are multiplied by two because
                the negative-frequency half is omitted.
            */
            double amplitude =
                2.0 * std::sqrt(
                    std::max(0.0, interpolatedPower)) /
                windowSum;

            amplitude = std::max(
                amplitude,
                dbFloorAmplitude);

            double dbFS =
                20.0 * std::log10(amplitude);

            dbFS = std::clamp(
                dbFS,
                static_cast<double>(minimumDbFS),
                0.0);

            frame.binsDbFS[outputBin] =
                static_cast<float>(dbFS);
        }

        result.frames.push_back(std::move(frame));

        // This was the final zero-padded frame.
        if (frameStart + frameSize >= waveform.size()) {
            break;
        }
    }

    return result;
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
			//std::cout << "chunksize = " << _chunksize << std::endl;
			
			file.read( seg, 4 );
			if( std::strncmp( seg, WAVE, 4 ) != 0 )
				return false;
			
			file.read( seg, 4 );
			if( std::strncmp( seg, FMT, 4 ) != 0 )
				return false;
			
			_subchunksize = 0;
			file.read( (char*)&_subchunksize, sizeof(_subchunksize));
			//std::cout << "subchunksize = " << _subchunksize << std::endl;

			_audioformat = 0;
			file.read( (char*)&_audioformat, sizeof(_audioformat));
			//std::cout << "audioformat = " << _audioformat << std::endl;
			
			_numchannels = 0;
			file.read( (char*)&_numchannels, sizeof(_numchannels));
			//std::cout << "numchannels = " << _numchannels << std::endl;
			
			_samprate = 0;
			file.read( (char*)&_samprate, sizeof(_samprate));
			//std::cout << "samprate = " << _samprate << std::endl;
			
			_byterate = 0;
			file.read( (char*)&_byterate, sizeof(_byterate));
			//std::cout << "byterate = " << _byterate << std::endl;
			
			_blockalign = 0;
			file.read( (char*)&_blockalign, sizeof(_blockalign));
			//std::cout << "blockalign = " << _blockalign << std::endl;
			
			_bitspersample = 0;
			file.read( (char*)&_bitspersample, sizeof(_bitspersample));
			//std::cout << "bitspersample = " << _bitspersample << std::endl;
			
			file.read( seg, 4 );
			if( std::strncmp( seg, DATA, 4 ) != 0 )
				return false;
			
			unsigned int _subchunk2Size = 0;
			file.read( (char*)&_subchunk2Size, sizeof(_subchunk2Size));
			//std::cout << "subchunk2Size = " << _subchunk2Size << std::endl;

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
		//std::cout << "chunksize = " << chunksize << std::endl;
		
		file.write( WAVE, 4 );
		file.write( FMT, 4 );
		
		file.write( (char*)&subchunksize, sizeof(subchunksize));
		//std::cout << "subchunksize = " << subchunksize << std::endl;

		file.write( (char*)&_audioformat, sizeof(_audioformat));
		//std::cout << "audioformat = " << _audioformat << std::endl;
		
		file.write( (char*)&_numchannels, sizeof(_numchannels));
		//std::cout << "numchannels = " << _numchannels << std::endl;
		
		file.write( (char*)&_samprate, sizeof(_samprate));
		//std::cout << "samprate = " << _samprate << std::endl;
		
		file.write( (char*)&_byterate, sizeof(_byterate));
		//std::cout << "byterate = " << _byterate << std::endl;
		
		unsigned short blockalign = ( ( _numchannels * _bitspersample ) / 8);
		
		file.write( (char*)&blockalign, sizeof(blockalign));
		//std::cout << "blockalign = " << blockalign << std::endl;
		
		file.write( (char*)&_bitspersample, sizeof(_bitspersample));
		//std::cout << "bitspersample = " << _bitspersample << std::endl;
		
		file.write( DATA, 4 );		
		
		file.write( (char*)&subchunk2size, sizeof(subchunk2size));
		//std::cout << "subchunk2size = " << subchunk2size << std::endl;
		
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

	void setsignal( vector<double>& signal, double amp=100.0 )
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
		
		samps16.clear();
		
		for( auto s : signal )
			samps16.push_back( (short) (s*ampl) );
	}

		
};



