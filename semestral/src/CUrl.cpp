#include "CUrl.h"

using namespace std;

CUrl::CUrl(string url){
    if (url.length() == 0)
        throw invalid_argument("URL: Given url is empty.");


    size_t position = 0;


    //READ SCHEME - if "://" is now found
    position = url.find("://");
    if (position != string::npos){
        m_scheme = url.substr(0, position);
        url = url.substr(position + 3);
    }

    //Read Query - if "?" is now found
    position = url.find('?');
    if (position != string::npos){
        m_query = url.substr(position + 1);
        url = url.substr(0, position);
    }

    //READ path - if "/" is now found
    position = url.find('/');
    if (position != string::npos){
        m_path = url.substr(position + 1);
        url = url.substr(0, position);
    }

    //READ PORT - if ":" is now found
    position = url.find(':');
    if (position != string::npos){
        m_port = stoi(url.substr(position + 1));
        url = url.substr(0, position);
    }

    //READ host - rest
    if (url.empty())
        throw invalid_argument("URL has no host!");
    m_host = url;

}

string CUrl::getScheme() const{
    return m_scheme;
}

string CUrl::getHost() const{
    return m_host;
}

unsigned short CUrl::getPort() const{
    return m_port;
}

string CUrl::getPath() const{
    return "/"s + m_path;
}

std::string CUrl::getQuery() const{
    return m_query;
}

std::string CUrl::getUrl() const{
    string url;

    //if is defined scheme, start with it
    if (!m_scheme.empty())
        url.append(m_scheme).append("://");

    //host - MANDATORY
    url.append(m_host);

    //port - if defined
    if (m_port)
        url.append(":").append(to_string(m_port));

    //path - if defined
    if (!m_path.empty())
        url.append("/").append(m_path);

    //query - if defined
    if (!m_query.empty())
        url.append("?").append(m_query);

    return url;
}
