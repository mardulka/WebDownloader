#ifndef __PROGTEST__

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <utility>
#include <vector>
#include <array>
#include <cassert>

using namespace std;
#endif /* __PROGTEST__ */


/**
 * Class for storing records
 */
class record{
    string name;
    string surname;
    string number;

public:
    string line;
    record() = default;

    record(string iname, string isurname, string iline) : name{std::move(iname)}, surname{std::move(isurname)},
                                                          line{std::move(iline)}{}

    bool check(){
        if (number[0] == '0')
            return false;
        for (char const & c: number){
            if (isalpha(c)) return false;
        }
        return true;
    }

    bool find(const string & query){
        if (name == query || surname == query)
            return true;
        return false;
    }

    friend ostream & operator <<(ostream & stream, const record & rec);
};

ostream & operator <<(ostream & stream, const record & rec){
    stream << rec.name << " " << rec.surname << " " << rec.number << endl;
    return stream;
}

/**
 * Report function
 * @param fileName
 * @param out
 * @return
 */
bool report(const string & fileName, ostream & out){

    vector<record> storage;

    //open file for reading
    ifstream file;
    file.open(fileName);
    if (!file) return false;

    //cyklus cteni dat

    while (true){
        //precteni radku do stringu (prazdny --> break)
        string line;
        file >> line;
        if (line.empty() || file.eof()) break;

        //parsovani do recordu a kontroly
        istringstream ss(line);
        string name, surname, number, dummy;

        if (!(ss >> name) || !(ss >> surname) || !(ss >> number) || ss >> dummy) return false;
        record input(move(name), move(surname), move(number));
        if (!input.check()) return false;

        //ulozeni do vectoru
        storage.push_back(input);
    }


    //cyklus cteni dotazu
    while (!file.eof()){
        string query;
        file >> query;

        // cyklus kontroly vysledku
        int cnt = 0;
        for (record rec: storage){
            if (rec.find(query))
                out << rec;
        }
        out << cnt << endl;
    }


    return true;
}

#ifndef __PROGTEST__

int main(){
    ostringstream oss;
    oss.str("");
    assert (report("tests/test0_in.txt", oss) == true);
    assert (oss.str() ==
            "John Christescu 258452362\n"
            "John Harmson 861647702\n"
            "-> 2\n"
            "-> 0\n"
            "Josh Dakhov 264112084\n"
            "Dakhov Speechley 865216101\n"
            "-> 2\n"
            "John Harmson 861647702\n"
            "-> 1\n");
    oss.str("");
    assert (report("tests/test1_in.txt", oss) == false);
    return 0;
}

#endif /* __PROGTEST__ */
