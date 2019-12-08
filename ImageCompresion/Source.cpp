#include<iostream>
#include<string>
using namespace std;

#include "jpeg_encoder.h"

int main()
{
	while (1) {
		system("cls");

		string name;
		cout << ">> Enter input file name (0: End process ): ";
		getline(cin, name);
		cin.ignore(0);

		if (name.length() == 1 && stoi(name) == 0) {
			return EXIT_SUCCESS;
		}

		string out_name = name.substr(0, name.length() - 4) + ".jpeg";

		JpegEncoder encoder;
		encoder.readFromBMP(name.c_str());
		encoder.encodeToJPG(out_name.c_str(), 50);

		cout << "\nDONE !\n\n";

		system("pause");
	}

	return EXIT_SUCCESS;
}