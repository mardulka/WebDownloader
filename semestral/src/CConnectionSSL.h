#ifndef SEMESTRAL_CCONNECTIONSSL_H
#define SEMESTRAL_CCONNECTIONSSL_H

#include <exception>
#include <string>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <strings.h>
#include <netdb.h>
#include <cstring>
#include <sstream>
#include <openssl/ssl.h>
#include <openssl/err.h>

class CConnectionSSL{

    /**
     * SSL pointer
     */
    shared_ptr<SSL> m_ssl;

    /**
     * File-descriptor for connection endpoint.
     */
    int m_socket;

    /**
     * Port number - predefined for http.
     */
    int m_port = 443;

    /**
     * Buffer size for communication - predefined.
     */
    int m_bufferSize = 10240;

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

};


#endif //SEMESTRAL_CCONNECTIONSSL_H
