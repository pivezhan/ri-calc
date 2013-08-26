#include <iostream>
#include <vector>
#include <complex>
#include <fstream>
#include <stdio.h>
#include <string.h>
using namespace std;

//fftw fourier transform library
#ifdef FFTW_AVAILABLE
#include <fftw3.h>
#endif

#include "rts/material.h"
//#include "options.h"

#include <boost/program_options.hpp>
namespace po = boost::program_options;


typedef double ptype;
typedef complex<ptype> pcomplex;

rts::material<ptype> M;

#define PI  3.14159

int main(int argc, char* argv[])
{
	po::options_description desc("Allowed options");
	desc.add_options()
		("help,h", "Display this help message.")
		("input-file,i", po::value<string>(), "Input file containing material information.")
		("input-format,f", po::value<string>()->default_value("wavenumber,n,k"), "Format string identifying the order of material properties in the input file. Options include: microns, wavenumber, n (real RI), k (imaginary RI), A (absorbance), Xp (real Chi), Xpp (imaginary Chi).\n\nThe default [microns,n,k] will load a material file with columns representing the wavelength in microns, followed by the real and imaginary parts of the refractive index.")
		("output-file,o", po::value<string>()->default_value("out.txt"), "Output file containing the processed material information.")
		("output-format,t", po::value<string>()->default_value("wavenumber,n,k"), "Format string for the output file (similar to --input-format).")
		("scaling,s", po::value<ptype>()->default_value(1.0), "Scaling value for the absorbance parameter. This value gives the thickness (in microns) of the measured material.")
		("n0,n", po::value<ptype>()->default_value(1.48), "Average effective refractive index. This is required when computing the real refractive index from the absorption.")
		("padding,p", po::value<int>()->default_value(2), "Padding factor used to remove edge artifacts in the Kramers-Kronig computation for computing the real RI from absorption. The default value of p=2 is sufficient in most cases.")
		("resolution,r", po::value<int>(), "Resolution of the spectrum. The default value is based on the number of spectral samples provided in the input file.")
		("reverse,v", "reverse the order of the output file");

	po::positional_options_description pos;
	pos.add("input-file", 1);
	pos.add("output-file", 1);

	po::variables_map vm;
	po::store(po::command_line_parser(argc, argv).options(desc).positional(pos).run(), vm);
	po::notify(vm);

	if(vm.count("help"))
	{
		cout<<desc<<endl;
		return 1;
	}

	//if the input file is given, load it, otherwise exit
	if(vm.count("input-file"))
	{
		M.fromFile(vm["input-file"].as<string>(),
				   vm["input-format"].as<string>(),
				   1.0 / vm["scaling"].as<ptype>());
	}
	else
	{
		cout<<"No input file was provided."<<endl;
		exit(1);
	}

	//the default sample rate of the spectrum is given by the number of samples in the input file
	int R = M.nSamples();
	if(vm.count("resolution"))
		R = vm["resolution"].as<int>();

	//compute the real refractive index
	rts::material<ptype> N = M.computeN(vm["n0"].as<ptype>(),
										R,
										vm["padding"].as<int>());

	//output the file using the standard format
	bool reverse_order = false;
	if(vm.count("reverse"))
        reverse_order = true;
	N.save(vm["output-file"].as<string>(), vm["output-format"].as<string>(), reverse_order);

	return 0;
}
