#include <string>
#pragma once
using namespace std;
enum DATATYPE { Social, Sensor };
enum ALG {aDFS, aBFS, aIDS, aUCS, abestFS};

class Constants
{
public:
	Constants();
	~Constants();
	
	static ALG ALGORITHM;
	static DATATYPE DATA;
	static int NUM_THREAD;
	static int BUDGET;
	static int K;
	static int M;
	static double EPS;
	static double DELTA; // for streaming algorithm
	static int NO_DENOISE_STEPS; // steps for eps' = 0 reach epsilon 
	static int start;
	static int end;
	static string FILEIN;
	static int n_nodes;
	static int limit;
};


