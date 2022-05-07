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
 * Enum for data types
 */
enum class CDataTypeValue{
    EMPTY, INT, DOUBLE, STRUCT, ENUM, ARRAY, POINTER
};

/**
 * Abstract class. Common ancestor for all types.
 */
class CDataType{
protected:
    CDataTypeValue m_type;
    size_t m_size;
    shared_ptr<CDataType> m_element;
public:
    /**
     * Constructor in abstract class for setting common fields.
     * @param type type name
     * @param size type size
     */
    explicit CDataType(CDataTypeValue type = CDataTypeValue::EMPTY, size_t size = 0) : m_type{type}, m_size{size}{}

    /**
     * Method getting type size. VIRTUAL
     * @return Type size.
     */
    [[nodiscard]] virtual size_t getSize() const;

    /**
     * Method getting type type. VIRTUAL
     * @return Type type.
     */
    [[nodiscard]] virtual CDataTypeValue getType() const;

    /**
     * Comparison operator. Comparing only same type. VIRTUAL
     * @param rhs Data type comparing with object type.
     * @return True if same. False if not.
     */
    virtual bool operator ==(const CDataType & rhs) const;

    /**
     * Comparison operator. Comparing only same type. VIRTUAL
     * @param rhs Data type comparing with object type.
     * @return True if different. True if same.
     */
    virtual bool operator !=(const CDataType & rhs) const;

    /**
     * Method returning proper formatted output of this type. VIRTUAL
     * @param offset Number of spaces from line start. For this type defined in parent printing.
     * @return String of printed output.
     */
    [[nodiscard]] virtual string printBody(int offset, string text) const;

    /**
     * Method cloning type. VIRTUAL
     * @return Pointer to new copy.
     */
    [[nodiscard]] virtual shared_ptr<CDataType> clone() const = 0;

    /**
     * Ostream operator for printing type.
     * @param os output stream
     * @param an_int Data type to be printed.
     * @return reference to output stream for chaining.
     */
    friend ostream & operator <<(ostream & os, const CDataType & an_int);

    /**
     * Return underlying element;
     * @return
     */
    [[nodiscard]] virtual const CDataType & element() const;

    /**
     * Method providing access to one nested type.
     * @param name name of nested type which should be provided
     * @return reference to required type or exception if not exists
     */
    [[nodiscard]] virtual const CDataType & field(const char * name) const;

    /**
     * Method providing access to one nested type.
     * @param name name of nested type which should be provided
     * @return reference to required type or exception if not exists
     */
    [[nodiscard]] virtual const CDataType & field(const string & name) const;
};

size_t CDataType::getSize() const{
    return m_size;
}

