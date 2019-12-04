#include<iostream>
#include<string>
using namespace std;

#include "jpeg_encoder.h"

int main()
{

	string name;
	cout << "Enter input file name: ";
	getline(cin, name);
	cin.ignore(0);

	string out_name = name.substr(0, name.length() - 4) + ".jpeg";

	JpegEncoder encoder;
	encoder.readFromBMP(name.c_str());
	encoder.encodeToJPG(out_name.c_str(), 99);

	return EXIT_SUCCESS;
}