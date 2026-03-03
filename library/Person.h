//
// Created by cendyz775 on 2026/03/03.
//

#ifndef LIBRARY_PERSON_H
#define LIBRARY_PERSON_H


#include <string>
#include <unordered_map>
#include <vector>
using std::vector;
using std::unordered_map;
using std::string;

class Person {
protected:
    unordered_map<int, vector<string>> normal_person;
    unordered_map<int, vector<string>> employee;



public:
    Person();
    ~Person();

private:
    void add_ppl_to_variable();
};

#endif //LIBRARY_PERSON_H