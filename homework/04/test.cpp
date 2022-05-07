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
    /**
     * Struct holding underlying array.
     */
    struct CVecData;

    CVecData * m_vec_data;

private:
    /**
     * Link given array as underlying array and increase its sharing count.
     * @param data Array which should be linked as underlying array.
     */
    void attach(CVecData * data);

    /**
     * Unlink underlying array and decrease its underlying count.
     * If no count left (this was only link) then destroy whole array.
     */
    void detach();
public:

    /**
     * Explicit constructor creating own underlying array of given size for this object
     * @param size Size of new array.
     */
    explicit CVector(uint32_t size);

    /**
     * Copy constructor linking underlying array from given CVector object.
     * @param vector Given CVector object for copying from.
     */
    CVector(const CVector & vector);

    /**
     * Destructor detach underlying array before destruct this object.
     */
    ~CVector();

    /**
     * Getting size of underlying array.
     * @return Size of array
     */
    [[nodiscard]] uint32_t size() const;

    /**
     * Operator for access to one element of underlying array.
     * When accessing shared array, new copy of underlying is provided to ensure proper modifications behaviour.
     * @param pos position of element
     * @return Reference to requested element.
     */
    uint8_t & operator [](uint32_t pos);

    /**
     * Operator for access to one element of underlying array. Const - modifications unable.
     * @param pos position of element
     * @return Copy of requested element.
     */
    uint8_t operator [](uint32_t pos) const;

    /**
     * Drops own array and link shared array of given vector.
     * @param vector Vector from which underlying array should be linked.
     * @return Reference to itself.
     */
    CVector & operator =(const CVector & vector);

    /**
     * Change size of underlying array by calling its own method.
     * Before that check if array is shared and make new copy of it when is shared.
     * @param capacity New capacity of array.
     */
    void resize(uint32_t capacity);

};

struct CVector::CVecData{
    uint8_t * m_data;
    uint32_t m_size;
    uint32_t m_capacity;
    uint32_t m_count;

    /**
     * Explicit constructor creating array of given size and set default count of sharing to 1.
     * @param size Size of new array.
     */
    explicit CVecData(uint32_t size);

    /**
     * Copy constructor creates own copy of given array.
     * @param data Array which data should be copied.
     */
    explicit CVecData(const CVecData * data);

    /**
     * Destructor deletes array before destructs object.
     */
    ~CVecData();

    /**
     * Resizes array making its new copy.
     * If allocated space is sufficient, only increases size attribute.
     * @param capacity New array capacity.
     * @return true if resize was successful, false otherwise
     */
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
    m_data = new uint8_t[m_capacity];
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
 * Class CHistory storing history in double linked list.
 */
class CHistory{
    /**
     * Element storing one history state and is linked in double linked list.
     */
    struct CElement;

    CElement * head;
    CElement * tail;
    int size;
public:
    /**
     * Constructs empty history ready for storing.
     */
    CHistory();

    /**
     * Copy constructor copying whole history from given CHistory object
     * @param history CHistory object which history should be copied.
     */
    CHistory(const CHistory & history);

    /**
     * Operator = copying whole history from given CHistory object
     * @param history CHistory object which history should be copied.
     * @return Reference to itself.
     */
    CHistory & operator =(const CHistory & history);

    /**
     * Destructor clears whole history before destructs object.
     */
    ~CHistory();

    /**
     * Retracting newest element from history.
     * @param retract Reference to CVector where the history should be copied.
     * @param position Reference to position in CVector where it should be copied version from history.
     * @return True if history was successfully retract into given objects and data, false otherwise.
     */
    bool pop(CVector & retract, uint32_t & position);

    /**
     * Storing current state to history.
     * @param store CVector which should be copied into history.
     * @param pos Position in CVector which should be stored.
     */
    void push(const CVector & store, uint32_t pos);
};

struct CHistory::CElement{
    CVector hcontent;
    uint32_t hposition;
    CElement * next;
    CElement * prev;

    /**
     * Constructor of new history element. Only way of construct it is provide data to storing in history.
     * @param hcontent Content which should be stored in history.
     * @param hposition Position in content.
     * @param next pointer to next History element = older history element
     * @param prev pointer to prev History element = newer history element
     */
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
 * CFile class simulates behaviour of binary file with requested undo and copying functions.
 */
class CFile{
public:
    /**
     * Constructor creates empty CFile
     */
    CFile();

    /**
     * Copy constructor creating copy of given file. All history is copied too.
     * @param file CFile which should be copied.
     */
    CFile(const CFile & file);

    /**
     * Operator creating copy of given file. All history is copied too.
     * @param file CFile which should be copied.
     * @return Reference to itself
     */
    CFile & operator =(const CFile & file);

    /**
     * Default destructor
     */
    ~CFile() = default;

    /**
     * Moves position in file on given offset.
     * @param offset Offset from beginning.
     * @return True if position was set successfully, false if given offset is out of file.
     */
    bool seek(uint32_t offset);

    /**
     * Reads given number of bytes from current position in file and store it in given array.
     * If file ends before requested number of bytes was read, ends here and return this read number.
     * @param dst Array where the read bytes should be stored.
     * @param bytes Number of bytes to read.
     * @return Actual number of bytes read.
     */
    uint32_t read(uint8_t * dst, uint32_t bytes);

    /**
     * Writes given number of bytes from given array and store it in file from current position.
     * If file is smaller then needed, is enlarged to ensure all bytes could be written.
     * @param src Array where the bytes for writing are stored.
     * @param bytes Number of bytes to write.
     * @return Actual number of bytes written.
     */
    uint32_t write(const uint8_t * src, uint32_t bytes);

    /**
     * Cuts file from current position ahead.
     */
    void truncate();

    /**
     * Checks file size.
     * @return File size.
     */
    uint32_t fileSize() const;

    /**
     * Stores current state of file into file history.
     */
    void addVersion();

    /**
     * Retract latest state from history and overwrites current state by it.
     * @return
     */
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
    if (content.size() <= (position + bytes))
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


