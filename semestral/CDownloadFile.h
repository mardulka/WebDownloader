#ifndef PA2_DOWNLOADFILE_H
#define PA2_DOWNLOADFILE_H

#include <sys/socket.h>
#include <netinet/in.h>

class DownloadFile{
    url m_url;

    virtual bool download() = 0;
};

#endif //PA2_DOWNLOADFILE_H
