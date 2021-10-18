/*
* 
* Name: Concepcion Ardon
* Date:10/16/2021
* CS210
* Project 3
* 
*/
#include <Python.h>

#include <iostream>

#include <iomanip>

#define NOMINMAX

#include <Windows.h>

#undef NOMINMAX

#include <cmath>

#include <string>

#include <fstream>

using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}

void menu() {
	//Initialize method-specific variables
	int menuLoop = 0; 
	int wordCount = 0; 
	int itemQuantity = 0; 
	string searchTerm; 
	string itemName; 
	string blueColor = "\033[34;1m"; 
	string defaultColor = "\033[0m"; 
	ifstream fileInput; 

	while (menuLoop != 4) {
	// Menu choices
		std::cout << "============================================================" << std::endl;
		std::cout << "|             CORNER GROCER : GROCERY TRACKING             |" << std::endl;
		std::cout << "============================================================" << std::endl;
		std::cout << "|1. Calculate the number of times each item was purchased  |" << std::endl;
		std::cout << "|2. Calculate the frequency of a specific item             |" << std::endl;
		std::cout << "|3. Create a histogram                                     |" << std::endl;
		std::cout << "|4. Quit                                                   |" << std::endl;
		std::cout << "|Enter your selection as a number 1, 2, or 3               |" << std::endl;
		std::cout << "============================================================" << std::endl;
		std::cin >> menuLoop;

		//Checks for the users input (valid/invalid)

		while (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Error! Invalid selection: ";
			std::cin >> menuLoop;

		}

		switch (menuLoop) {
		case 1:  //Calculates the number of times each item was purchased
			system("CLS"); 
			CallProcedure("CountAll"); //Calls the Python function "CountAll"
			std::cout << std::endl; 
			break;

		case 2:       //Calculate the number of times a specific item appears
			system("CLS");
			std::cout << "What item would you like to look for?" << std::endl;
			std::cin >> searchTerm;
			//Calls the Python function with the search term, then return an integer word count value.
			wordCount = callIntFunc("CountInstances", searchTerm);
			//Prints the statement with a returned word count.
			std::cout << std::endl << searchTerm << " : " << wordCount << std::endl << std::endl;
			break;
			
		case 3:      //Case 3: Prints a histogram based on how many times each item appears.
			system("CLS"); 
			CallProcedure("CollectData"); //Calls the Python function "CollectData"
			fileInput.open("frequency.dat"); //Opens the frequency.dat file
			fileInput >> itemName; //Collects the first item on list
			fileInput >> itemQuantity; //Collects the first quantity on list

			while (!fileInput.fail()) {
				//Sets the text color to the default white
				std::cout << defaultColor;
				//Prints the items names
				std::cout << std::setw(14) << std::left << itemName << std::setw(6);
				//Sets the histogram color to blue
				std::cout << blueColor;
				//Prints the itemQuantity number of asterisks
				for (int i = 0; i < itemQuantity; i++) 
				{
					//Print asterisks in line.
					std::cout << std::right << "*";
				}
				std::cout << std::endl;
				fileInput >> itemName;
				fileInput >> itemQuantity;
			}

			//Closes the frequency.dat file

			fileInput.close();

			std::cout << defaultColor << endl;

			break;

			//Case 4 Ends program.

		case 4:

			return;

			//Default case: Invalid input

		default:

			std::cout << "Error! Invalid selection: ";

			std::cout << std::endl;

			break;

		}

	}

}

//Main method. Calls the menu method to collect user input.

void main()

{

	//Displays the user menu.

	menu();

}