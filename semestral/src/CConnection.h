#ifndef SEMESTRAL_CCONNECTION_H
#define SEMESTRAL_CCONNECTION_H


/**
 * Virtual class as interface for
 */
class CConnection{

public:

    /**
     * Virtual method for overriding
     * @param url Url of given file
     * @return Optional pointer to downloaded file.
     */
    virtual std::optional<std::shared_ptr<CFile>> getFile(const CUrl & url) = 0;

};


#endif //SEMESTRAL_CCONNECTION_H
