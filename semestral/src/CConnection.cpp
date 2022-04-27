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
    //Get address, check if any address has been returned.
    m_host_ptr = gethostbyname(hostName.c_str());
    if (m_host_ptr == nullptr) throw invalid_argument("Url is not valid.");

    //Copy obtained address to server address struct.
    memcpy(&m_serverAddress.sin_addr, m_host_ptr->h_addr, m_host_ptr->h_length);

    //Try to connect to server with prepared address struct.
    if (::connect(m_socket, (struct sockaddr *) &m_serverAddress, m_sockAddrSize) < 0){
        close(m_socket);
        throw logic_error("Communication with server cannot be established!");
    }
}

CConnection::~CConnection(){
    close(m_socket);
}

void CConnection::sendGetRequest(const string & resource){
    string request;
    request.append("GET ").append(resource).append(" HTTP/1.1").append("\r\n");
    request.append("Host: ").append(m_host_ptr->h_name).append("\r\n");
    request.append("Connection: ").append("close").append("\r\n");
    request.append("Accept: */*").append("\r\n").append("\r\n");
    send(m_socket, request.c_str(), request.length(), MSG_NOSIGNAL);
}

optional<CHttpResponse> CConnection::getServerResponse() const{
    string output;
    //prepared buffer;
    char * buffer = new char[m_bufferSize];
    memset(buffer, 0, m_bufferSize);

    //read
    while (read(m_socket, buffer, m_bufferSize) > 0){
        output.append(buffer);
        memset(buffer, 0, m_bufferSize);
    }

    //delete buffer
    delete[] buffer;

    //Try create message and return optional
    try{
        CHttpResponse response(output);
        if (response.getStatus() != 200){
            return nullopt;
        }
        return {output};
    } catch (const invalid_argument & e){
        return nullopt;
    }
}

std::optional<shared_ptr<CFile>> CConnection::getFile(const CUrl & url){
    connect(url.getHost());
    sendGetRequest(url.getPath());

    auto response = getServerResponse();

    //no response - no file
    if (!response.has_value())
        return nullopt;

    if (response.value().getContentType() == "text"){
        if(response.value().getContentFormat() == "html"){
            return {make_shared<CFileHtml>("filename"s)};
        } else if (response.value().getContentFormat() == "css") {
            return {make_shared<CFileCss>("filename"s)};
        }
    } else if (response.value().getContentType() == "image"){
        return {make_shared<CFilePicture>("filename"s, response.value().getContentFormat())};
    }

    return nullopt;
}
