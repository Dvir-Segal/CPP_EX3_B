#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <climits>
#include <unordered_map>
#include <map>
#include <bits/stdc++.h>
#include <utility>
using namespace std;

namespace ariel{
    class NumberWithUnits{
        double size = 0;
        string typeOfSize = "";
        static map<string, map<string, double>> table;   
        

        public:
            NumberWithUnits(const double& s, const string& t);
            ~NumberWithUnits(){};
            static void read_units(ifstream& file);
            static double bfs(const string& t1, const string& t2);
            friend bool epsilon(const NumberWithUnits& a, const NumberWithUnits& b, double& relation);
            friend NumberWithUnits operator+(const NumberWithUnits& a,const NumberWithUnits& b);
            NumberWithUnits& operator+=(const NumberWithUnits& b);
            NumberWithUnits& operator+(){return *this;};
            friend NumberWithUnits operator-(const NumberWithUnits& a,const NumberWithUnits& b);
            NumberWithUnits& operator-=(const NumberWithUnits& b);
            NumberWithUnits operator-();
            friend NumberWithUnits operator*(const NumberWithUnits& a, double x);
            friend NumberWithUnits operator*(double x, const NumberWithUnits& a);

            
            friend bool operator>(const NumberWithUnits& a, const NumberWithUnits& b);
            friend bool operator>=(const NumberWithUnits& a, const NumberWithUnits& b);
            friend bool operator==(const NumberWithUnits& a, const NumberWithUnits& b);
            friend bool operator<(const NumberWithUnits& a, const NumberWithUnits& b);
            friend bool operator<=(const NumberWithUnits& a, const NumberWithUnits& b);
            friend bool operator!=(const NumberWithUnits& a, const NumberWithUnits& b);

            NumberWithUnits& operator++();
            NumberWithUnits operator++(int flag);
            NumberWithUnits& operator--();
            NumberWithUnits operator--(int flag);

            friend istringstream& operator>>(istringstream& input, NumberWithUnits& a);
            friend ostream& operator<<(ostream& os, const NumberWithUnits& input);

    };
}