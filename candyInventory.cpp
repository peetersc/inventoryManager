//Developer: Cameron Peeters
//Project: Candy Bar
//Abstract: Simple inventory system for candy bars and the amount of calories and weight in each different bar

//header files.
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>

// name spaces.
using namespace std;

// Candy Bar class.
class CandyBar
{
private:
	// vectors used in parallel to keep track of name, cal, and wght.
	vector<string> _brandName;
	vector<float> _candyCalories;
	vector<float> _candyWeight;

	//floats to hold total count of all candy.
	float totalCal;				
	float totalWght; 	

public:
	// Main Methods that add functionality the CandyBar class.
	void addCandyBar();
	void deleteCandy();
	void display();
	void saveData();
	void loadData();
	void clearData();
	void sort(vector<string> &, vector<float> &, vector<float> &, string);

	//Generic template used for swaping strings and ints
	template <class data>
	void swapData(data *, data *);	

	//Methods calls that can be called and access private CandyBar data
	void callSortCal();
	void callSortWght();
	void setTotal();


};

// Adds a new candy bar.  
void CandyBar::addCandyBar()
{
	//gets and pushes back the candys brand name.
	cout << "Add Candy: " << endl;
	cout << "Enter the new Candy Bar's brand name: ";

	cin.ignore(); 
	string brand;
	getline(cin, brand);

	_brandName.push_back(brand);

	//gets and pushes back the candys calories.
	cout << "Enter the calories for " << brand << ": ";
	float cal;
	float limit = 9999999999999.99;
	cin >> cal;

	while (cal > limit)
	{
		cout <<"Too big enter another number for the calories: ";
		cin >> cal;
	}
	_candyCalories.push_back(cal);

	//gets and pushes back the candys wieght.
	cout << "Enter the weight for " << brand << ": ";
	float wght;
	cin >> wght;

	while (wght > limit)
	{
		cout <<"Too big enter another number for the weight: ";
		cin >> wght;
	}
	_candyWeight.push_back(wght);

}

// Deletes a candy bar.
void CandyBar::deleteCandy()
{

	//checks to see if there are candy to delete.
	if (_brandName.size() == 0)
	{
		cout << "There is nothing to delete.\n" << endl;
		return;
	}
	else
	{
		//displays so the user knows which candy can be deleted.
		display();

		//gets candy's name to delete.
		cout << "Which candy do you whish to delete <enter candy's name>:";
		string delCandy;
		cin >> delCandy;

		//traverses the name vector and deletes if found else not found
		for (unsigned int i = 0; i < _brandName.size(); i++)
		{
			if (delCandy == _brandName[i])
			{
				_brandName.erase(_brandName.begin()+i);
				_candyCalories.erase(_candyCalories.begin()+i);
				_candyWeight.erase(_candyWeight.begin()+i);

				cout << "Candy was succesfully deleted." << endl;
				break;
			}
			else
			{
				cout << "This candy is not in the inventory." << endl;
				break;
			}
		}
	}
}

// Displays the candy bars in vector. 
void CandyBar::display()
{
	cout << "Display:" << endl;
	cout << "***********Candy Bar Crunch************" << endl;
	cout << "Brand Name\t Calories\t Weight" << endl;
	cout << "---------------------------------------" << endl;
	for (unsigned int i = 0; i < _brandName.size(); i++)
	{
		cout << _brandName[i] << setw(20 - _brandName[i].length()) << _candyCalories[i] << setw(17) << _candyWeight[i] << endl;
	}
	// Displays totals for candy bar calories and weight.
	setTotal();														
	cout << "\nTotal calories: " << totalCal << endl;
	cout << "Total weight: " << setw(4) << totalWght << endl;
	cout << "***************************************" << endl;
}

// Saves candy bar data to a .txt(candyBars.txt) file for all candy bars.
void CandyBar::saveData()
{
	ofstream outputFile;
	outputFile.open("candyBars.txt");

	cout << "Saving Data:\a" << endl;
	for (unsigned int i = 0; i < _brandName.size(); i++)
	{
		outputFile << _brandName[i] << "\t";
		outputFile << _candyCalories[i] << "\t";
		outputFile << _candyWeight[i] << "\t\r\n";

	}

	outputFile.close();
}

// Loads data from a file (candyBars.txt).
void CandyBar::loadData() 
{
	string name;
	float cal, wght;

	cout << "Loading Data:\a" << endl;
	ifstream inFile;
	inFile.open("candyBars.txt");

	if (inFile.is_open())
  	{
  		_brandName.clear();
  		_candyCalories.clear();
  		_candyWeight.clear();

  	  while (!inFile.eof())
    	{
    		inFile >> name >> cal >> wght;
    		_brandName.push_back(name);
    		_candyCalories.push_back(cal);
    		_candyWeight.push_back(wght);
    	
    	}

    	 _brandName.erase(_brandName.end()-1);
  		_candyCalories.erase(_candyCalories.end()-1);
  		_candyWeight.erase(_candyWeight.end()-1);

   	 inFile.close();
  	}
  	else
  	{
  		cout << "No data found.\n";
  	}
}

