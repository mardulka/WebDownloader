#include "CDownloader.h"

using namespace std;

int main(int argc, char ** argv){

    //Read CLI information for application RUN into prepared settings struct
    try{
        if(!CCli::readSettings(argc, argv))
            return 0;
    } catch (const exception & e){
        CCli::logError(e.what());
        return 1;
    }

    //Settings output
    CCli::printSettings();


    //Give control to download engine and start downloading.
    try{
        CDownEngine engine;
        engine.start();
    } catch (const invalid_argument & e){
        CCli::logError(e.what());
        return 2;
    } catch (const filesystem::filesystem_error & fe){
        CCli::logError(fe.what());
        return 5;
    } catch (...){
        CCli::logError("Unknown ERROR occurred!");
    }

    //Print stats at program end
    CCli::printStatistics();

    //Thank
    CCli::write("Thank you for using our program!");

    return 0;
}