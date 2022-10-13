#include "Constants.h"
using namespace std;


Constants::Constants()
{
}

Constants::~Constants()
{
}

ALG Constants::ALGORITHM = aDFS;
DATATYPE Constants::DATA = Social;
int Constants::NUM_THREAD = 70;
double Constants::DELTA = 1.0;
int Constants::K = 3;
int Constants::BUDGET = 10;
int Constants::M = 3;
int Constants::start = 0;
int Constants::end = 12;
string Constants::FILEIN = "input.in";
int Constants::n_nodes = 20;
int Constants::limit = 10;


// for social
double Constants::EPS = 0.5;
int Constants::NO_DENOISE_STEPS = 2;

// for sensor
//double Constants::EPS = 0.0;
//int Constants::NO_DENOISE_STEPS = 1;