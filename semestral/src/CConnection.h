#ifndef SEMESTRAL_CCONNECTION_H
#define SEMESTRAL_CCONNECTION_H

#include <exception>
#include <string>
#include <iostream>
#include <iomanip>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>
#include <netdb.h>
#include <cstring>
#include <sstream>
#include <optional>
#include <memory>

#include "CFile.h"
#include "CFileHtml.h"
#include "CFileCss.h"
#include "CFilePicture.h"
#include "CUrl.h"

class CConnection{

    /**
     * File-descriptor for connection endpoint.
     */
    int m_socket;

    /**
     * Port number - predefined for http.
     */
    int m_port = 80;

    /**
     * Buffer size for communication - predefined.
     */
    int m_bufferSize = 1024;

    /**
     * Size of sockaddr_in struct
     */
    socklen_t m_sockAddrSize;

    /**
     * Socket address struct for server address.
     */
    struct sockaddr_in m_serverAddress;

    /**
     *
     */
    struct hostent * m_host_ptr;

public:
    /**
     * Nonparametric constructor. Initializes general class attributes.
     * Throws "logic error" exception if socket cannot be created.
     */
    explicit CConnection();

    /**
     * Destructor. Implemented to free all raw pointers which are necessary to handle INET communication.
     */
    virtual ~CConnection();

    /**
     * Method returning file from web connection.
     * @param url URL of the file
     * @return OPTIONAL SHARED PTR of the new file.
     */
    std::optional<std::shared_ptr<CFile>> getFile(const CUrl & url);

private:
    /**
     * Create connection with defined URL.
     * Throws "logic error" exception if connection cannot be established.
     */
    void connect(const std::string & hostName);


    /**
     * Method for sending requests to server.
     * @param content text of request
     */
    void sendGetRequest(const std::string & content);

    /**
     * Method for reading response from server.
     */
    [[nodiscard]] std::string getServerResponse() const;

};


#endif //SEMESTRAL_CCONNECTION_H
