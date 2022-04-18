#include "CDownloader.h"

using namespace std;

int main(int argc, char ** argv){
    //Create struct holding settings together
    auto settings = make_shared<CSettings>();

    //Read CLI information for application RUN into prepared settings struct
    CCli Cli(settings);
    try{
        Cli.readSettings(argc, argv);
    } catch (const invalid_argument & e){
        string message = e.what();
        Cli.write(message);
        return 1;
    }

    /*Check // TODO delete
    Cli.printSettings();
    */

    //Creation of CConnection class with automatic try of creation connection
    CConnection connection;
    try{
        connection.connect(settings->url);
    } catch (const invalid_argument & e){
        string message = e.what();
        return 3;
    } catch (const logic_error & e){
        string message = e.what();
        return 3;
    }


    //TODO Give control to download
    cout << "Stahujeme." << endl;

    //TODO Write result

}