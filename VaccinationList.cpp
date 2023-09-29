#include "VaccinationList.h"
#include "Vaccines.h"
#include "CitizenList.h"
#include "Vaccines.h"
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <limits>

using namespace std;

VaccinationList::VaccinationList()
{
	this->vHead = NULL;
	this->vTail = NULL;
}

void VaccinationList::discard_line(ifstream& in)
{
	char c;

	do
		in.get(c);
	while (c != '\n');
}

void VaccinationList::readVFile(ifstream& infile, VaccinationList& vList, int& vCount)
{
    infile.open("vaccination.txt");

    if (!infile.is_open()) {
        cerr << "Error: Could not open vaccinations file!" << endl;
        system("PAUSE");
        exit(1);
    }
    vList.discard_line(infile);

    vaccData temp;
    vCount = 0;
    while (infile >> temp.c_id >> temp.num_vac >> temp.V1_code >> temp.V1_date >> temp.V2_code >> temp.V2_date >> temp.B_code >> temp.B_date) {
        vList.AppendNode(temp);
        vCount++;
    }
}

void VaccinationList::AppendNode(vaccData input)
{
    VaccNode* node = new VaccNode;
    node->data = input;
    if (vHead == NULL) {     //if list is empty
        vHead = node;        //make head point to pNode
        node->prev = NULL;
    }
    else {
        vTail->next = node;  //make tail point to pNode
        node->prev = vTail;
    }
    vTail = node;        //tail is now pNode
    node->next = NULL;  //pNode next now points to NULL
}

void VaccinationList::printVaccination(VaccinationList vList,CitizenList citList, Vaccines* viPtr,int viSize,int vSize, int citSize, float partial, float fully, float fullyB, float vTotal)
{
	if (vHead == NULL) {
		cout << "VACCINATION LIST IS EMPTY" << endl;
		return;
	}

	cout << "\n\t\t\t\t\t\t\tVACCINATION RECORDS\n";
	cout << "\t---------------------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "\tCID" << "\tFull Name" << "\tAge" << "\t#VAC" << "\tV1 Name" << "\t\tV1 Date" << "\t\tV2 Name" << "\t\tV2 Date" << "\t\tBooster name" << "\tBooster date\n";
	cout << "\t---------------------------------------------------------------------------------------------------------------------------------------" << endl;

	VaccNode* vTemp = vHead;
	for (vTemp = vHead; vTemp != NULL; vTemp = vTemp->next) {
		cout << "\t" << vTemp->data.c_id << "\t";
		cout << citList.fetchFullName(vTemp->data.c_id);
		cout << "\t" << citList.fetchAge(citList, vTemp->data.c_id);
		cout << "\t" << vTemp->data.num_vac << "\t";

		//Checking the statistsics of vaccinations
		if (vTemp->data.num_vac == 1) {
			partial++;
		}
		else if (vTemp->data.num_vac == 2) {
			fully++;
		}
		else {
			fullyB++;
		}

		//Printing Vaccine 1 details
		cout << viPtr->fetchVname(viPtr,vTemp->data.V1_code,viSize);
		cout << "\t" << vTemp->data.V1_date << "\t";


		//Printing vaccine 2 name
		if (vTemp->data.V2_code == 0) {
			cout << " ";
		}
		else {
			cout << viPtr->fetchVname(viPtr,vTemp->data.V2_code,viSize);
		}

		//Print Vaccine 2 Date
		if (vTemp->data.V2_date == 0) {
			cout << " ";
		}
		else {
			cout << "\t" << vTemp->data.V2_date << "\t";
		}

		//Printing booster name
		if (vTemp->data.B_code == 0) {
			cout << " ";
		}
		else {
			cout << viPtr->fetchVname(viPtr, vTemp->data.B_code, viSize);
		}

		//Printing booster date
		if (vTemp->data.B_date == 0) {
			cout << " ";
		}
		else {
			cout << "\t" << vTemp->data.B_date;
		}
		cout << endl;

	}
	for (int i = 0; i < vSize; i++) {

	}
	cout << "\n\tTotal vaccinated: " << vSize << " out of " << citSize << " = " << fixed << setprecision(2) << findVaccPercent(vTotal, citSize) << "%";
	cout << "\n\tPartial vaccinated: " << fixed << setprecision(0) << partial << " out of " << vSize << " = " << fixed << setprecision(2) << findVaccPercent(partial, vTotal) << "%";
	cout << "\n\tFully vaccinated: " << fixed << setprecision(0) << fully << " out of " << vSize << " = " << fixed << setprecision(2) << findVaccPercent(fully, vTotal) << "%";
	cout << "\n\tFully vaccinated with booster: " << fixed << setprecision(0) << fullyB << " out of " << vSize << " = " << fixed << setprecision(2) << findVaccPercent(fullyB, vTotal) << "%";
}

