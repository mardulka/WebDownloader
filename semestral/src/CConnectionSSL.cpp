#include "CConnectionSSL.h"

using namespace std

CConnectionSSL::CConnectionSSL(){
    //Socket creation
    m_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (m_socket < 0)
        throw logic_error("Communication socket cannot be created.");

    //Fill socklen_t
    m_sockAddrSize = sizeof(struct sockaddr_in);

    //Socket address setup
    bzero(&m_serverAddress, sizeof m_serverAddress);
    m_serverAddress.sin_family = AF_INET;
    m_serverAddress.sin_port = htons(m_port);
}


//replace

//connect()
//read()
//write()

//with

//ssl_connect()
//ssl_read()
//sst_write()