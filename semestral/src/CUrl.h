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
     * Scheme (only http, https valid)
     */
    std::string m_scheme;

    /**
     * Host name
     */
    std::string m_host;

    /**
     * Port number
     */
    unsigned int m_port = 80;

    /**
     * Indicates if port is default - default port is not printed into url string
     */
    bool m_default_port = true;


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
     * Default constructor
     */
    CUrl() = default;

    /**
     * Basic constructor
     * @param url Url for parsing and storing.
     *
     * Throws INVALID_ARGUMENT exception if syntax error in URL is occurred while is parsed.
     */
    explicit CUrl(std::string url);

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
     * Getter on path
     * @return String of path
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

    /**
     * Getter on path?resource
     * @return String of resource path
     */
    [[nodiscard]] std::string getResource() const;

    /**
     * Method returning information if url is empty. Empty URL is when HOST is empty
     * @return true if URL is empty, false otherwise
     */
    bool empty();

    /**
     * Equality operator
     * @param rhs compared URL
     * @return true if same, false otherwise
     */
    bool operator ==(const CUrl & rhs) const;

    /**
     * Inequality operator
     * @param rhs compared URL
     * @return false if same, true otherwise
     */
    bool operator !=(const CUrl & rhs) const;
};


#endif //SEMESTRAL_CURL_H
