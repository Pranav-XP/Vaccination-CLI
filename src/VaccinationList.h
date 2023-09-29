#pragma once
#include "Vaccines.h"
#include "VaccNode.h"
#include "CitizenList.h"

using namespace std;

class VaccinationList
{
	friend class CitizenList;
	friend class citizenVaccinated;

private:
	VaccNode* vHead;
	VaccNode* vTail;

public:
	VaccinationList();
	void readVFile(ifstream& infile, VaccinationList& vList, int& vCount); // Read and populate vaccination data
	void AppendNode(vaccData input);//Adds node to the end of linked list
	void printVaccination(VaccinationList vList,CitizenList citList, Vaccines* viPtr, int viSize, int vSize, int citSize, float partial, float fully, float fullyB, float vTotal);
	void bubbleSort(); // Sorts linked list according to Number of vaccines in descending order

	//Search methods
	void bubbleSortID(); //Sorts linked list according to c_id in ascending order
	VaccNode* search(int key);
	void printResult(VaccNode* result,Vaccines* viPtr, int viSize); //Prints result according to citizen ID

	//Delete Function
	void deleteNode(VaccNode* result,int &vCount); // Deletes node according to citizen ID

	//Utility functions
	float findVaccPercent(float total, float number);
	int fetchNumvac(int key);
	int fetchVCode(int key, int type);
	int fetchVdate(int key, int type);
	void discard_line(ifstream& in);
};