CDataTypeValue CDataType::getType() const{
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

string CDataType::printBody(int offset, string text) const{
    string printText;
    return printText.append(offset, ' ').append(text);
}

ostream & operator <<(ostream & os, const CDataType & an_int){
    os << an_int.printBody(0, "");
    return os;
}

const CDataType & CDataType::element() const{
    string text = "Cannot use element() for type: " + printBody(0, "");
    throw invalid_argument(text);
}

const CDataType & CDataType::field([[maybe_unused]] const char * name) const{
    string text = "Cannot use field() for type: " + printBody(0, "");
    throw invalid_argument(text);
}

const CDataType & CDataType::field([[maybe_unused]] const string & name) const{
    string text = "Cannot use field() for type: " + printBody(0, "");
    throw invalid_argument(text);
}

/**
 * Class dor INT type
 */
class CDataTypeInt : public CDataType{
public:
    /**
     * Default constructor. Calling parent constructor with defined parameters.
     */
    explicit CDataTypeInt() : CDataType(CDataTypeValue::INT, 4){}

    /**
     * Method cloning type. VIRTUAL
     * @return Pointer to new copy.
     */
    [[nodiscard]] shared_ptr<CDataType> clone() const override;

    /**
     * Method returning proper formatted output of this type. VIRTUAL
     * @param offset Number of spaces from line start. For this type defined in parent printing.
     * @return String of printed output.
     */
    [[nodiscard]] string printBody(int offset, string text) const override;

};

shared_ptr<CDataType> CDataTypeInt::clone() const{
    return shared_ptr<CDataType>(new CDataTypeInt());
}

string CDataTypeInt::printBody(int offset, string text) const{
    string printText;
    return printText.append(offset, ' ').append("int").append(text);
}

/**
 * Class for DOUBLE type
 */
class CDataTypeDouble : public CDataType{
public:
    /**
     * Default constructor. Calling parent constructor with defined parameters.
     */
    explicit CDataTypeDouble() : CDataType(CDataTypeValue::DOUBLE, 8){}

    /**
     * Method cloning type. VIRTUAL
     * @return Pointer to new copy.
     */
    [[nodiscard]] shared_ptr<CDataType> clone() const override;

    /**
     * Method returning proper formatted output of this type. VIRTUAL
     * @param offset Number of spaces from line start. For this type defined in parent printing.
     * @return String of printed output.
     */
    [[nodiscard]] string printBody(int offset, string text) const override;

};

shared_ptr<CDataType> CDataTypeDouble::clone() const{
    return shared_ptr<CDataType>(new CDataTypeDouble());
}

string CDataTypeDouble::printBody(int offset, string text) const{
    string printText;
    return printText.append(offset, ' ').append("double").append(text);
}

/**
 * Class for ENUM type
 */
class CDataTypeEnum : public CDataType{
    set<string> used_options;
    vector<string> options;
public:
    /**
     * Default constructor. Calling parent constructor with defined parameters.
     */
    explicit CDataTypeEnum() : CDataType(CDataTypeValue::ENUM, 4){}

    /**
     * Copy and move constructor and operator = with copy-swap approach. Ensuring deep copy.
     * @param source
     */
    CDataTypeEnum(const CDataTypeEnum & source);
    CDataTypeEnum(CDataTypeEnum && source) noexcept;
    CDataTypeEnum & operator =(CDataTypeEnum source);

    /**
     * Comparision operator. Comparing same type, same options with same order. VIRTUAL
     * @param rhs Data type comparing with object type.
     * @return True if same. False if not.
     */
    bool operator ==(const CDataType & rhs) const override;

    /**
     * Comparision operator. Comparing same type, same options with same order. VIRTUAL
     * @param rhs Data type comparing with object type.
     * @return True if different. True if same.
     */
    bool operator !=(const CDataType & rhs) const override;
    /**
     * Method returning proper formatted output of this type. VIRTUAL
     * @param offset Number of spaces from line start. For this type defined in parent printing.
     * @return String of printed output.
     */
    [[nodiscard]] string printBody(int offset, string text) const override;

    /**
     * Method cloning type. VIRTUAL
     * @return Pointer to new copy.
     */
    [[nodiscard]] shared_ptr<CDataType> clone() const override;

    /**
     * Method adding new option into this type.
     * @param name name of new option.
     * @return reference to object itself for chaining. Exception if type is already present.
     */
    CDataTypeEnum & add(const char * name);

    /**
     * Method adding new option into this type.
     * @param name name of new option.
     * @return reference to object itself for chaining. Exception if type is already present.
     */
    CDataTypeEnum & add(const string & name);
};

CDataTypeEnum::CDataTypeEnum(const CDataTypeEnum & source) : CDataTypeEnum(){
    m_type = source.m_type;
    m_size = source.m_size;
    for (const auto & item: source.options){
        options.push_back(item);
    }
    for (const auto & item: options){
        used_options.insert(item);
    }
}

CDataTypeEnum::CDataTypeEnum(CDataTypeEnum && source) noexcept{
    m_type = source.m_type;
    m_size = source.m_size;
    swap(options, source.options);
    swap(used_options, source.used_options);
}

CDataTypeEnum & CDataTypeEnum::operator =(CDataTypeEnum source){
    swap(options, source.options);
    return *this;
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

string CDataTypeEnum::printBody(int offset, string text) const{
    string printText;
    printText.append(offset, ' ').append("enum\n");
    printText.append(offset, ' ').append("{\n");
    for (const auto & item: options){
        printText.append(offset + 2, ' ').append(item);
        if (item == options.back())
            printText.append("\n");
        else
            printText.append(",\n");
    }
    printText.append(offset, ' ').append("}").append(text);
    return printText;
}

shared_ptr<CDataType> CDataTypeEnum::clone() const{
    shared_ptr<CDataTypeEnum> clonedType(new CDataTypeEnum());

    for (const auto & item: this->options){
        clonedType->add(item);
    }

    return clonedType;
}

CDataTypeEnum & CDataTypeEnum::add(const char * name){
    string sname{name};
    if (used_options.find(sname) != used_options.end())
        throw invalid_argument("Duplicate enum value: " + sname);
    options.push_back(sname);
    used_options.insert(sname);
    return *this;
}

CDataTypeEnum & CDataTypeEnum::add(const string & name){
    if (used_options.find(name) != used_options.end())
        throw invalid_argument("Duplicate enum value: " + name);
    options.push_back(name);
    used_options.insert(name);
    return *this;
}

/**
 * Class for STRUCT type
 */
class CDataTypeStruct : public CDataType{
    map<string, shared_ptr<CDataType>> used_names;
    vector<pair<string, shared_ptr<CDataType>>> fields;
public:
    /**
     * Default constructor. Calling parent constructor with defined parameters.
     */
    explicit CDataTypeStruct() : CDataType(CDataTypeValue::STRUCT, 0){}

    /**
     * Copy and move constructor and operator = with copy-swap approach. Ensuring deep copy.
     * @param source
     */
    CDataTypeStruct(const CDataTypeStruct & source);
    CDataTypeStruct(CDataTypeStruct && source) noexcept;
    CDataTypeStruct & operator =(CDataTypeStruct source);

    /**
     * Comparision operator. Comparing same type, same included types with same order. Names are not relevant. VIRTUAL
     * @param rhs Data type comparing with object type.
     * @return True if same. False if not.
     */
    bool operator ==(const CDataType & rhs) const override;

    /**
     * Comparision operator. Comparing same type, same included types with same order. Names are not relevant. VIRTUAL
     * @param rhs Data type comparing with object type.
     * @return True if different. True if same.
     */
    bool operator !=(const CDataType & rhs) const override;

    /**
     * Method returning proper formatted output of this type. VIRTUAL
     * @param offset Number of spaces from line start. For this type defined in parent printing.
     * @return String of printed output.
     */
    [[nodiscard]] string printBody(int offset, string text) const override;

    /**
     * Method cloning type. VIRTUAL
     * @return Pointer to new copy.
     */
    [[nodiscard]] shared_ptr<CDataType> clone() const override;

    /**
     * Method adding new nested type into this type.
     * @param name name of new type.
     * @param type Object of type which should be included.
     * @return reference to object itself for chaining. Exception if type name is already present.
     */
    CDataTypeStruct & addField(const char * name, const CDataType & type);

    /**
     * Method adding new nested type into this type.
     * @param name name of new type.
     * @param type Object of type which should be included.
     * @return reference to object itself for chaining. Exception if type name is already present.
     */
    CDataTypeStruct & addField(const string & name, const CDataType & type);

    /**
     * Method providing access to one nested type.
     * @param name name of nested type which should be provided
     * @return reference to required type or exception if not exists
     */
    const CDataType & field(const char * name) const override;

    /**
     * Method providing access to one nested type.
     * @param name name of nested type which should be provided
     * @return reference to required type or exception if not exists
     */
    [[nodiscard]] const CDataType & field(const string & name) const override;
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

string CDataTypeStruct::printBody(int offset, string text) const{
    string printText;
    printText.append(offset, ' ').append("struct\n");
    printText.append(offset, ' ').append("{\n");
    for (const auto & item: fields){
        printText.append(item.second->printBody(offset + 2, " " + item.first)).append(";\n");
    }
    printText.append(offset, ' ').append("}").append(text);
    return printText;
}

shared_ptr<CDataType> CDataTypeStruct::clone() const{
    shared_ptr<CDataTypeStruct> clonedType(new CDataTypeStruct());
    for (const auto & item: fields){
        clonedType->addField(item.first, *(item.second));
    }

    return clonedType;
}

CDataTypeStruct & CDataTypeStruct::addField(const char * name, const CDataType & type){
    string sname{name};
    if (used_names.find(sname) != used_names.end()){
        throw invalid_argument("Duplicate field: " + sname);
    }
    auto element = type.clone();
    used_names.insert({sname, element});
    fields.emplace_back(sname, element);
    m_size += element->getSize();
    return *this;
}

CDataTypeStruct & CDataTypeStruct::addField(const string & name, const CDataType & type){
    if (used_names.find(name) != used_names.end()){
        throw invalid_argument("Duplicate field: " + name);
    }
    auto element = type.clone();
    used_names.insert({name, element});
    fields.emplace_back(name, element);
    m_size += element->getSize();
    return *this;
}

const CDataType & CDataTypeStruct::field(const char * name) const{
    string sname{name};
    auto element = used_names.find(sname);
    if (element == used_names.end())
        throw invalid_argument("Unknown field: " + sname);

    return *(element->second);
}

const CDataType & CDataTypeStruct::field(const string & name) const{
    auto element = used_names.find(name);
    if (element == used_names.end())
        throw invalid_argument("Unknown field: " + name);

    return *(element->second);
}

/**
 * Class for ARRAY type
 */
class CDataTypeArray : public CDataType{
    size_t array_size;
public:
    CDataTypeArray(size_t size, const CDataType & type)
            : CDataType(CDataTypeValue::ARRAY, size * type.getSize()), array_size{size}{
        m_element = type.clone();
    }

    /**
     * Copy and move constructor and operator = with copy-swap approach. Ensuring deep copy.
     * @param source
     */
    CDataTypeArray(const CDataTypeArray & source);
    CDataTypeArray(CDataTypeArray && source) noexcept;
    CDataTypeArray & operator =(CDataTypeArray source);

    /**
     * Comparision operator. Comparing same type, same included types with same order. Names are not relevant. VIRTUAL
     * @param rhs Data type comparing with object type.
     * @return True if same. False if not.
     */
    bool operator ==(const CDataType & rhs) const override;

    /**
     * Comparision operator. Comparing same type, same included types with same order. Names are not relevant. VIRTUAL
     * @param rhs Data type comparing with object type.
     * @return True if different. True if same.
     */
    bool operator !=(const CDataType & rhs) const override;

    /**
     * Method returning proper formatted output of this type. VIRTUAL
     * @param offset Number of spaces from line start. For this type defined in parent printing.
     * @return String of printed output.
     */
    [[nodiscard]] string printBody(int offset, string text) const override;

    /**
     * Method cloning type. VIRTUAL
     * @return Pointer to new copy.
     */
    [[nodiscard]] shared_ptr<CDataType> clone() const override;

    /**
     * Method returning referenced element type. VIRTUAL
     * @return const reference to underlying element.
     */
    [[nodiscard]] const CDataType & element() const override;

};

CDataTypeArray::CDataTypeArray(const CDataTypeArray & source) : CDataType(source){
    m_type = source.m_type;
    m_size = source.m_size;
    array_size = source.array_size;
    m_element = {source.m_element->clone()};
}

CDataTypeArray::CDataTypeArray(CDataTypeArray && source) noexcept{
    m_type = source.m_type;
    m_size = source.m_size;
    array_size = source.array_size;
    swap(m_element, source.m_element);
}

CDataTypeArray & CDataTypeArray::operator =(CDataTypeArray source){
    m_type = source.m_type;
    m_size = source.m_size;
    array_size = source.array_size;
    swap(m_element, source.m_element);
    return *this;
}

bool CDataTypeArray::operator ==(const CDataType & rhs) const{
    if (this->m_type != rhs.getType())
        return false;

    if (array_size != rhs.getSize() || m_element->getType() != rhs.element().getType())
        return false;

    return true;
}

bool CDataTypeArray::operator !=(const CDataType & rhs) const{
    return !(*this == rhs);
}

string CDataTypeArray::printBody(int offset, string text) const{
    string printText;
    printText.append(text).append("[").append(to_string(array_size)).append("]");
    printText = element().printBody(offset, printText);
    return printText;
}

shared_ptr<CDataType> CDataTypeArray::clone() const{
    shared_ptr<CDataTypeArray> clonedType(new CDataTypeArray(array_size, *(m_element)));
    return clonedType;
}

const CDataType & CDataTypeArray::element() const{
    return *(m_element);
}

/**
 * Class for POINTER type
 */
class CDataTypePtr : public CDataType{

public:
    CDataTypePtr(const CDataType & type) : CDataType(CDataTypeValue::POINTER, 8){
        m_element = type.clone();
    }

    /**
     * Copy and move constructor and operator = with copy-swap approach. Ensuring deep copy.
     * @param source
     */
    CDataTypePtr(const CDataTypePtr & source);
    CDataTypePtr(CDataTypePtr && source) noexcept;
    CDataTypePtr & operator =(CDataTypePtr source);

    /**
     * Comparision operator. Comparing same type, same included types with same order. Names are not relevant. VIRTUAL
     * @param rhs Data type comparing with object type.
     * @return True if same. False if not.
     */
    bool operator ==(const CDataType & rhs) const override;

    /**
     * Comparision operator. Comparing same type, same included types with same order. Names are not relevant. VIRTUAL
     * @param rhs Data type comparing with object type.
     * @return True if different. True if same.
     */
    bool operator !=(const CDataType & rhs) const override;

    /**
     * Method returning proper formatted output of this type. VIRTUAL
     * @param offset Number of spaces from line start. For this type defined in parent printing.
     * @return String of printed output.
     */
    [[nodiscard]] string printBody(int offset, string text) const override;

    /**
     * Method cloning type. VIRTUAL
     * @return Pointer to new copy.
     */
    [[nodiscard]] shared_ptr<CDataType> clone() const override;

    /**
     * Method returning referenced element type. VIRTUAL
     * @return const reference to underlying element.
     */
    [[nodiscard]] const CDataType & element() const override;

};

CDataTypePtr::CDataTypePtr(const CDataTypePtr & source) : CDataType(source){
    m_type = source.m_type;
    m_size = source.m_size;
    m_element = {source.m_element->clone()};
}

CDataTypePtr::CDataTypePtr(CDataTypePtr && source) noexcept{
    m_type = source.m_type;
    m_size = source.m_size;
    swap(m_element, source.m_element);
}

CDataTypePtr & CDataTypePtr::operator =(CDataTypePtr source){
    m_type = source.m_type;
    m_size = source.m_size;
    swap(m_element, source.m_element);
    return *this;
}

bool CDataTypePtr::operator ==(const CDataType & rhs) const{
    if (this->m_type != rhs.getType())
        return false;

    return m_element->getType() == rhs.element().getType();
}

bool CDataTypePtr::operator !=(const CDataType & rhs) const{
    return !(*this == rhs);
}

string CDataTypePtr::printBody(int offset, string text) const{
    string printText;
    if (element().getType() == CDataTypeValue::ARRAY){
        printText.append("(*").append(text).append(")");
    } else{
        printText.append("*").append(text);
    }
    printText = element().printBody(offset, printText);
    return printText;
}

shared_ptr<CDataType> CDataTypePtr::clone() const{
    shared_ptr<CDataTypePtr> clonedType(new CDataTypePtr(*(m_element)));
    return clonedType;
}

const CDataType & CDataTypePtr::element() const{
    return *(m_element);
}
