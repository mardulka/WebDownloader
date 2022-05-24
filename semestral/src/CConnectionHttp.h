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

/**
 * @class CConnectionHttp
 * @extends CConnection
 * @brief Class providing network connection through http protocol only.
 */
class CConnectionHttp : public CConnection{

    /**
     * @brief File-descriptor for connection endpoint.
     */
    int m_socket;

    /**
     * @brief Port number - predefined for http.
     */
    int m_port = 80;

    /**
     * @brief Buffer size for communication - predefined.
     */
    const int m_bufferSize = 1024;

    /**
     * @brief Size of sockaddr_in struct
     */
    socklen_t m_sockAddrSize;

    /**
     * @brief Socket address struct for server address.
     */
    struct sockaddr_in m_serverAddress;

    /**
     * @brief Host pointer for connection
     */
    struct hostent * m_host_ptr;

public:

    /**
     * @brief Nonparametric constructor. Initializes general class attributes.
     */
    explicit CConnectionHttp();

    /**
     * @brief Destructor. Implemented to close connection.
     */
    virtual ~CConnectionHttp();

    /**
     * @brief Returns file from web connection. Implemented virtual method - main interface.
     * @param url URL of the file
     * @return optional shared pointer of the new file.
     */
    std::optional<std::shared_ptr<CFile>> getFile(const CUrl & url) override;

private:

    /**
     * @brief Creates connection with defined URL.
     * @throws logic_error exception if connection cannot be established.
     * @throws invalid_argument exception if hostname is not valid.
     */
    void connect(const std::string & hostName);

    /**
     * @brief Closes connection with remote server
     */
    void closeConnection() const;

    /**
     * @brief Sends requests to server.
     * @param content text of request
     */
    void sendGetRequest(const std::string & content);

    /**
     * @brief Reads response from server.
     */
    [[nodiscard]] std::optional<CHttpResponse> getServerResponse() const;

};


#endif //SEMESTRAL_CCONNECTIONHTTP_H
