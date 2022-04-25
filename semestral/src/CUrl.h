#ifndef SEMESTRAL_CURL_H
#define SEMESTRAL_CURL_H

#include <string>
#include <exception>
#include <stdexcept>

/**
 * Class for wrapping http and https URL without fragments.
 * Provides parsing and validation logic and offers some methods for direct access to URL parts.
 *
 * <scheme>://<host>:<port>/<path>?<query>
 */
class CUrl{
    /**
     * Scheme (http, https, ftp, smtp,...)
     */
    std::string m_scheme;

    /**
     * Host name (with or without "www.")
     */
    std::string m_host;

    /**
     * Port number
     */
    unsigned short m_port;

    /**
     * Resource path - mustn't start with "/" symbol - it is here only as delimiter between host and path
     */
    std::string m_path;

    /**
     * Query
     */
    std::string m_query;

public:
    CUrl(const std::string & url);

    /**
     * Getter on scheme
     * @return String of scheme
     */
    const std::string & getScheme() const;

    /**
     * Getter on host
     * @return String of host
     */
    const std::string & getHost() const;

    /**
     * Getter on port
     * @return port number
     */
    unsigned short getPort() const;

    /**
     * Getter on path / resource
     * @return String of resource path
     */
    const std::string & getPath() const;

    /**
     * Getter on query
     * @return String of query
     */
    const std::string & getQuery() const;

    /**
     * Method returning URL in proper format.
     * @return String of URL.
     */
    const std::string getUrl() const;
};


#endif //SEMESTRAL_CURL_H
