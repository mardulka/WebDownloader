#ifndef SEMESTRAL_CURL_H
#define SEMESTRAL_CURL_H

#include <string>
#include <iostream>
#include <iomanip>
#include <exception>
#include <stdexcept>

/**
 * Immutable class for wrapping http and https URL without fragments.
 * Provides parsing and validation logic and offers some methods for direct access to URL parts.
 *
 * <scheme>://<host>:<port>/<path>?<query>
 *
 * Constructor throws INVALID_ARGUMENT exception if syntax error in URL is occurred while is parsed.
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
     * Port number, default value is 80
     */
    unsigned int m_port = 80;

    /**
     * Resource path - mustn't start with "/" symbol - it is here only as delimiter between host and path
     */
    std::string m_path;

    /**
     * Query
     */
    std::string m_query;

public:

    /**
     * Basic constructor
     * @param url Url for parsing and storing.
     *
     * Throws INVALID_ARGUMENT exception if syntax error in URL is occurred while is parsed.
     */
    CUrl(std::string url);

    /**
     * Copy and move constructors and operators. Since contents are only strings which has implemented these, defaults are ok.
     */
    CUrl(const CUrl & url) = default;
    CUrl(CUrl && url) = default;
    CUrl & operator =(const CUrl & url) = default;
    CUrl & operator =(CUrl && url) = default;

    /**
     * Getter on scheme
     * @return String of scheme
     */
    [[nodiscard]] std::string getScheme() const;

    /**
     * Getter on host
     * @return String of host
     */
    [[nodiscard]] std::string getHost() const;

    /**
     * Getter on port
     * @return port number
     */
    [[nodiscard]] unsigned int getPort() const;

    /**
     * Getter on path / resource
     * @return String of resource path
     */
    [[nodiscard]] std::string getPath() const;

    /**
     * Getter on query
     * @return String of query
     */
    [[nodiscard]] std::string getQuery() const;

    /**
     * Method returning URL in proper format.
     * @return String of URL.
     */
    [[nodiscard]] std::string getUrl() const;
};


#endif //SEMESTRAL_CURL_H
