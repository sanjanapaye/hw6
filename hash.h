#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
using namespace std;
typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        unsigned long long w[5] = {0, 0, 0, 0, 0};
        
		int length = k.length(); 

		for (int i = length-1; i >= 0; i-=6){
			unsigned long long new_w =0;
            if(i > 5){
                for (int j = i; j > i-6; --j){
                    HASH_INDEX_T letter = letterDigitToNumber(k[j]);
                    new_w += letter*pow(36, i-j);
                }
                w[4-(length/6-(i+1)/6)] = new_w;
            }else{
                for (int j = i; j >= 0; --j){
                    HASH_INDEX_T letter = letterDigitToNumber(k[j]);
                    new_w += letter*pow(36, i-j);
                }
                w[4-(length/6-(i+1)/6)] = new_w;
            }
		}
        return rValues[0]*w[0]+rValues[1]*w[1]+rValues[2]*w[2]+rValues[3]*w[3]+rValues[4]*w[4];

    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
			char letter1 = tolower(letter);
			if (letter1 >= 'a' && letter1 <= 'z'){
				return static_cast<HASH_INDEX_T>(letter1 - 'a');
			}else if (letter1>='0'&&letter1<='9'){
				return static_cast<HASH_INDEX_T>(letter1 - '0'+26);
			}
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
