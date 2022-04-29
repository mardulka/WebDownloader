#include "CDownloader.h"

using namespace std;

int main(int argc, char ** argv){
    //Create struct holding settings together
    auto settings = make_shared<CSettings>();

    //Read CLI information for application RUN into prepared settings struct
    CCli Cli(settings);
    try{
        Cli.readSettings(argc, argv);
    } catch (const exception & e){
        Cli.write(e.what());
        return 1;
    }

    //Settings output
    Cli.printSettings();

    //Give control to download engine and start downloading.
    try{
        CDownEngine engine(settings);
        engine.start(); //TODO stats as input-output value
    } catch (const invalid_argument & e){
        Cli.write(e.what());
        return 2;
    } catch (const filesystem::filesystem_error & fe){
        cout << fe.what() << endl;
        return 5;
    } catch (...){
        cout << "Unknown ERROR occurred." << endl;
    }

    //TODO print downloading stats
    //engine.printStats();

    cout << "Konec programu!" << endl;
    return 0;
}