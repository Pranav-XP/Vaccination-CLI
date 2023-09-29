#include "CitizenNode.h"
#include "CitizenList.h"
#include "VaccinationList.h"
#include "VaccNode.h"
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

//Constructor
CitizenList::CitizenList()
{
	this->citHead = NULL;
	this->citTail = NULL;
}

//Open and read citizen file
void CitizenList::readCitizenFile(ifstream& infile, CitizenList& citList, int& citCount)
{
    infile.open("citizens.txt");

    if (!infile.is_open()) {
        cerr << "Error: Could not open citizens file!" << endl;
        system("PAUSE");
        exit(1);
    }
    citList.discard_line(infile);

    citizenData temp;
    citCount = 0;
    while (infile >> temp.c_id >> temp.fname >> temp.lname >> temp.gender >> temp.age >> temp.phoneNumber >> temp.address) {
        citList.AppendNode(temp);
        citCount++;
    }
}

//Add Node to the end of the linked list
void CitizenList::AppendNode(citizenData input)
{
    CitizenNode* node = new CitizenNode;
    node->data = input;
    if (citHead == NULL) {     //if list is empty
        citHead = node;        //make head point to pNode
        node->prev = NULL;
    }
    else {
        citTail->next = node;  //make tail point to pNode
        node->prev = citTail;
    }
    citTail = node;        //tail is now pNode
    node->next = NULL;  //pNode next now points to NULL
}

void CitizenList::printCitizen()
{
    if (citHead == NULL) {
        cout << "ERROR: NO CITIZENS DATA FOUND" << endl;
        return;
    }
    cout << "\t\t\t\tCITIZENS DATA\n";
    cout << "\t----------------------------------------------------------------------------" << endl;
    cout << "\tCID" << "\tFname" << "\tLname" << "\tGender" << "\tAge" << "\tPhone" << "\t\tAddress\n";
    cout << "\t----------------------------------------------------------------------------" << endl;

    CitizenNode* temp = citTail;
    while (temp != NULL) {
        cout << "\t" << temp->data.c_id << "\t" << temp->data.fname << "\t" << temp->data.lname << "\t  " << temp->data.gender << "\t" << temp->data.age << "\t" << temp->data.phoneNumber << "\t\t" << temp->data.address << endl;
        temp = temp->prev;
    }

    cout << endl;
}

CitizenNode* CitizenList::getHead()
{
    return citHead;
}

CitizenNode* CitizenList::Search(int key)
{   
    CitizenNode* temp = citHead;
    for (temp; temp != NULL; temp=temp->next) {
        if (temp->data.c_id == key) {
            return temp;
        }
    }
    return NULL;
}

void CitizenList::printResult(CitizenNode* temp)
{
    cout << "\t-----------------------------------------------------------" << endl;
    cout << "\tCitizen ID: " << temp->data.c_id << endl;
    cout << "\tName: " << temp->data.fname << " " << temp->data.lname << endl;
    cout << "\tGender: " << temp->data.gender << endl;
    cout << "\tAge: " << temp->data.age << endl;
    cout << "\tPhone: " << temp->data.phoneNumber << endl;
    cout << "\tAddress: " << temp->data.address << endl;
}


//Utility Functions
void CitizenList::discard_line(ifstream& in)
{
    char c;

    do
        in.get(c);
    while (c != '\n');
}

string CitizenList::fetchFullName(int key) {
    CitizenNode* temp = citHead;

    for (temp; temp != NULL; temp = temp->next) {
        if (temp->data.c_id == key) {
            return temp->data.fname +" "+ temp->data.lname;
        }
    }

}

int CitizenList::fetchAge(CitizenList citList, int key) {
    CitizenNode* temp = citList.citHead;

    for (temp; temp != NULL; temp = temp->next) {
        if (temp->data.c_id == key) {
            return temp->data.age;
        }
    }
}

