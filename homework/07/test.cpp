#ifndef __PROGTEST__

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <cctype>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <set>
#include <list>
#include <map>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include <functional>
#include <memory>
#include <numeric>
#include <optional>
#include <variant>
#include <any>

using namespace std;
#endif /* __PROGTEST__ */

/*
template<typename T_>
bool comp = [](T_ a, T_ b){return a < b;};
*/

template<typename T_, typename C_ = int>
class CIndex{


    T_ storage;

public:

    explicit CIndex(T_ storage) : storage(storage){}

    //explicit CIndex(T_ && storage) : storage(move(storage)){}

    set<size_t> search(T_ query) const{
        auto result = set<size_t>();

        for (size_t i = 0 ; i < storage.size() ; ++i){
            size_t j = i;
            size_t k = 0;
            bool fit = true;
            for (; k < query.size() && j < storage.size() ; ++j, ++k){
                if (storage[j] < query[k] || query[k] < storage[j]){
                    fit = false;
                    break;
                }
            }
            if (k < query.size())
                continue;


            //storing into set i position
            if (fit)
                result.insert(i);
        }

        return result;
    }

};



