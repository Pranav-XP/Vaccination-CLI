#include "Vaccines.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

Vaccines::Vaccines()
{
	;
}

Vaccines::~Vaccines()
{
	;
}

void Vaccines::setVCode(int code)
{
	this->vaccine_code = code;
}

void Vaccines::setVname(string name)
{
	this->vaccine_name = name;
}

void Vaccines::setVminspace(int minspace)
{
	this->vaccine_minspace = minspace;
}

int Vaccines::getVcode()
{

	return vaccine_code;
}

string Vaccines::getVname() {
	return vaccine_name;
}

int Vaccines::getVminspace() {
	return vaccine_minspace;
}

string Vaccines::fetchVname(Vaccines* ptr, int key, int viSize)
{
	for (int i = 0; i < viSize; i++) {
		if ((ptr + i)->vaccine_code == key) {
			return (ptr + i)->vaccine_name;
		}
	}
}

int Vaccines:: fetchVminspace(Vaccines* ptr, int key, int viSize)
{
	for (int i = 0; i < viSize; i++) {
		if ((ptr + i)->vaccine_code == key) {
			return (ptr + i)->vaccine_minspace;
		}
	}
}


