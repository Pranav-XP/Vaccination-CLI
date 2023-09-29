//Team FORGE
//Name: Pui Chen ID: S11209162
//Name: Pranav Chand ID: S11171153
// Please maximise console window for best UI experience!

#include "CitizenList.h"
#include "VaccinationList.h"
#include "Vaccines.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <limits>

const int SIZE = 10;

using namespace std;

void readViFile(ifstream& infile, Vaccines vi[], int& viCount);
void discard_line(ifstream& in);


int main() {
	//Creating data structures
	CitizenList citList;
	VaccinationList vList;
	Vaccines viArray[SIZE];

	ifstream citFile;
	ifstream vFile;
	ifstream viFile;


	int citCount;
	int vCount;
	int viCount;
	int cvCount;
	int choice;
	char choice2;
	int idSearch;

	float partialVacc;
	float fullVacc;
	float fullBVacc;
	float totVacc;

	//Reading files and populating lists
	citCount = 0;
	vCount = 0;
	viCount = 0;
	cvCount = 0;


	citList.readCitizenFile(citFile, citList, citCount);
	vList.readVFile(vFile, vList, vCount);
	readViFile(viFile, viArray, viCount);

	//Printing program introduction & menu
	cout << "\n\t=========================================================================\n";
	cout << "\t||\t\tWELCOME TO VACCINATION ANALYSIS PROGRAM  2.0              ||\n";
	cout << "\t=========================================================================\n";
	cout << "\t||This program will analyse medical vaccination records of citizens to ||\n";
	cout << "\t||provide deeper insight to assist medical health providers.           ||\n";
	cout << "\t||The program can display relevant medical entries, search for citizens||\n";
	cout << "\t||and provide vaccination recommendations accordingly.                 ||\n";
	cout << "\t||The program is faster and more efficient by using better sorting and ||\n";
	cout << "\t||search algorithms.                                                   ||\n";
	cout << "\t||PLEASE MAXIMISE CONSOLE WINDOW FOR BEST VIEWING EXPERIENCE           ||\n";
	cout << "\t=========================================================================\n";
	cout << "\tPress enter to continue . . .";
	cin.get();

	do {
		system("cls");
		cout << "\tPROGRAM MENU\n\n";
		cout << "\t1. Exit the program" << endl;
		cout << "\t2. Print all citizen's records" << endl;
		cout << "\t3. Print vaccination data" << endl;
		cout << "\t4. Search citizen using the Citizen ID" << endl;
		cout << "\t5. Print Recommendation\n";
		cout << "\t6. Delete Vaccination Record for a citizen\n" << endl;

		//Validating choice input
		for (;;) {
			cout << "\n\tEnter your option (1-6): ";
			if (cin >> choice) {
				break;
			}
			else {
				cout << "\n\tPlease enter a valid input 1-6" << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
		}

		//Running functions according to choice input
		if (choice == 1) {
			cout << "\tThank you for choosing this program." << endl;

			return 0;
		}
		else if (choice == 2) {
			citList.printCitizen();
			cout << "\tTotal entries: " << citCount;
			cout << "\n\n" << "\tPress enter to continue . . .";
			cin.get();
			cin.get();
			cout << endl;
		}
		else if (choice == 3) {
			partialVacc = 0;
			fullVacc = 0;
			fullBVacc = 0;
			totVacc = vCount; //Converting int to float to calculate percentage to 2 decimal places

			vList.bubbleSort();
			vList.printVaccination(vList,citList,viArray,viCount, vCount, citCount, partialVacc, fullVacc, fullBVacc, totVacc);
			cout << "\n\n" << "\tPress enter to continue . . .";
			cin.get();
			cin.get();
			cout << endl;
		}
		else if (choice == 4) {
			do {
				for (;;) {//Validating the search input
					cout << "\tEnter citizen ID to search: ";
					if (cin >> idSearch) {
						break;
					}
					else {
						cout << "\n\tERROR: Please enter a valid number input" << endl;
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
					}
				}

				//Searching for citizens data and printing accordingly
				CitizenNode* citResult;
				citResult=citList.Search(idSearch);
				if (citResult != NULL) {
					citList.printResult(citResult);
				}
				else {
					cout << "\tID NOT FOUND";
				}
				
				//Search Vaccination Data and printing accordingly
				VaccNode* vaccResult;
				vaccResult=vList.search(idSearch);
				if (vaccResult != NULL) {
					vList.printResult(vaccResult,viArray,viCount);
				}
				else {
					cout << "\tVACCINATION RECORDS NOT FOUND";
				}
				
				//Checks if user wishes to search again
				cout << "\n\n\tEnter Y to search again:  ";
				cin >> choice2;
				cout << endl;
			} while (choice2 == 'y' || choice2 == 'Y');
			cout << "\n\tPress enter to continue . . .";
			cin.get();
			cin.get();
			cout << endl;
		}
		else if (choice == 5) {
			citList.bubbleSort();
			citList.printRec(vList, viArray, viCount);
			cout << "\n\tPress enter to continue . . .";
			cin.get();
			cin.get();
		}
		else if (choice == 6) {
			do {
				for (;;) {//Validating the search input
					cout << "\tEnter citizen ID to search: ";
					if (cin >> idSearch) {
						break;
					}
					else {
						cout << "\n\tERROR: Please enter a valid number input" << endl;
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
					}
				}

				//Searching for citizen in vaccination
				VaccNode* deleted;
				deleted = vList.search(idSearch);
				if (deleted != NULL) {
					vList.deleteNode(deleted, vCount);
					cout << "\tTotal vaccination entries: " << vCount;
				}
				else {
					cout << "\tID NOT FOUND";
				}

				//Checks if user wishes to delete again
				cout << "\n\n\tEnter Y to delete again:  ";
				cin >> choice2;
				cout << endl;
			} while (choice2 == 'y' || choice2 == 'Y');

			cout << "\n\tPress enter to continue . . .";
			cin.get();
			cin.get();
			cout << endl;
		}
		else if (choice < 1 || choice > 6) {
			cerr << "\n\tERROR: Enter a valid number 1-6";
			cout << "\n\tPress enter to continue . . . ";
			cin.get();
			cin.get();
		}
		else {
			cerr << "\tERROR: Invalid input. Enter a number 1-6\n";
			cout << "\n\tPress enter to continue . . . ";
			cin.get();
			cin.get();
		}


	} while (choice != 1);

	return 0;

}

//Read and populate vaccines data
void readViFile(ifstream& infile, Vaccines vi[], int& viCount)
{
		infile.open("vaccines.txt");

		if (!infile.is_open()) {
			cerr << "Error: Could not open vaccines file!" << endl;
			system("PAUSE");
			exit(1);
		}

		discard_line(infile);

		int vaccine_code;
		string vaccine_name;
		int vaccine_minspace;

		while (!infile.eof()) {
			infile >> vaccine_code >> vaccine_name >> vaccine_minspace >> ws;
			vi->setVCode(vaccine_code);
			vi->setVname(vaccine_name);
			vi->setVminspace(vaccine_minspace);
			vi++;
			viCount++;
		}
}


//Utility function
void discard_line(ifstream& in)
{
		char c;

		do
			in.get(c);
		while (c != '\n');
}




