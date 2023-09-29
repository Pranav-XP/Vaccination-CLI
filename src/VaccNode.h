#pragma once
#include <string>

using namespace std;

struct vaccData {
	int c_id;
	int num_vac;
	int V1_code;
	int V1_date;
	int V2_code;
	int V2_date;
	int B_code;
	int B_date;
};

class VaccNode
{
	friend class VaccinationList;
	friend class citizenVaccinated;

private:
	vaccData data;
	VaccNode* next;
	VaccNode* prev;

public:
	VaccNode();
};

