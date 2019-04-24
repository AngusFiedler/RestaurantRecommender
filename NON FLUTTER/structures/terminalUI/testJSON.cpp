#include <iostream>
#include <fstream>
#include <string>
#include <fstream>
using namespace std;

#include "JSON.h"

class Test{
public:
	int number;
	string name;

};

BEGIN_CLASS_DESCRIPTOR(Test)
   CLASS_DESCRIPTOR_ENTRY(number)
   CLASS_DESCRIPTOR_ENTRY(name)
   // CLASS_DESCRIPTOR_ENTRY(moreTesting)
END_CLASS_DESCRIPTOR()


int main(){

	Test t0;

	t0.number = 7;
	t0.name = "Jacob";

	ofstream writeFile("out.json");
	WriteJSON(writeFile, anObject);

	return 0;
}