void VaccinationList::bubbleSort()
{
	int checkSwap;
	VaccNode* ptr1;
	VaccNode* ptr2 = NULL;

	if (vHead == NULL) {
		return;
	}

	do {
		checkSwap = 0;
		ptr1 = vHead;

		while (ptr1->next != ptr2) {
			if (ptr1->data.num_vac < ptr1->next->data.num_vac) {
				swap(ptr1->data, ptr1->next->data);
				checkSwap = 1;
			}
			ptr1 = ptr1->next;
		}
		ptr2 = ptr1;
	} while (checkSwap);

}

void VaccinationList::bubbleSortID()
{
	int checkSwap, i;
	VaccNode* ptr1;
	VaccNode* ptr2 = NULL;

	if (vHead == NULL) {
		return;
	}

	do {
		checkSwap = 0;
		ptr1 = vHead;

		while (ptr1->next != ptr2) {
			if (ptr1->data.c_id > ptr1->next->data.c_id) {
				swap(ptr1->data, ptr1->next->data);
				checkSwap = 1;
			}
			ptr1 = ptr1->next;
		}
		ptr2 = ptr1;
	} while (checkSwap);

}

VaccNode* VaccinationList::search(int key)
{
	VaccNode* temp = vHead;
	for (temp; temp != NULL; temp = temp->next) {
		if (temp->data.c_id == key) {
			return temp;
		}
	}
	return NULL;
}

void VaccinationList::printResult(VaccNode* result, Vaccines *viPtr,int viSize)
{
	cout << "\t-----------------------------------------------------------" << endl;
	cout << "\tNumber of vaccines: " << result->data.num_vac << endl;
	cout << "\tVaccination 1: ";
	cout << viPtr->fetchVname(viPtr, result->data.V1_code, viSize); 
	cout << "\tVaccination 1 date: " << result->data.V1_date << endl;
	cout << "\tVaccination 2: ";
	if (result->data.V2_code == 0) {
		cout << left << setw(10) << "N/A";
	}
	else {
		cout << viPtr->fetchVname(viPtr,result->data.V2_code,viSize);
	}
	cout << "\tVaccination 2 date: ";
	if (result->data.V2_date == 0) {
		cout << "N/A" << endl;;
	}
	else {
		cout << result->data.V2_date << endl;
	}
	cout << "\tBooster: ";
	if (result->data.B_code == 0) {
		cout << left << setw(8) << "N/A";
	}
	else {
		cout << viPtr->fetchVname(viPtr,result->data.B_code,viSize);
	}
	cout << "\t\tBooster date: ";
	if (result->data.B_date == 0) {
		cout << "N/A" << endl;
	}
	else {
		cout << result->data.B_date << endl;
	}
	cout << "\tVaccination status: ";
	if (result->data.num_vac == 1) {
		cout << "Partially vaccinated";
	}
	else if (result->data.num_vac == 2) {
		cout << "Fully vaccinated";
	}
	else {
		cout << "Fully vaccinated with booster\n";
	}
}

void VaccinationList::deleteNode(VaccNode* result,int &vCount)
{
	//Base case
	if (vHead == NULL || result == NULL) {
		return;
	}

	//If deleted node is head node
	if (vHead == result) {
		vHead = result->next;
	}

	//Correcting next pointer if needed
	if (result->next != NULL) {
		result->next->prev = result->prev;
	}

	//Correcting prev pointer if needed
	if (result->prev != NULL) {
		result->prev->next = result->next;
	}

	//Free Memory
	delete(result);
	vCount--;
	return;
}

float VaccinationList::findVaccPercent(float tally, float total) {
	float percent;
	percent = tally * 100 / total;
	return percent;
}

int VaccinationList::fetchNumvac(int key)
{
	for (VaccNode* temp = vHead; temp!= NULL;temp=temp->next)
	{
		if (temp->data.c_id == key) {
			return temp->data.num_vac;
		}
	}
	return 0;
}

int VaccinationList::fetchVCode(int key, int type)
{	
	if (type == 1) {
		for (VaccNode* temp = vHead; temp != NULL; temp = temp->next) {
			if (temp->data.c_id == key) {
				return temp->data.V1_code;
			}
		}
	}

	if (type == 2) {
		for (VaccNode* temp = vHead; temp != NULL; temp = temp->next) {
			if (temp->data.c_id == key) {
				return temp->data.V2_code;
			}
		}
	}

	if (type == 3) {
		for (VaccNode* temp = vHead; temp != NULL; temp = temp->next) {
			if (temp->data.c_id == key) {
				return temp->data.B_code;
			}
		}
	}

	return 0;
}

int VaccinationList::fetchVdate(int key, int type)
{
	if (type == 1) {
		for (VaccNode* temp = vHead; temp != NULL; temp = temp->next) {
			if (temp->data.c_id == key) {
				return temp->data.V1_date;
			}
		}
	}

	if (type == 2) {
		for (VaccNode* temp = vHead; temp != NULL; temp = temp->next) {
			if (temp->data.c_id == key) {
				return temp->data.V2_date;
			}
		}
	}

	if (type == 3) {
		for (VaccNode* temp = vHead; temp != NULL; temp = temp->next) {
			if (temp->data.c_id == key) {
				return temp->data.B_date;
			}
		}
	}
	return 0;
}