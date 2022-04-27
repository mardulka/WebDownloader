#ifndef SEMESTRAL_CHTTPRESPONSE_H
#define SEMESTRAL_CHTTPRESPONSE_H


#include <string>
#include <sstream>
#include <exception>

class CHttpResponse{

    /**
     * Protocol (HTTP/1.1)
     */
    std::string m_protocol;


    /**
     * Response status (200)
     */
    unsigned short m_status;

    /**
     * Response status text (OK)
     */
    std::string m_status_text;

    /**
     * Reponse content type (text)
     */
    std::string m_content_type;

    /**
     * Reponse content type (html)
     */
    std::string m_content_format;

    /**
     * Response content itself - html formatted text, css content, script content, or image binary
     */
    std::string m_content;

public:

    /**
     * Default constructor
     */
    CHttpResponse() = default;

    /**
     * Constructor with whole response string as parameter
     * Throws INVALID_ARGUMENT on parsing error.
     * @param response
     */
    CHttpResponse(const std::string & response);


    /**
     * Getter on content
     * @return String of content
     */
    std::string getProtocol() const;

    /**
     * Getter on response status
     * @return String of status code
     */
    unsigned short getStatus() const;

    /**
     * Getter on content type
     * @return String of status code
     */
    std::string getContentType() const;

    /**
     * Getter on content format
     * @return String of status code
     */
    std::string getContentFormat() const;


    /**
     * Getter on content
     * @return String of content
     */
    std::string getContent() const;

};


#endif //SEMESTRAL_CHTTPRESPONSE_H