void CitizenList::printRec(VaccinationList vList, Vaccines *viPtr, int viSize)
{
    cout << "\n\t\t\t\t\t\t\tVACCINATION ANALYSIS\n";
    cout << "\t----------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "\tCID" << "\tFull Name" << "\tAge" << "\t#VAC" << "\tVaccination Status" << "\t\t\tRecommendation\n";
    cout << "\t----------------------------------------------------------------------------------------------------------------------------" << endl;

    int min_space;
    int n;
    int cDate;
    cDate = 16793183;

    CitizenNode* temp = citHead;
    for (temp; temp != NULL; temp = temp->next) {
        cout << "\t" << temp->data.c_id << "\t";
        cout << temp->data.fname << " " << temp->data.lname;
        cout << "\t" << temp->data.age;
        cout << "\t" << vList.fetchNumvac(temp->data.c_id);

		//between ages 18 and 59

		if (temp->data.age >= 18 && temp->data.age <= 59) {
			if (vList.fetchNumvac(temp->data.c_id) == 0) {
				cout << "\tNot vaccinated";
				cout << "\t\t\t\tGet vaccinated" << endl;
			}
			else if (vList.fetchNumvac(temp->data.c_id) == 1) {
				cout << "\tPartially vaccinated"; //NUM VAC=1
				min_space = viPtr->fetchVminspace(viPtr, vList.fetchVCode(temp->data.c_id, vList.fetchNumvac(temp->data.c_id)),viSize);
				n = cDate - vList.fetchVdate(temp->data.c_id, vList.fetchNumvac(temp->data.c_id));
				if (n < min_space) {
					cout << "\t\t\t" << min_space - n << " days left for second vaccine: ";
					cout << viPtr->fetchVname(viPtr, vList.fetchVCode(temp->data.c_id, vList.fetchNumvac(temp->data.c_id)), viSize);
					cout << endl;
				}
				else {
					cout << "\t\t\tReady for second shot: ";
					cout << viPtr->fetchVname(viPtr, vList.fetchVCode(temp->data.c_id, vList.fetchNumvac(temp->data.c_id)), viSize);
					cout << endl;
				}
			}
			else if (vList.fetchNumvac(temp->data.c_id) == 2) {
				cout << "\tFully vaccinated";
				min_space = viPtr->fetchVminspace(viPtr, vList.fetchVCode(temp->data.c_id, vList.fetchNumvac(temp->data.c_id)), viSize);
				n = vList.fetchVdate(temp->data.c_id, vList.fetchNumvac(temp->data.c_id)) - vList.fetchVdate(temp->data.c_id, 1);
				if (n < min_space) {
					cout << "\t\t\t" << min_space - n << " days left for the booster vaccine: Pfizer_2.0\n";
				}
				else {
					cout << "\t\t\tReady for Booster vaccine: Pfizer_2.0\n";
				}
			}
			else {
				cout << "\tFully vaccinated with Booster";
				cout << "\t        Fully vaccinated with Booster\n";
			}
		}

		//Between ages 6 to 7

		else if (temp->data.age >= 6 && temp->data.age <= 17) {
			if (vList.fetchNumvac(temp->data.c_id) == 0) {
				cout << "\tNot vaccinated";
				cout << "\tGet vaccinated" << endl;
			}
			else if (vList.fetchNumvac(temp->data.c_id) == 1) {
				cout << "\tPartially vaccinated";
				min_space = viPtr->fetchVminspace(viPtr, vList.fetchVCode(temp->data.c_id, vList.fetchNumvac(temp->data.c_id)), viSize);
				n = cDate - vList.fetchVdate(temp->data.c_id, vList.fetchNumvac(temp->data.c_id));
				if (n < min_space) {
					cout << "\t\t\t" << min_space - n << " days left for second shot: ";
					cout << viPtr->fetchVname(viPtr, vList.fetchVCode(temp->data.c_id, vList.fetchNumvac(temp->data.c_id)), viSize);
					cout << endl;
				}
				else {
					cout << "\t\t\tReady for second vaccine: ";
					cout << viPtr->fetchVname(viPtr, vList.fetchVCode(temp->data.c_id, vList.fetchNumvac(temp->data.c_id)), viSize);
					cout << endl;
				}
			}
			else if (vList.fetchNumvac(temp->data.c_id) == 2) {
				cout << "\tFully vaccinated";
				min_space = viPtr->fetchVminspace(viPtr, vList.fetchVCode(temp->data.c_id, vList.fetchNumvac(temp->data.c_id)), viSize);
				n = vList.fetchVdate(temp->data.c_id, vList.fetchNumvac(temp->data.c_id)) - vList.fetchVdate(temp->data.c_id, 1);
				if (n < min_space) {
					cout << "\t\t\t" << min_space - n << " days left for booster vaccine: Pfizer_2.0\n";
				}
				else {
					cout << "\t\t\tReady for Booster vaccine: Pfizer_2.0\n";
				}
			}
			else {
				cout << "\t\tFully vaccinated with booster";
				cout << "Fully vaccinated with booster\n";
			}
		}




		else {
			if (vList.fetchNumvac(temp->data.c_id) == 0) {
				cout << "\tNot vaccinated";
				cout << "\tGet vaccinated" << endl;
			}
			else if (vList.fetchNumvac(temp->data.c_id) == 1) {
				cout << "\tPartially vaccinated";
				min_space = viPtr->fetchVminspace(viPtr, vList.fetchVCode(temp->data.c_id, vList.fetchNumvac(temp->data.c_id)), viSize);
				n = cDate - vList.fetchVdate(temp->data.c_id, vList.fetchNumvac(temp->data.c_id));
				if (n < min_space) {
					cout << "\t\t\t" << min_space - n << " days left for second shot: ";
					cout << viPtr->fetchVname(viPtr, vList.fetchVCode(temp->data.c_id, vList.fetchNumvac(temp->data.c_id)), viSize);
					cout << endl;
				}
				else {
					cout << "\t\t\tReady for second vaccine: ";
					cout << viPtr->fetchVname(viPtr, vList.fetchVCode(temp->data.c_id, vList.fetchNumvac(temp->data.c_id)), viSize);
					cout << endl;
				}
			}
			else {
				cout << "\tFully vaccinated";
				cout << "\t\t\tFully vaccinated. Booster is not needed\n";
			}
		}
    }

}

void CitizenList::bubbleSort()
{
	int checkSwap, i;
	CitizenNode* ptr1;
	CitizenNode* ptr2 = NULL;

	if (citHead == NULL) {
		return;
	}

	do {
		checkSwap = 0;
		ptr1 = citHead;

		while (ptr1->next != ptr2) {
			if (ptr1->data.age < ptr1->next->data.age) {
				swap(ptr1->data, ptr1->next->data);
				checkSwap = 1;
			}
			ptr1 = ptr1->next;
		}
		ptr2 = ptr1;
	} while (checkSwap);

}



