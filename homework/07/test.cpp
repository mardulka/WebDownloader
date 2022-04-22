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


/**
 * Templated class
 * @tparam T_ Type which should be indexed. Expected STRING, LIST<STRING> and VECTOR<STRING>
 * @tparam C_ Comparator, not mandatory. Expected LAMBDA, FUNCTOR, FUNCTION POINTER.
 */
template<typename T_, typename C_ = less<typename T_::const_reference>>
class CIndex{

    /**
     * Storge of indexing
     */
    T_ m_storage;

    /**
     * Comparating function, which providing required operator <
     */
    C_ m_cmp;

public:

    /**
     * Constructor
     * @param storage Storafe for indexing
     * @param cmp Comparing function
     */
    explicit CIndex(const T_ & storage, const C_ & cmp = less<typename T_::const_reference>()) : m_storage(storage),
                                                                                                 m_cmp(cmp){}

    /**
     * Method for indexing query matches.
     * @param query Query of elements which occurrences is searched inside indexed type.
     * @return Set of indexes where the match begins.
     */
    set<size_t> search(T_ query) const{
        auto result = set<size_t>();

        size_t i = 0;
        for (auto it = m_storage.begin() ; it != m_storage.end() ; ++it, ++i){
            auto s_it = it;
            auto q_it = query.begin();
            bool fit = true;
            for (; q_it != query.end() && s_it != m_storage.end() ; ++s_it, ++q_it){
                if (m_cmp(*s_it, *q_it) || m_cmp(*q_it, *s_it)){
                    fit = false;
                    break;
                }
            }

            //break before query end
            if (q_it != query.end())
                continue;

            //storing into set i position
            if (fit)
                result.insert(i);
        }

        return result;
    }

};

