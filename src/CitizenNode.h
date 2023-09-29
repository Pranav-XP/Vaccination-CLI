#pragma once
#include <string>

using namespace std;

struct citizenData {
    int c_id;
    string fname;
    string lname;
    char gender;
    int age;
    int phoneNumber;
    string address;
};

class CitizenNode
{
    friend class CitizenList;
    friend class citizenVaccinated;

private:
    citizenData data;
    CitizenNode* next;
    CitizenNode* prev;

public:
    CitizenNode();
};

