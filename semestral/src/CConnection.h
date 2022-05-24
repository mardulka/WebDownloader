#ifndef SEMESTRAL_CCONNECTION_H
#define SEMESTRAL_CCONNECTION_H


/**
 * @class CConnection
 * @brief Virtual class as interface for all classes providing network communication.
 */
class CConnection{

public:

    /**
     * @brief Try to download file represented by URL. If is downloaded OK, return instance of corresponding file class.
     * @param url Url of given file
     * @return Optional shared pointer to downloaded file instance.
     */
    virtual std::optional<std::shared_ptr<CFile>> getFile(const CUrl & url) = 0;

};


#endif //SEMESTRAL_CCONNECTION_H
