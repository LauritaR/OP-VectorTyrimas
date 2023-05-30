/**

*@brief This header file includes necessary libraries and defines several using statements.
*/
#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <limits>
#include <memory>
#include <time.h>
#include <fstream>
#include <sstream>
#include <chrono>
#include"vector.h" 
#include<random>
#include<locale.h>
#include <clocale>
#include<deque>
#include <execution>
#include <stdexcept>
#include<initializer_list>
#include<list>
#include<Windows.h>
using std::allocator;
using std::wcout;
using std::setlocale;
using std::partition;
using std::exit;
using std::list;
using std::deque;
using std::move;
using std::cout;
using std::cin;
using std::ios;
using std::endl;
using std::setlocale;
using std::back_inserter;
using std::left;
using std::right;
using std::setw;
using std::copy;
using std::setprecision;
using std::string;
using std::flush;
using std::sort;
using std::vector;
using std::getline;
using std::fixed;
using std::stringstream;
using std::runtime_error;
using std::ifstream;
using std::ofstream;
using std::cerr;
using std::istringstream;
using std::move;
/**

*@brief The RandInt class generates a random integer between a given low and high value.
*/
class RandInt{
    public:
    /**
        *@brief Construct a new RandInt object with the given low and high values.
        *
        * @param low The lower bound for the generated integer.
        * @param high The upper bound for the generated integer.
    */
    RandInt(int low,int high): mt{rd()},dist{low,high}{}
     /**
  * @brief Generates a random integer between the low and high values.
  * 
  * @return int A random integer between the low and high values.
  */
    int operator()(){return dist(mt);}
    private:
    std::random_device rd;
    std::mt19937 mt;
    std::uniform_int_distribution<int> dist;
};
