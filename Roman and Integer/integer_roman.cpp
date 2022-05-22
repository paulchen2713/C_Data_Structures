#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <stdexcept>

std::string int2Roman(int num) {
    // 1 - I    10  - X     100 - C
    // 2 - II   20  - XX    200 - CC
    // 3 - III  30  - XXX   300 - CCC
    
    // 4 - IV   40  - XL    400 - CD
    
    // 5 - V    50  - L     500 - D
    // 6 - VI   60  - LX    600 - DC
    // 7 - VII  70  - LXX   700 - DCC
    // 8 - VIII 80  - LXXX  800 - DCCC
    
    // 9 - IX   90  - XC    900 - CM
    
    // n == 0, x == 1994 / 1000 == 1...994, result = "M"
    // n == 2, x ==  994 / 100  == 9...94,  result = "M C M"
    // n == 4, x ==   94 / 10   == 9...4,   result = "MCM X C"
    // n == 6, x ==    4 / 1    == 4...0,   result = "MCMXC I V"
    // num = 1994, result = "M CM XC IV"
    
    std::string result = "";
    std::vector<char> roman{'M', 'D', 'C', 'L', 'X', 'V', 'I'};
    std::vector<int>  value{1000, 500, 100, 50, 10, 5, 1};
    for (int n = 0; n <= 6; n += 2) {
        int x = num / value[n];
        if (x < 4) {
            for (int i = 1; i <= x; i++) {
                result += roman[n];
            }
        } 
        else if (x == 4) {
            result = result + roman[n] + roman[n - 1];
        } 
        else if (x > 4 && x < 9) {
            result += roman[n - 1];
            for (int i = 6; i <= x; i++) {
                result += roman[n];
            }
        } 
        else if (x == 9) {
            result = result + roman[n] + roman[n - 2];
        }
        num %= value[n];
    }
    return result;
}

int roman2Int(std::string s) {
    int result = 0;
    std::unordered_map<char, int> map_{{'I', 1}, {'V', 5}, {'X', 10}, {'L', 50}, 
                                       {'C', 100}, {'D', 500}, {'M', 1000}};
    for (unsigned int i = 0; i < s.size(); i++) {
        if (i == s.size() - 1 || map_[s[i + 1]] <= map_[s[i]]) {
            result += map_[s[i]];
        }
        else {
            result -= map_[s[i]];
        }
    }
    return result;
}

int main() {
    int t;
    std::cout << "please enter the number of instances: ";
    std::cin >> t;
    while (t--) {
        int N = 0, recoverInt = 0;
        std::cin >> N;
        if (N < 1 || N > 3999) {
            throw std::invalid_argument( "received value less than 1 or value over 3999" );
        }
        std::string s = int2Roman(N);
        std::cout << "Integer " << N << " in Roman is: " << s << std::endl;
        recoverInt = roman2Int(s);
        std::cout << "Roman " << s << "in Integer is: " << recoverInt << std::endl;
    }
    std::cout << std::endl;

    return 0;
}


