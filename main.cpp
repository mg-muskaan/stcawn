/*
	Title: Short Text Classification Accompanying WordNet
	Directed By: Dr. Sarah Zelikovitz
	Author: Lasha Zakariashvili

	Description: A different approach to stripping words (i will come up with better desc. later)
*/

//includes needed to compile on UNIX: cstdlib, cstring.
#include <cstdlib>
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <vector>
//#include "porter2_stemmer.h"

using namespace std;

extern void WNStrip(string);
extern void WNStrip(string, string);

int main() {

	char word[32] = "";					//Array to store user's WN search word
	char cmd[128] = "wn ";				//Array to store UNIX command
	char filename_in[128] = "";			//Array to store the input file name (FROM file)
	char filename_out[128] = "";		//Array to store the output file name (TO file)
	ifstream input;
	ifstream tmp;	//HOTFIX
	ofstream tmp1;	//HOTFIX
	string garbage = "asdasd";	//HOTFIX
	char tmp2 = 10;
	
	//------Menu-----------
	cout << "\n---Short Text Classifier---\n"
		<< "By: Lasha Zakariashvili\n\n"
		<< "How to use: Have a short list of words ready to be loaded (seperated\n"
		<< "by spaces). After the file is processed, it will output another file\n"
		<< "which compressed the previous file given.\n\n"

		<< "Please enter input filename: ";
	cin >> filename_in;
	cout << "Please enter output filename: ";
	cin >> filename_out;


	//----Obtaining WordNetOutput.txt from WordNet ----

	input.open(filename_in);
	if (!filename_in) {
		cout << "File input not found, terminating process!";
		return 0;
	}

	while (input.peek() != EOF) {
		cout << "Next letter: " << input.peek() << "\n";
		//Creating a command string to run through UNIX
		input >> word;								
		strcat(cmd, word);										
		strcat(cmd, " -a -hypon -treen > WN_Output.tmp");
		cout << cmd << '\n';
		system(cmd);										//Call the command in UNIX
		tmp.open("WN_Output.tmp");	//HOTFIX
		garbage = "~";
		tmp >> garbage;
		if (garbage == "~") {
			cout << "Running if-garbage\n";
			tmp1.open(filename_out, ios::app);
			tmp1 << word << "\n-\n";
			tmp1.close();
		} else {
																				
			WNStrip(filename_out);								//Strip and format WN output
		}
		strcpy(cmd, "wn ");
		strcpy(word, "");
		tmp.close();
		cin.get(tmp2);
															//***FUTURE: Instead of appending to 1 file, seperate into multi files
															//*****NOTE: I am going to use the LARGE FILE approach on this one
	}
	//------------------------------------------------


	system("pause");
	return 0;
}
