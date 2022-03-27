#ifndef __PROGTEST__

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <iostream>

using namespace std;
#endif /* __PROGTEST__ */


/**
 * Vector class
 */
class CVector{
    struct CVecData;
    CVecData * m_vec_data;
    void attach(CVecData * data);
    void detach();
public:
    explicit CVector(uint32_t size);
    CVector(const CVector & vector);
    ~CVector();

    [[nodiscard]] uint32_t size() const;
    uint8_t & operator [](uint32_t pos);
    uint8_t operator [](uint32_t pos) const;
    CVector & operator =(const CVector & vector);
    void resize(uint32_t capacity);

};

struct CVector::CVecData{
    uint8_t * m_data;
    uint32_t m_size;
    uint32_t m_capacity;
    uint32_t m_count;

    explicit CVecData(uint32_t size);
    explicit CVecData(const CVecData * data);
    ~CVecData();
    bool resize(uint32_t capacity);

};

// CVector methods -----------------------------------------------------------------------------------------------------

CVector::CVector(uint32_t size){
    m_vec_data = new CVecData(size);
}

CVector::CVector(const CVector & vector){
    //m_vec_data filled through attach method
    m_vec_data = nullptr;
    attach(vector.m_vec_data);
}

CVector::~CVector(){
    detach();
}

uint32_t CVector::size() const{return m_vec_data->m_size;}

uint8_t & CVector::operator [](uint32_t pos){
    if (pos >= m_vec_data->m_size)
        throw out_of_range("Attempt to read outside file.");
    if (m_vec_data->m_count > 1){
        m_vec_data->m_count--;
        m_vec_data = new CVecData(m_vec_data);
    }

    return m_vec_data->m_data[pos];
}

uint8_t CVector::operator [](uint32_t pos) const{
    if (pos >= m_vec_data->m_size)
        throw out_of_range("Attempt to read outside file.");
    return m_vec_data->m_data[pos];
}

CVector & CVector::operator =(const CVector & vector){
    if (this == &vector) return *this;
    detach();
    attach(vector.m_vec_data);
    return *this;
}

void CVector::attach(CVector::CVecData * data){
    m_vec_data = data;
    m_vec_data->m_count++;
}

void CVector::detach(){
    m_vec_data->m_count--;
    if (m_vec_data->m_count == 0)
        delete m_vec_data;
}

void CVector::resize(uint32_t capacity){
    if (m_vec_data->m_count > 1){
        m_vec_data->m_count--;
        m_vec_data = new CVecData(m_vec_data);
    }
    m_vec_data->resize(capacity);
}


// CVector::CVecData methods -------------------------------------------------------------------------------------------

CVector::CVecData::CVecData(uint32_t size) : m_size{0}, m_capacity{size}{
    m_data = new uint8_t[m_size];
    m_count = 1;
}

CVector::CVecData::CVecData(const CVector::CVecData * data) : m_size{data->m_size}, m_capacity{data->m_size}{
    m_count = 1;
    m_data = new uint8_t[m_capacity];
    for (uint32_t i = 0 ; i < m_size ; ++i){
        m_data[i] = data->m_data[i];
    }
}

CVector::CVecData::~CVecData(){
    delete[] m_data;
}

bool CVector::CVecData::resize(uint32_t capacity){
    if (capacity <= m_capacity){
        m_size = capacity;
        return true;
    }
    int multiplication = 2;

    auto * m_data_new = new uint8_t[multiplication * capacity];
    for (uint32_t i = 0 ; i < m_capacity ; ++i){
        m_data_new[i] = m_data[i];
    }
    delete[]m_data;
    m_data = m_data_new;
    m_capacity = multiplication * capacity;
    m_size = capacity;

    return true;
}

// ---------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

/**
 * Class CHistory
 */
class CHistory{
    struct CElement;
    CElement * head;
    CElement * tail;
    int size;
public:
    CHistory();
    CHistory(const CHistory & history);
    CHistory & operator =(const CHistory & history);
    ~CHistory();
    bool pop(CVector & retract, uint32_t & position);
    void push(const CVector & store, uint32_t pos);
};

struct CHistory::CElement{
    CVector hcontent;
    uint32_t hposition;
    CElement * next;
    CElement * prev;

    explicit CElement(const CVector & hcontent, uint32_t hposition, CElement * next = nullptr, CElement * prev = nullptr)
    : hcontent{hcontent}, hposition{hposition}, next{next}, prev{prev}{}
};

CHistory::CHistory(){
    size = 0;
    tail = head = nullptr;

}

CHistory::CHistory(const CHistory & history){
    head = tail = nullptr;
    size = history.size;
    auto elem = history.tail;
    while (elem){
        push(elem->hcontent, elem->hposition);
        ++size;
        elem = elem->prev;
    }

}

CHistory & CHistory::operator =(const CHistory & history){
    if (this == &history) return *this;

    auto elem = history.tail;
    while (elem){
        push(elem->hcontent, elem->hposition);
        ++size;
        elem = elem->prev;
    }
    return *this;

}

CHistory::~CHistory(){
    while (head){
        auto tmp = head->next;
        delete head;
        head = tmp;
    }
}

bool CHistory::pop(CVector & retract, uint32_t & position){
    if (!head) return false;
    retract = head->hcontent;
    position = head->hposition;
    auto temp = head;
    head = head->next;
    temp->next = nullptr;
    if (head) head->prev = nullptr;
    delete temp;
    if (!head) tail = nullptr;

    --size;
    return true;
}

void CHistory::push(const CVector & store, uint32_t pos){
    auto element = new CElement(store, pos, head);
    if (head) head->prev = element;
    head = element;
    if (!tail) tail = element;
    ++size;
}

/**
 * CFile class
 */
class CFile{
public:
    CFile();
    CFile(const CFile & file);
    CFile & operator =(const CFile & file);
    ~CFile() = default;

    bool seek(uint32_t offset);
    uint32_t read(uint8_t * dst, uint32_t bytes);
    uint32_t write(const uint8_t * src, uint32_t bytes);
    void truncate();
    uint32_t fileSize() const;
    void addVersion();
    bool undoVersion();
private:
    mutable uint32_t position;
    CVector content;
    CHistory history;

};

CFile::CFile() : content{10}{
    position = 0;
}

CFile::CFile(const CFile & file) : position{file.position}, content{file.content}{
    history = file.history;

}

CFile & CFile::operator =(const CFile & file){
    if (this == &file) return *this;
    content = file.content;
    history = file.history;
    return *this;
}

bool CFile::seek(uint32_t offset){
    if (offset > content.size())
        return false;
    position = offset;
    return true;
}

uint32_t CFile::fileSize() const{
    return content.size();
}

void CFile::truncate(){
    content.resize(position);
}

uint32_t CFile::read(uint8_t * dst, uint32_t bytes){
    uint32_t i = 0;
    for (; i < bytes && position < content.size() ; ++i, ++position){
        dst[i] = content[position];
    }
    return i;
}

uint32_t CFile::write(const uint8_t * src, uint32_t bytes){
    uint32_t i = 0;
    if (content.size() <= position + bytes)
        content.resize(position + bytes);
    for (; i < bytes ; ++i, ++position){
        content[position] = src[i];
    }

    return i;
}

void CFile::addVersion(){
    history.push(content, position);
}

bool CFile::undoVersion(){
    if (!history.pop(content, position)) return false;
    return true;

}


