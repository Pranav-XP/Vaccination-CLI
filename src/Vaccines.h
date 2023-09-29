#pragma once
#include <string>

using namespace std;

class Vaccines
{
	friend class VaccinationList;
	friend class citizenVaccinated;

public:
	Vaccines();
	~Vaccines();
	void setVCode(int code);
	void setVname(string name);
	void setVminspace(int minspace);
	int getVcode();
	string getVname();
	int getVminspace();

	//utility functions
	string fetchVname(Vaccines* ptr, int key, int viSize);
	int fetchVminspace(Vaccines* ptr, int key, int viSize);

private:
	int vaccine_code;
	string vaccine_name;
	int vaccine_minspace;

protected:

};

