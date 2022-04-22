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
    request.append("GET ").append(url).append(" HTTP/1.1").append("\r\n");
    request.append("Host: ").append(m_host_ptr->h_name).append("\r\n");
    request.append("Connection: ").append("close").append("\r\n");
    request.append("Accept: */*").append("\r\n").append("\r\n");
    send(m_socket, request.c_str(), request.length(), MSG_NOSIGNAL);
    cout << "Sent request: " << endl << request << endl;
}

string CConnection::getServerResponse(){
    string output;
    char * buffer = new char[m_bufferSize];
    memset(buffer, 0, m_bufferSize);
    cout << "Waiting for response....." << endl;
    int a = 0;
    while ((a = read(m_socket, buffer, m_bufferSize)) > 0){
        cout << setfill('-') << setw(10) << right << "->" << a << endl;
        output.append(buffer);
        memset(buffer, 0, m_bufferSize);
    }
    delete[] buffer;
    return output;
}
