#include <stdexcept>

class Solution {
   public:
    int romanToInt(std::string s) {
        int curr = 0,  // Current numeral character being processed, expressed
                       // as an int
            max = 0,  // Maximum numeral character encountered so far, expressed
                      // as an int
            total = 0;  // Accumulation of all numerals (addends and
                        // subtrahends) encountered so far

        for (auto iter = s.rbegin(); iter != s.rend();
             iter++) {  // Iterating through s in reverse order
            curr = romanCharToInt(
                *iter);  // Fetching the `int` representation of the current
                         // numeral character being processed

            if (curr > max)  // Self-explanatory
                max = curr;  //

            if (curr == max)  // As in VI or II
                              //       ^     ^
                total += curr;
            else  // As in IV
                  //       ^
                total -= curr;
        }

        return total;
    }

    inline int const romanCharToInt(char const& c) {
        /* Faster than unordered_map */
        switch (c) {
            case 'I':
                return 1;
            case 'V':
                return 5;
            case 'X':
                return 10;
            case 'L':
                return 50;
            case 'C':
                return 100;
            case 'D':
                return 500;
            case 'M':
                return 1000;
            default:
                throw std::invalid_argument(
                    "Roman numeral character not recognised.");
        }
    }
};
