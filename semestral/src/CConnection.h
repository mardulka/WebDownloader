#ifndef SEMESTRAL_CCONNECTION_H
#define SEMESTRAL_CCONNECTION_H

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

    /**
     * Destructor. Implemented to free all raw pointers which are necessary to handle INET communication.
     */
    virtual ~CConnection();

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
    std::string getServerResponse();

};


#endif //SEMESTRAL_CCONNECTION_H
