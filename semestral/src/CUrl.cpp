//
// Created by marek on 25.04.2022.
//

#include "CUrl.h"

using namespace std;

CUrl::CUrl(const string & url){
    if (url.length() == 0)
        throw invalid_argument("URL: Given url is empty.");

    //TODO read scheme

    //TODO read host

    //TODO read port

    //todo read path


}

const string & CUrl::getScheme() const{
    return m_scheme;
}

const string & CUrl::getHost() const{
    return m_host;
}

unsigned short CUrl::getPort() const{
    return m_port;
}

const string & CUrl::getPath() const{
    return m_path;
}

const std::string & CUrl::getQuery() const{
    return m_query;
}

const std::string CUrl::getUrl() const{
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
