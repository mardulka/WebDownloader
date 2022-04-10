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
    size_t m_size;
public:
    explicit CDataType(string type = "", size_t size = 0) : m_type{std::move(type)}, m_size{size}{}

    [[nodiscard]] virtual size_t getSize() const;
    [[nodiscard]] virtual string getType() const;
    virtual bool operator ==(const CDataType & rhs) const;
    virtual bool operator !=(const CDataType & rhs) const;
    [[nodiscard]] virtual string printBody(int offset) const;
    [[nodiscard]] virtual CDataType * clone() const = 0;
    friend ostream & operator <<(ostream & os, const CDataType & an_int);
};

size_t CDataType::getSize() const{
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

string CDataType::printBody(int offset) const{
    string text;
    return text.append(offset, ' ').append(m_type);
}

ostream & operator <<(ostream & os, const CDataType & an_int){
    os << an_int.printBody(0);
    return os;
}

/**
 * Class dor INT type
 */
class CDataTypeInt : public CDataType{
public:
    explicit CDataTypeInt() : CDataType("int", 4){}

    [[nodiscard]] CDataType * clone() const override;
};

CDataType * CDataTypeInt::clone() const{
    return new CDataTypeInt();
}

/**
 * Class for DOUBLE type
 */
class CDataTypeDouble : public CDataType{
public:
    explicit CDataTypeDouble() : CDataType("double", 8){}

    [[nodiscard]] CDataType * clone() const override;
};

CDataType * CDataTypeDouble::clone() const{
    return new CDataTypeDouble();
}

/**
 * Class for ENUM type
 */
class CDataTypeEnum : public CDataType{
    vector<string> options;
public:
    explicit CDataTypeEnum() : CDataType("enum"s, 4){}

    CDataTypeEnum(const CDataTypeEnum & source);
    CDataTypeEnum(CDataTypeEnum && source) noexcept;
    CDataTypeEnum & operator =(CDataTypeEnum source);

    CDataTypeEnum & add(const string & name);
    [[nodiscard]] string printBody(int offset) const override;
    bool operator ==(const CDataType & rhs) const override;
    bool operator !=(const CDataType & rhs) const override;
    [[nodiscard]] CDataType * clone() const override;
};

CDataTypeEnum::CDataTypeEnum(const CDataTypeEnum & source) : CDataTypeEnum(){
    m_type = source.m_type;
    m_size = source.m_size;
    for (const auto & item: source.options){
        options.push_back(item);
    }
}

CDataTypeEnum::CDataTypeEnum(CDataTypeEnum && source) noexcept{
    m_type = source.m_type;
    m_size = source.m_size;
    swap(options, source.options);
}

CDataTypeEnum & CDataTypeEnum::operator =(CDataTypeEnum source){
    swap(options, source.options);
    return *this;
}

CDataTypeEnum & CDataTypeEnum::add(const string & name){
    options.push_back(name);
    return *this;
}

string CDataTypeEnum::printBody(int offset) const{
    string text;
    text.append(offset, ' ').append("enum\n");
    text.append(offset, ' ').append("{\n");
    for (const auto & item: options){
        text.append(offset + 2, ' ').append(item);
        if (item == options.back())
            text.append("\n");
        else
            text.append(",\n");
    }
    text.append(offset, ' ').append("}");
    return text;
}

bool CDataTypeEnum::operator ==(const CDataType & rhs) const{
    if (this->m_type != rhs.getType())
        return false;
    const auto & compared = dynamic_cast<const CDataTypeEnum &>(rhs);
    if (this->options.size() != compared.options.size())
        return false;
    for (size_t i = 0 ; i < options.size() ; ++i){
        if (options[i] != compared.options[i])
            return false;
    }
    return true;
}

bool CDataTypeEnum::operator !=(const CDataType & rhs) const{
    return !(*this == rhs);
}

CDataType * CDataTypeEnum::clone() const{
    auto * clonedType = new CDataTypeEnum();
    for (const auto & item: this->options){
        clonedType->options.push_back(item);
    }
    return clonedType;
}

/**
 * Class for STRUCT type
 */
class CDataTypeStruct : public CDataType{
    map<string, shared_ptr<CDataType>> used_names;
    vector<pair<string, shared_ptr<CDataType>>> fields;
public:
    explicit CDataTypeStruct() : CDataType("struct"s, 0){}

    CDataTypeStruct(const CDataTypeStruct & source);
    CDataTypeStruct(CDataTypeStruct && source) noexcept;
    CDataTypeStruct & operator =(CDataTypeStruct source);

    CDataTypeStruct & addField(const string & name, const CDataType & type);
    const CDataType & field(const string & name);

    [[nodiscard]] string printBody(int offset) const override;
    [[nodiscard]] CDataType * clone() const override;
    bool operator ==(const CDataType & rhs) const override;
    bool operator !=(const CDataType & rhs) const override;
};

CDataTypeStruct::CDataTypeStruct(const CDataTypeStruct & source) : CDataTypeStruct(){
    m_type = source.m_type;
    m_size = source.m_size;

    for (const auto & item: source.fields){
        fields.emplace_back(item.first, item.second->clone());
    }
    for (const auto & item: fields){
        used_names.emplace(item.first, item.second);
    }
}

CDataTypeStruct::CDataTypeStruct(CDataTypeStruct && source) noexcept{
    m_type = source.m_type;
    m_size = source.m_size;
    swap(used_names, source.used_names);
    swap(fields, source.fields);
}

CDataTypeStruct & CDataTypeStruct::operator =(CDataTypeStruct source){
    swap(used_names, source.used_names);
    swap(fields, source.fields);
    return *this;
}

CDataTypeStruct & CDataTypeStruct::addField(const string & name, const CDataType & type){
    if (used_names.find(name) != used_names.end()){
        throw invalid_argument("Duplicate field: " + name);
    }
    auto element = shared_ptr<CDataType>(type.clone());
    used_names.insert({name, element});
    fields.emplace_back(name, element);
    m_size += element->getSize();
    return *this;
}

const CDataType & CDataTypeStruct::field(const string & name){
    auto element = used_names.find(name);
    if (element == used_names.end())
        throw invalid_argument("Unknown field: " + name);

    return *(element->second);
}

string CDataTypeStruct::printBody(int offset) const{
    string text;
    text.append(offset, ' ').append("struct\n");
    text.append(offset, ' ').append("{\n");
    for (const auto & item: fields){
        text.append(item.second->printBody(offset + 2)).append(" ").append(item.first).append(";\n");
    }
    text.append(offset, ' ').append("}");
    return text;
}

CDataType * CDataTypeStruct::clone() const{
    auto * clonedType = new CDataTypeStruct();
    for (const auto & item: fields){
        clonedType->fields.emplace_back(item.first, shared_ptr<CDataType>(item.second->clone()));
    }
    for (const auto & item: clonedType->fields){
        clonedType->used_names.emplace(item.first, item.second);
    }

    return clonedType;
}

bool CDataTypeStruct::operator ==(const CDataType & rhs) const{
    if (this->m_type != rhs.getType())
        return false;

    const auto & compared = dynamic_cast<const CDataTypeStruct &>(rhs);
    if (fields.size() != compared.fields.size())
        return false;
    for (size_t i = 0 ; i < fields.size() ; ++i){
        if (*(fields[i].second) != *(compared.fields[i].second))
            return false;
    }

    return true;
}

bool CDataTypeStruct::operator !=(const CDataType & rhs) const{
    return !(*this == rhs);
}

/*

*/
/**
 * Class for ARRAY type
 *//*

class CDataTypeArray : public CDataType{
    // todo
};

*/
/**
 * Class for POINTER type
 *//*

class CDataTypePtr : public CDataType{
    // todo
};

*/
