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
#include <utility>
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

/**
 * Abstract class. Common ancestor for all types.
 */
class CDataType{
protected:
    string m_type;
    int m_size;
public:
    explicit CDataType(string type = "", int size = 0) : m_type{std::move(type)}, m_size{size}{}

    [[nodiscard]] virtual int getSize() const;
    [[nodiscard]] virtual string getType() const;
    virtual bool operator ==(const CDataType & rhs) const;
    virtual bool operator !=(const CDataType & rhs) const;
    [[nodiscard]] virtual string exportBody(const string & name, int offset) const;
    friend ostream & operator <<(ostream & os, const CDataType & an_int);
};

int CDataType::getSize() const{
    return m_size;
}

string CDataType::getType() const{
    return m_type;
}

bool CDataType::operator ==(const CDataType & rhs) const{
    if (rhs.getType() == this->m_type)
        return true;
    return false;
}

bool CDataType::operator !=(const CDataType & rhs) const{
    return !(*this == rhs);
}

string CDataType::exportBody(const string & name, int offset) const{
    string text;
    return text.append(offset, ' ').append(m_type).append(" ").append(name).append("\n");
}

ostream & operator <<(ostream & os, const CDataType & an_int){
    os << an_int.exportBody("", 0);
    return os;
}

/**
 * Class dor INT type
 */
class CDataTypeInt : public CDataType{
public:
    explicit CDataTypeInt() : CDataType("int"s, 4){}
};

/**
 * Class for DOUBLE type
 */
class CDataTypeDouble : public CDataType{
public:
    explicit CDataTypeDouble() : CDataType("double"s, 8){}
};

/**
 * Class for ENUM type
 */
class CDataTypeEnum : public CDataType{
    vector<string> options;
public:
    explicit CDataTypeEnum() : CDataType("enum"s, 4){}

    CDataTypeEnum & add(const string & name);
    [[nodiscard]] string exportBody(const string & name, int offset) const override;
};

CDataTypeEnum & CDataTypeEnum::add(const string & name){
    options.push_back(name);
    return *this;
}

string CDataTypeEnum::exportBody(const string & name, int offset) const{
    string text;
    text.append(offset, ' ').append("enum\n");
    text.append(offset, ' ').append("{\n");
    for (auto item: options){
        text.append(offset + 2, ' ').append(item).append("\n");
    }
    text.append("} ").append(name).append(";\n");
}

/**
 * Class for STRUCT type
 */
class CDataTypeStruct : public CDataType{
    set<string> used_names;
    vector<pair<string, CDataType *>> fields;
public:
    explicit CDataTypeStruct() : CDataType("struct"s, 0){}

    CDataTypeStruct & addField(const string & name, CDataType * type);
    [[nodiscard]] string exportBody(const string & name, int offset) const override;
};

CDataTypeStruct & CDataTypeStruct::addField(const string & name, CDataType * type){
    if (used_names.find(name) != used_names.end())
        throw invalid_argument("Duplicate field: m_Status");
    used_names.insert(name);
    fields.emplace_back(make_pair(name, type));
    return *this;
}

string CDataTypeStruct::exportBody(const string & name, int offset) const{
    string text;
    text.append(offset, ' ').append("struct\n");
    text.append(offset, ' ').append("{\n");
    for (auto item: fields){
        text.append(offset + 2, ' ').append(item.second->getType());
        text.append(" ").append(item.first).append(";\n");
    }
    text.append(offset, ' ').append("}").append(name);
    return text;
}

/**
 * Class for ARRAY type
 */
class CDataTypeArray : public CDataType{
    // todo
};

/**
 * Class for POINTER type
 */
class CDataTypePtr : public CDataType{
    // todo
};
