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
    record() = default;

    record(string iname, string isurname, string inumber) : name{std::move(iname)}, surname{std::move(isurname)},
                                                            number{std::move(inumber)}{}

    bool check(){
        if (number[0] == '0' || number.length() != 9)
            return false;
        for (char const & c: number){
            if (!isdigit(c)) return false;
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
    stream << rec.name << " " << rec.surname << " " << rec.number;
    return stream;
}

/**
 * Function read input from file, parse data into record class and store into vector
 * @param file File for read data
 * @param storage Vector for storage records
 * @return true if ok, false if error
 */
bool readInput(ifstream & file, vector<record> & storage){
    while (file){
        //read one line (empty --> break)
        string line;
        getline(file, line);
        if (line.empty()) break;

        //parsing and check data
        istringstream ss(line);
        string name, surname, number, dummy;
        if (!(ss >> name) || !(ss >> surname) || !(ss >> number) || ss >> dummy) return false;
        record input(move(name), move(surname), move(number));
        if (!input.check()) return false;

        //save into vector
        storage.push_back(input);
    }
    return true;
}

/**
 * Search query in given storage and print output
 * @param storage Vector of stored records
 * @param query Searching string
 * @param out output stream for printing
 */
void searchAndPrint(vector<record> & storage, string & query, ostream & out){
    int cnt = 0;
    if (query.empty()){
        out << "-> " << cnt << endl;
        return;
    }
    for (record rec: storage){
        if (rec.find(query)){
            out << rec << endl;
            ++cnt;
        }
    }
    out << "-> " << cnt << endl;
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
    if (!file.is_open()) return false;

    // read data first
    if (!readInput(file, storage)) return false;

    // Search and print
    while (file.peek() != EOF){
        string query;
        getline(file, query);
        searchAndPrint(storage, query, out);
    }

    return true;
}

#ifndef __PROGTEST__

int main(){
    ostringstream oss;
    oss.str("");
    assert (report("tests/test0_in.txt", oss) == true);
    //cout << oss.str() << flush;
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
    assert (report("tests/test2_in.txt", oss) == true);
    //cout << oss.str() << flush;
    assert (oss.str() ==
            "John Christescu 258452362\n"
            "John Christescu 258452362\n"
            "John Christescu 258452362\n"
            "-> 3\n"
            "-> 0\n"
            "-> 0\n"
            "-> 0\n"
            "-> 0\n");
    oss.str("");
    assert (report("tests/test3_in.txt", oss) == false);
    assert (report("tests/test4_in.txt", oss) == false);
    return 0;
}

#endif /* __PROGTEST__ */
