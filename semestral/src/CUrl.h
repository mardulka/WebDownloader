#ifndef SEMESTRAL_CURL_H
#define SEMESTRAL_CURL_H

#include <string>
#include <iostream>
#include <iomanip>
#include <exception>
#include <stdexcept>
#include <optional>

/**
 * @class CUrl
 * @brief Immutable class for wrapping http and https URL without fragments.
 *
 * Provides parsing and validation logic and offers some methods for direct access to URL parts.
 *
 * @note <scheme>://<host>:<port>/<path>?<query>
 */
class CUrl{

    /**
     * @brief Scheme
     * @note only http and https is valid
     */
    std::string m_scheme;

    /**
     * @brief Host name
     */
    std::string m_host;

    /**
     *@brief  Port number
     */
    unsigned int m_port = 80;

    /**
     * @brief Indicates if port is default - default port is not printed into url string
     */
    bool m_default_port = true;


    /**
     * @brief Resource path
     * @note mustn't start with "/" symbol - it is here only as delimiter between host and path
     */
    std::string m_path;

    /**
     * @brief Query
     */
    std::string m_query;

public:


    /**
     * @brief Default constructor
     */
    CUrl() = default;

    /**
     * @brief Basic constructor
     * @param url Url for parsing and storing.
     * @throws invalid_argument exception if syntax error in URL is occurred while is parsed.
     */
    explicit CUrl(std::string url);


    CUrl(const CUrl & url) = default;
    CUrl(CUrl && url) = default;
    CUrl & operator =(const CUrl & url) = default;
    CUrl & operator =(CUrl && url) = default;

    /**
     * @brief Getter on scheme
     * @return String of scheme
     */
    [[nodiscard]] std::string getScheme() const;

    /**
     * @brief Getter on host
     * @return String of host
     */
    [[nodiscard]] std::string getHost() const;

    /**
     * @brief Getter on port
     * @return port number
     */
    [[nodiscard]] unsigned int getPort() const;

    /**
     * @brief Getter on path
     * @return String of path
     */
    [[nodiscard]] std::string getPath() const;

    /**
     * @brief Getter on query
     * @return String of query
     */
    [[nodiscard]] std::string getQuery() const;

    /**
     * @brief Returns URL in proper format.
     * @return String of URL.
     */
    [[nodiscard]] std::string getUrl() const;

    /**
     * @brief Getter on path?resource
     * @return String of resource path
     */
    [[nodiscard]] std::string getResource() const;

    /**
     * @brief Returns information if url is empty.
     * @note Empty URL is when HOST is empty
     * @return true if URL is empty, false otherwise
     */
    bool empty();

    /**
     * @brief Equality operator
     * @param rhs compared URL
     * @return true if same, false otherwise
     */
    bool operator ==(const CUrl & rhs) const;

    /**
     * @brief Inequality operator
     * @param rhs compared URL
     * @return false if same, true otherwise
     */
    bool operator !=(const CUrl & rhs) const;


    /**
     * @brief Method for complete link to absolute based on the URL
     * @param link link to be made absolute
     * @return Link if is absolute or was converted, nullopt for another link types
     */
    [[nodiscard]] std::optional<std::string> makeLinkAbsolute(const std::string & link) const;
};


#endif //SEMESTRAL_CURL_H
