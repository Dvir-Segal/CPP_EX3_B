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
#include <queue>
#include "NumberWithUnits.hpp"
using namespace std;

namespace ariel{
    map<string, map<string, double>> NumberWithUnits::table;
    const double ep = 0.001;

    NumberWithUnits::NumberWithUnits(const double& s, const string& t){
        if (NumberWithUnits::table.find(t) == NumberWithUnits::table.end()){
            throw out_of_range("thr type does not exist");
        }
        this->size = s;
        this->typeOfSize = t;
    }

    void NumberWithUnits::read_units(ifstream& file){
        string line;
        while (getline(file, line)){
            size_t indexCompare = line.find_first_of('=');
            string typeLeft = line.substr(1, indexCompare-1);
            typeLeft = typeLeft.substr(typeLeft.find_first_not_of(' '), typeLeft.find_last_not_of(' ')-typeLeft.find_first_not_of(' ')+1);
            string partRight = line.substr(indexCompare+1);
            partRight = partRight.substr(partRight.find_first_not_of(' '));
            double amount = stod(partRight.substr(0, partRight.find_first_of(' ')));
            partRight = partRight.substr(partRight.find_first_of(' '));
            string typeRight = partRight.substr(partRight.find_first_not_of(' '));
            NumberWithUnits::table[typeLeft][typeRight] = amount;
            NumberWithUnits::table[typeRight][typeLeft] = 1/amount;
        }
    }

    double NumberWithUnits::bfs(const string& t1, const string& t2){
        if (t1==t2){
            return 1;
        }
        map <string, double> tracking;
        queue<string> q;
        tracking[t1] = 1;
        q.push(t1);
        string u;
        while (!q.empty()){
            u = q.front();
            q.pop();
            for (auto i = NumberWithUnits::table[u].begin(); i != NumberWithUnits::table[u].end(); i++){
                if (tracking.find(i->first) == tracking.end()){
                    tracking[i->first] = (i->second)*tracking[u];
                    if (i->first == t2){
                        return tracking[i->first];
                    }
                    q.push(i->first);
                }
            }   
        }
        return -1;
    }

    NumberWithUnits operator+(const NumberWithUnits& a, const NumberWithUnits& b){
        double outcome = NumberWithUnits::bfs(a.typeOfSize, b.typeOfSize);
        if (outcome < 0){
            throw out_of_range("Invalid Operation\n");
        }
        NumberWithUnits c{a.size+(b.size/outcome), a.typeOfSize};
        return c;
    }

    NumberWithUnits& NumberWithUnits::operator+=(const NumberWithUnits& b){
        string a = this->typeOfSize;
        double outcome = NumberWithUnits::bfs(a, b.typeOfSize);
        if (outcome < 0){
            throw out_of_range("Invalid Operation\n");
        }
        this->size = this->size + b.size/outcome;
        return *this;
    }

     NumberWithUnits operator-(const NumberWithUnits& a, const NumberWithUnits& b){
        double outcome = NumberWithUnits::bfs(a.typeOfSize, b.typeOfSize);
        if (outcome < 0){
            throw out_of_range("Invalid Operation\n");
        }
        NumberWithUnits c{a.size-b.size/outcome, a.typeOfSize};
        return c;
    }

    NumberWithUnits& NumberWithUnits::operator-=(const NumberWithUnits& b){
        string a = this->typeOfSize;
        double outcome = NumberWithUnits::bfs(a, b.typeOfSize);
        if (outcome < 0){
            throw out_of_range("Invalid Operation\n");
        }
        this->size = this->size - b.size/outcome;
        return *this;
    }

    NumberWithUnits NumberWithUnits::operator-(){
        return NumberWithUnits(-(this->size), this->typeOfSize);
    }

    NumberWithUnits operator*(const NumberWithUnits& a, double x){
        NumberWithUnits result(a.size*x,a.typeOfSize);
        return result;
    }

    NumberWithUnits operator*(double x, const NumberWithUnits& a){
        return a*x;
    }

    bool operator>(const NumberWithUnits& a, const NumberWithUnits& b){
        double outcome = NumberWithUnits::bfs(a.typeOfSize, b.typeOfSize);
        if (outcome < 0){
            throw out_of_range("Invalid Operation\n");
        }
        return (a.size*outcome > b.size && a!=b);
    }

    bool operator>=(const NumberWithUnits& a, const NumberWithUnits& b){
        return (a==b || a>b);
    }
    bool operator==(const NumberWithUnits& a, const NumberWithUnits& b){
        double outcome = NumberWithUnits::bfs(a.typeOfSize, b.typeOfSize);
        if (outcome < 0){
            throw out_of_range("Invalid Operation\n");
        }
        return (abs((b.size/outcome)-(a.size)) < ep);
    }

    bool operator<(const NumberWithUnits& a, const NumberWithUnits& b){
        return (a!=b && !(a>b));
    }

    bool operator<=(const NumberWithUnits& a, const NumberWithUnits& b){
        return (a==b || a<b);
    }
    bool operator!=(const NumberWithUnits& a, const NumberWithUnits& b){
        return !(a==b);
    }

    NumberWithUnits& NumberWithUnits::operator++(){
        this->size++;
        return *this;
    }

    NumberWithUnits NumberWithUnits::operator++(int flag){
        NumberWithUnits copy = *this;
        this->size++;
        return copy;
    }

    NumberWithUnits& NumberWithUnits::operator--(){
        this->size--;
        return *this;
    }
                
    NumberWithUnits NumberWithUnits::operator--(int flag){
        NumberWithUnits copy = *this;
        this->size--;
        return copy;
    }

    istringstream& operator>>(istringstream& input, NumberWithUnits& a){
      size_t indexRightBarr = 0;
      string type;
      char lBarr= 0;
      char rBarr = 0;
      double size = 0;
      input >> size >> lBarr >> type;
      if (type.find(']', 0) == string::npos){
         input >> rBarr;
      }
      else{
         indexRightBarr = type.find(']', 0);
         type = type.substr(0, indexRightBarr);
      }
      if (NumberWithUnits::table.find(type) == NumberWithUnits::table.end()){
        throw out_of_range("the type does not exist");
      }
      a.size = size;
      a.typeOfSize = type;
      return input;
    }

    ostream& operator<<(ostream& os, const NumberWithUnits& input){
        os << input.size << "[" << input.typeOfSize << "]";
        return os;
    }
}

