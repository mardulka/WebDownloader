#include "CHttpResponse.h"

using namespace std;

CHttpResponse::CHttpResponse(const std::string & response){
    istringstream input(response);

    string line;

    //read first header line into class attributes
    readHeadIntro(input);

    //check protocol
    if (m_protocol != "HTTP/1.1")
        throw invalid_argument("Wrong protocol");

    //read head parameters into class attributes
    readHeadParameters(input);

    //rest of the message
    while (getline(input, line))
        m_content.append(line).append(1, '\n');
}

void CHttpResponse::readHeadIntro(istringstream & input){
    string line;

    //read protocol, status and status text
    input >> m_protocol >> m_status >> m_status_text;
    //skip rest of line
    getline(input, line);
}

void CHttpResponse::readHeadParameters(istringstream & input){

    string line;

    //Read head line by line - ends with empty line
    while (getline(input, line)){
        //if win line breaks, delete excesive \r symbol
        if (line.back() == '\r')
            line.pop_back();
        //check empty line indicating header end
        if (line.empty())
            break;

        istringstream line_input(line);
        string attr_name;

        //parse attribute name - other attributes can be added in "else if" statement
        line_input >> attr_name;
        if (attr_name == "Content-Type:"){
            string ctype;
            line_input >> ctype;

            if (ctype.back() == ';')    //if there is charset value, ';' is used as delimiter
                ctype.pop_back();

            //split
            istringstream ctypestream(ctype);
            getline(ctypestream, m_content_type, '/');
            getline(ctypestream, m_content_format);
        }
    }
}

string CHttpResponse::getProtocol() const{
    return m_protocol;
}

unsigned short CHttpResponse::getStatus() const{
    return m_status;
}

string CHttpResponse::getContentType() const{
    return m_content_type;
}

string CHttpResponse::getContentFormat() const{
    return m_content_format;
}

string CHttpResponse::getContent() const{
    return m_content;
}
