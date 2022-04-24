#ifndef SEMESTRAL_CFILE_H
#define SEMESTRAL_CFILE_H

#include <string>

class CFile{
    std::string m_url;
    std::string m_content;

public:
    /**
     * Constructor
     * @param url Url of
     */
    CFile(const std::string & url) : m_url(url){}

    /**
     * Save content.
     * @return
     */
    virtual bool save() = 0;
};


#endif //SEMESTRAL_CFILE_H
