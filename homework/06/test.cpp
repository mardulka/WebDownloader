#ifndef __PROGTEST__

#include <cstring>
#include <cassert>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cctype>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stdexcept>
#include <algorithm>
#include <typeinfo>
#include <unordered_map>
#include <unordered_set>
#include <memory>

using namespace std;
#endif /* __PROGTEST__ */

class CDataTypeInt {
    // todo
};

class CDataTypeDouble {
    // todo
};

class CDataTypeEnum {
    // todo
};

class CDataTypeStruct {
    // todo
};

class CDataTypeArray {
    // todo
};

class CDataTypePtr {
    // todo
};

#ifndef __PROGTEST__

static bool whitespaceMatch(const string &a, const string &b) {
    // todo
    return true;
}

template<typename T_>
static bool whitespaceMatch(const T_ &x, const string &ref) {
    ostringstream oss;
    oss << x;
    return whitespaceMatch(oss.str(), ref);
}

#endif /* __PROGTEST__ */