// Clears all data from the inventory.
void CandyBar::clearData()
{
	cout << "Warning this will clear all data and then save.\n" 
		 << "Do you wish to continue? Enter <y/n>:" << endl;

		 char decsion;
		 cin >> decsion;

		 if (decsion == 'y')
		 {
		 	_brandName.clear();
			_candyWeight.clear();
			_candyCalories.clear();
			saveData();
			cout << "Inventory cleared succesfully." << endl;
		 }
		 else
		 {
		 	cout << "No data was deleted.";
		 }
}

// bubble sort function that sorts the calories from least to greatest.
void CandyBar::sort(vector<string> &vectorName, vector<float> &vectorWeight, vector<float> &vectorCal, string type)
{
	cout << "Sorting: \n";
	//comparisons will be done n times.
    for (unsigned int i = 0; i < vectorCal.size(); i++)
    {
        //compare elemet to the next element, and swap if condition is true.
        for(unsigned int j = 0; j < vectorCal.size() - 1; j++)
        {   
        	//sorts by calories
        	if (type == "calories")
        	{
        		if (vectorCal[j] > vectorCal[j+1])
        		{
                	swapData(&vectorCal[j], &vectorCal[j+1]);
            		swapData(&vectorWeight[j], &vectorWeight[j+1]);
            		swapData(&vectorName[j], &vectorName[j+1]);
            	}
        	}
        	//sorts by weight
        	else if (type == "weight")
        	{
           		if (vectorWeight[j] > vectorWeight[j+1])
            	{
            	    swapData(&vectorCal[j], &vectorCal[j+1]);
            		swapData(&vectorWeight[j], &vectorWeight[j+1]);
            		swapData(&vectorName[j], &vectorName[j+1]);
            	}
        	}
        }
    }
}

// generic template and swap function used by the bubble sort to swap generic data.
template<class data>
void CandyBar::swapData(data *i, data *j)
{
	data temp = *i;
	*i = *j;
	*j = temp;

}

// sets totals for candy bar calories and weight.
void CandyBar::setTotal()
{
	totalCal = 0;				
	totalWght = 0;
	for (unsigned int i = 0; i < _candyWeight.size(); i++)
	{
		totalCal = totalCal + _candyCalories[i]; 
		totalWght = totalWght + _candyWeight[i];

	}
}

// function call to sort the callories to be called by the object.
void CandyBar::callSortCal()
{
	sort(_brandName, _candyWeight, _candyCalories, "calories");
}
// function call to sort the weight to be called by the object.
void CandyBar::callSortWght()
{
	sort(_brandName, _candyWeight, _candyCalories, "weight");
}
// Function prototypes.
void greetings();
void menu(CandyBar* candyBar);
void endOfFile();

// Main Function. 
int main()
{
	CandyBar* candyBar = new CandyBar;

	greetings();
	menu(candyBar);
	endOfFile();

	delete candyBar;
}

// Displays greeting to the user.  
void greetings()
{
	cout << "\nHello, welcome to the Candy Bar Counter Program.\n"
		 << "This program allows you to add, delete, save, sort, and display\n"
		 << "A candy bar's brand, weight, and calorie content.\n"	
		 << "From the following menu please select one of the following options.\n" << endl; 
}

// Function that displays the menu. 
void menu(CandyBar* candyBar)
{
	int option = 0;
	while (option != 9)
	{
		cout << "\nMenu: " 
			 << "\n1 - Add Candy               5 - Save Data" 
			 << "\n2 - Delete Single Candy     6 - Load Data"
			 << "\n3 - Display All Candy       7 - Clear Data" 
			 << "\n4 - Sort By Calories        8 - Sort By Weight" 
			 << "\n                            9 - Quit " << endl;

		cout << "Choose an option: ";
		cin >> option;
		if (option > 9 || option < 1)
		{
			cout << "Please select a valid option from the range (1-9).";
		}
		cout << endl;

		switch(option)
		{
			case 1:
				candyBar->addCandyBar();
				break;
			case 2:
				candyBar->deleteCandy();
				break;
			case 3:
				candyBar->display();
				break;
			case 4:
				candyBar->callSortCal();
				break;
			case 5:
				candyBar->saveData();
				break;
			case 6:
				candyBar->loadData();
				break;
			case 7:
				candyBar->clearData();
				break;
			case 8:
				candyBar->callSortWght();
				break;
		}
	}
}

// Displays ending message.
void endOfFile()
{
	cout << "Thank you for using the Candy Bar Counter Program, Have a nice day.\n" << endl;
}
