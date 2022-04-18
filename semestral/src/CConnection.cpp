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
    //Get address, check if any address has been returned, copy obtained address to server address struct.
    m_host_ptr = gethostbyname(hostName.c_str());
    if (m_host_ptr == nullptr) throw invalid_argument("Url is not valid.");
    memcpy(&m_serverAddress.sin_addr, m_host_ptr->h_addr, m_host_ptr->h_length);

    //Try to connect to server.
    if (::connect(m_socket, (struct sockaddr *) &m_serverAddress, m_sockAddrSize) < 0){
        close(m_socket);
        throw logic_error("Communication with server cannot be established!");
    }

    cout << "Connection established." << endl;
}

CConnection::~CConnection(){
    close(m_socket);
}

void CConnection::sendGetRequest(const string & url){
    string request;
    request.append("GET ").append(url).append(R"( HTTP/1.1\r\n)");
    request.append("Host: ").append(m_host_ptr->h_name).append(R"(\r\n)");
    request.append("Connection: keep-alive").append(R"(\r\n\r\n)");
    send(m_socket, request.c_str(), request.length(), 0);
    cout << "Sent request: " << endl << request << endl;
}

string CConnection::getServerResponse(){
    string output;
    char * buffer = new char[m_bufferSize];
    cout << "Waiting for response....." << endl;
    while (read(m_socket, buffer, m_bufferSize - 1) > 0)
        output.append(buffer);
    delete[] buffer;
    return output;
}
