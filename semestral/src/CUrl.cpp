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

        //Check scheme validity
        if (m_scheme != "http" && m_scheme != "https"){
            throw invalid_argument(
                    "Given URL scheme is not valid. Supported URL schemes are http and https only, apparently could be omitted.");
        }
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
        try{
            m_port = stoi(url.substr(position + 1));
        } catch (const invalid_argument & e){
            throw invalid_argument("Given URL has wrong port number!");
        } catch (const out_of_range & e2){
            throw invalid_argument("Given URL has wrong port number!");
        }
        url = url.substr(0, position);

        //check zero and negative value
        if (m_port <= 0 || m_port > 65535){
            throw invalid_argument("Given URL has wrong port number!");
        }
    }

    //READ host - rest
    if (url.empty())
        throw invalid_argument("URL has no host!");
    m_host = url;

    //check content for host and path
    for (auto character: m_host){
        if (isalpha(character) || character == '_' || character == '-' || character == '~' || character == '.')
            continue;
        throw invalid_argument("Given URL contains characters there are not valid!");
    }

    for (auto character: m_path){
        if (isalpha(character) || character == '_' || character == '-' || character == '~' || character == '/' || character == '.')
            continue;
        throw invalid_argument("Given URL contains characters there are not valid!");
    }


}

string CUrl::getScheme() const{
    return m_scheme;
}

string CUrl::getHost() const{
    return m_host;
}

unsigned int CUrl::getPort() const{
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

bool CUrl::empty(){
    return m_host.empty();
}

bool CUrl::operator ==(const CUrl & rhs) const{
    return m_scheme == rhs.m_scheme &&
           m_host == rhs.m_host &&
           m_port == rhs.m_port &&
           m_path == rhs.m_path &&
           m_query == rhs.m_query;
}

bool CUrl::operator !=(const CUrl & rhs) const{
    return !(rhs == *this);
}
