/**************************
By Yiwen (Chris) Shen
Apr 26, 2016

Collect simulation data
Main tasks:
1. scan target directory to get file name
2. parse file name
3. read last line of each file
4. save data into vector
5. calculate statistic information, e.g. mean, variance, confidence intervals, CDF
6. save data to file for GNU Plot

Compile command:
g++ -DDEBUG -std=c++11 -o plotScript.o plotScript.cpp plotScript.h

Using C++ standard 11

Debug with arg: -DDEBUG

***************************/

#include <string.h>
#include <iostream>
#include <stdio.h>

#include <vector>
#include <cstdlib>
#include <ctime>
#include <sstream>

#include <fstream>
#include <limits>

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <map>
#include <iomanip>      // std::setw
#include <algorithm>    // std::sort
#include <tuple>        // std::tuple, std::get, std::tie, std::ignore

using namespace std;

typedef map< float, vector<double> > dataMapVecType;
typedef map< float, double> dataMapType;
typedef multimap<float, double> dataMultiMapType;
typedef multimap<float, map< float, double> > dataMultiMapMapType;
typedef vector< tuple<float, float, double> > dataVecTupType;

std::istream& ignoreline(std::ifstream&, std::ifstream::pos_type&);

std::string getLastLine(std::ifstream&);

vector<double> lineDataReturn( string );

/** save data into dataMapVecType
*	input: index, line data, ,key(x or y axis)
*/
void saveDelay( int, vector<double>, dataMapVecType&, float );

// void saveDelay( int, vector<double>, map< int, vector<double> >&, float );

dataMapType computeAverage( dataMapVecType );

dataMapType computePercentage( dataMapType, int );

/** save data into dataMultiMapMapType, it is shared data
	it need to be called several times to save complete 3D data
*/
void combine3DData( dataMapType, float, dataVecTupType& );

dataMapType computeVariance( dataMapVecType, dataMapType );

dataMapType computeConfiInterval( dataMapVecType, dataMapType );

dataMultiMapType getCDF( dataMapVecType );

void saveDataToFile(string, dataMapType, dataMapType );

void saveDataToFile(string, dataMultiMapType );

void saveDataToFile(string, dataMapType );
