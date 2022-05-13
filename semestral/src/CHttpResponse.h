#ifndef SEMESTRAL_CHTTPRESPONSE_H
#define SEMESTRAL_CHTTPRESPONSE_H

#include <string>
#include <iostream>
#include <sstream>
#include <exception>

/**
 * @class CHttpReponse
 * @brief Class representing HTTP response obtained from network. It can parse obtained response and provide asses to data.
 */
class CHttpResponse{

    /**
     * @brief Protocol
     * @example HTTP/1.1
     */
    std::string m_protocol;

    /**
     * @brief Response status
     * @example 200
     */
    unsigned short m_status{};

    /**
     * @brief Response status text
     * @example OK
     */
    std::string m_status_text;

    /**
     * @brief Reponse content type
     * @example text
     */
    std::string m_content_type;

    /**
     * @brief Reponse content type
     * @example html
     */
    std::string m_content_format;

    /**
     * @brief Response content itself
     * @example html formatted text, css content, script content, or image binary
     */
    std::string m_content;

public:

    /**
     * @brief Default constructor
     */
    CHttpResponse() = default;

    CHttpResponse(const CHttpResponse & rhs) = default;
    CHttpResponse & operator =(const CHttpResponse & rhs) = default;
    CHttpResponse(CHttpResponse && rhs) = default;
    CHttpResponse & operator = (CHttpResponse && rhs) = default;


    /**
     * @brief Constructor with whole response string as parameter
     * @throws invalid_argument if protocol of response is not HTTP/1.1
     * @param response String of response obtained from network
     */
    explicit CHttpResponse(const std::string & response);


    /**
     * @brief Getter on content
     * @return String of content
     */
    [[nodiscard]] std::string getProtocol() const;

    /**
     * @brief Getter on response status
     * @return String of status code
     */
    [[nodiscard]] unsigned short getStatus() const;

    /**
     * @brief Getter on content type
     * @return String of status code
     */
    [[nodiscard]] std::string getContentType() const;

    /**
     * @brief Getter on content format
     * @return String of status code
     */
    [[nodiscard]] std::string getContentFormat() const;


    /**
     * @brief Getter on content
     * @return String of content
     */
    [[nodiscard]] std::string getContent() const;

private:

    /**
     * @brief Reads first header line into class attributes
     * @param input stream to parsed response string
     */
    void readHeadIntro(std::istringstream & input);

    /**
     * @brief Reads defined head parameters into class attributes
     * @param input stream to parsed response string
     */
    void readHeadParameters(std::istringstream & input);
};


#endif //SEMESTRAL_CHTTPRESPONSE_H
