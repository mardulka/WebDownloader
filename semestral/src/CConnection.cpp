#include <cstring>
#include "CConnection.h"

using namespace std;

CConnection::CConnection(){
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

void CConnection::connect(const string & hostName){
    //Get address.
    m_host_ptr = gethostbyname(hostName.c_str());
    if (!m_host_ptr) throw invalid_argument("Url is not valid.");
    memcpy(&m_serverAddress.sin_addr, m_host_ptr->h_addr, m_host_ptr->h_length);

    //Try to connect
    if (::connect(m_socket, (struct sockaddr *) &m_serverAddress, m_sockAddrSize) < 0){
        close(m_socket);
        throw logic_error("Communication with server cannot be established!");
    }

    cout << "Connection established." << endl;
}

CConnection::~CConnection(){
    close(m_socket);
}
