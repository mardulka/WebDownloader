#ifndef SEMESTRAL_CCONNECTIONHTTP_H
#define SEMESTRAL_CCONNECTIONHTTP_H

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
#include "CFileScript.h"
#include "CUrl.h"
#include "CHttpResponse.h"
#include "CConnection.h"

class CConnectionHttp : public CConnection{

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
    const int m_bufferSize = 1024;

    /**
     * Size of sockaddr_in struct
     */
    socklen_t m_sockAddrSize;

    /**
     * Socket address struct for server address.
     */
    struct sockaddr_in m_serverAddress;

    /**
     * Host pointer for connection
     */
    struct hostent * m_host_ptr;

public:
    /**
     * Nonparametric constructor. Initializes general class attributes.
     * Throws "logic error" exception if socket cannot be created.
     */
    explicit CConnectionHttp();

    /**
     * Destructor. Implemented to close connection.
     */
    virtual ~CConnectionHttp();

    /**
     * Method returning file from web connection. Overrode from abstract parent class.
     * @param url URL of the file
     * @return OPTIONAL SHARED PTR of the new file.
     */
    std::optional<std::shared_ptr<CFile>> getFile(const CUrl & url) override;

private:
    /**
     * Create connection with defined URL.
     * Throws "logic error" exception if connection cannot be established.
     */
    void connect(const std::string & hostName);

    /**
     * Closing connection with remote server
     */
    void closeConnection() const;

    /**
     * Method for sending requests to server.
     * @param content text of request
     */
    void sendGetRequest(const std::string & content);

    /**
     * Method for reading response from server.
     */
    [[nodiscard]] std::optional<CHttpResponse> getServerResponse() const;

};


#endif //SEMESTRAL_CCONNECTIONHTTP_H
