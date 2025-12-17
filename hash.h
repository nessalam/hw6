#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

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
        //if empty strings
        if(k.empty()){
          return 0;
        }

        //array to process string
        unsigned long long w[5] = {0, 0, 0, 0, 0};

        //# of groups needed
        int len = k.length(); 
        int wIndex = 4; 

        //processing string from end to beginning (reverse)
        for(int i = len - 1; i >= 0; i -= 6){
          unsigned long long groupValue = 0;

          //processing up to 6 chars
          for(int j = 0; j < 6; j++){
            //calculating pos in string
            int charPos = i - (5 - j);

            if(charPos >= 0){
              char c = k[charPos];
              HASH_INDEX_T digit = letterDigitToNumber(c);
              groupValue = groupValue * 36 + digit;
            }
            else{
              //no char at curr pos = 0
              groupValue = groupValue * 36;
            }
          }
          w[wIndex] = groupValue;
          wIndex--;

          //stop if all groups processed
          if(wIndex < 0){
            break;
          }
        }

        //final hash
        unsigned long long result = 0;
        for(int i = 0; i < 5; i++){
          result += rValues[i] * w[i];
        }
      return result;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        //check if digit
        if(letter >= '0' && letter <= '9'){
          return 26 + (letter - '0'); //converts digits to integral vals 26-35
        }

        //converting to lowercase letters
        char lowerLetter = letter;
        if(letter >= 'A' && letter <= 'Z'){
          lowerLetter = letter + ('a' - 'A'); 
        }

        return lowerLetter - 'a';
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
