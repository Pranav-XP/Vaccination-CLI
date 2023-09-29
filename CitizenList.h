#pragma once
#include "CitizenNode.h"
#include "CitizenList.h"
#include "VaccinationList.h"
#include "VaccNode.h"

using namespace std;

class CitizenList
{
	friend class VaccinationList;
	friend class citizenVaccinated;

private:
	CitizenNode* citHead;
	CitizenNode* citTail;

public:
	CitizenList();
	void readCitizenFile(ifstream& infile, CitizenList& citList, int& citCount);
	void AppendNode(citizenData input);
	void printCitizen();

	//Sort and print recommendations
	void printRec(VaccinationList vList, Vaccines *viPtr, int viSize);
	void bubbleSort();
	

	//Search Methods
	//CitizenNode* MiddleNode();
	CitizenNode* Search(int key);
	void printResult(CitizenNode* temp);

	//Utility functions
	string fetchFullName(int key);
	int fetchAge(CitizenList citList, int key);
	CitizenNode* getHead();
	void discard_line(ifstream& in);

};

