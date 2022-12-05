//References: "Quick Sort Code"- Lecture 6-Sorting slide 122, Geeks for Geeks: Bucket Sort - https://www.geeksforgeeks.org/bucket-sort-2/ , Lab 4 from Programming Fundamentals 2, Geeks for Geeks: Chrono in C++ - https://www.geeksforgeeks.org/chrono-in-c/ , "Insertion Sort Code"- Lecture 6-Sorting slide 38
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
#include <set>
#include <chrono>
#include "Class.h"
using namespace std;
using namespace chrono;
//--------------------------------FUNCTION PROTOTYPES--------------------------------------------
void swap(Area& a, Area& b);
int partition(vector<Area>& unsorted, int low, int high);
void quickSortIndex(vector<Area>& unsorted, int low, int high);
void readFile(vector<Area>& areaObjectsVector, map <string, vector<Area>>& areaObjectsByStateMap, map <string, vector<Area>>& areaObjectsByCountyMap);
void bucketSort(vector<Area>& unsorted);
void insertionSort(vector<Area>& unsorted);
void highestWalk(vector<Area>& sorted, StateFIPS& stateDictionary, CountyFIPS& countyDictionary);
void lowestWalk(vector<Area>& sorted, StateFIPS& stateDictionary, CountyFIPS& countyDictionary);

//--------------------------------MAIN FUNCTION--------------------------------------------
int main() {
    //set up objects to keep track of time
    time_point<system_clock> start, end; 

    //load in and copy data
    vector<Area> copy1;
    map <string, vector<Area>> areaByState;
    map <string, vector<Area>> areaByCounty;

    cout << "Hello! Welcome to the Walkability Index Organizer." << endl;
    cout << "Loading in 2019 US Census data..." << endl;
  
    readFile(copy1, areaByState, areaByCounty);
    vector<Area> copy2 = copy1;

    //load in state and county FIPS infromation for FIPS->name (string) conversions
    StateFIPS stateDictionary;
    CountyFIPS countyDictionary;

    int menuSelection;

    //offer selection
    cout << "-----------------------------------------------------------------------" << endl;
    cout << "Would you like to learn about the areas with the best walkability or worst in the nation?" << endl;
    cout << "1. Best" << endl;
    cout << "2. Worst" << endl;

    cin >> menuSelection;
    cout << "-----------------------------------------------------------------------" << endl;
    cout << "Calculating..." << endl;

    //call each sort, time each sort
    //timing method referenced - Geeks for Geeks: Chrono in C++ - https://www.geeksforgeeks.org/chrono-in-c/
    start = system_clock::now();
    //call quick sort
    quickSortIndex(copy1, 0, copy1.size() - 1); // low = 0, high = # of area objs
    end = system_clock::now();
    duration<double> quickTime = end - start;

    start = system_clock::now();
	  //call bucket sort
    bucketSort(copy2);
	end = chrono::system_clock::now();
    duration<double> bucketTime = end - start;

    //print time and area results
    cout << "It took " << quickTime.count() << "seconds to find your result using quick sort." << endl;
    cout << "It took " << bucketTime.count() << "seconds to find your result using bucket sort." << endl;
    cout << "Quick sort was " << bucketTime.count() - quickTime.count() << " seconds faster than bucket sort." << endl;
    cout << "-----------------------------------------------------------------------" << endl;

    if(menuSelection == 1){
        cout << "The areas with the highest walkability in the nation are:" << endl;
        highestWalk(copy1, stateDictionary, countyDictionary);
    }
    else if(menuSelection == 2){
        cout << "The areas with the lowest walkability in the nation are:" << endl;
        lowestWalk(copy1, stateDictionary, countyDictionary);
    }
    else {
        cout << "You have entered an invalid selection! Please enter a number 1-3" << endl;
    }

    //offer additional searches
    cout << "-----------------------------------------------------------------------" << endl;
    cout << "Please enter the level of which you would you like to further access walkability or \nif you would like to end the program." << endl;
    cout << "1. State" << endl;
    cout << "2. County" << endl;
    cout << "3. Exit" << endl;
    cin >> menuSelection;

    //run loop while user does not exit
    while(menuSelection != 3){
    
    if (menuSelection == 1) {
        //if the user selects 1, they want to search on the state level
        //get the user's state of intrest
        cout << "-----------------------------------------------------------------------" << endl;
        cout << "Which state would you like to learn about?" << endl;
        cout << "Please enter the state name with a capital first letter ex. Florida" << endl;
        string state;
        cin.ignore(); // leading whitespace was causing getline to not work so this solves that
        getline(cin, state); // use getline for states that have two words

        //check if valid state
        while(stateDictionary.getStateNumber(state) == ""){
            cout << "Invalid state entry, please type in a valid state." << endl;
            getline(cin, state); // use getline for states that have two words
        }

        //get metric of intrest
        cout << "-----------------------------------------------------------------------" << endl;
        cout << "For the state of " << state << " which of the following would you like to know?" << endl;
        cout << "1. The average walkability of " << state << endl;
        cout << "2. The areas where the highest walkability is found " << state << endl;
        cout << "3. The areas where the lowest walkability is found in " << state << endl;
        cin >> menuSelection;

        if(menuSelection == 1){
          //user wants the average walkibility of the state
          //get the vector of area objects for the appropriate state
          vector<Area> targetState = areaByState[stateDictionary.getStateNumber(state)];
          double stateAverage = 0;

          //add up the walking indexes of each area object associated with the state of intrest
          for(int i = 0; i < targetState.size(); i++){
            stateAverage += targetState[i].getIndex();
          }
          //calculate the average and print the result
          stateAverage = stateAverage /(targetState.size() - 1);
          cout << "The average walkability for " << state << " is " << stateAverage << endl;
        }
        else if(menuSelection == 2){
          //user wants a list of areas in the state with the highest walkibility
          //get the vector of area objects associated with the state of intrest
          vector<Area> targetState = areaByState[stateDictionary.getStateNumber(state)];
          //sort the vector, find the results, print the results
          quickSortIndex(targetState, 0, targetState.size() - 1);
          cout << "The counties with the highest walkability in " << state << " are:" << endl;
          highestWalk(targetState, stateDictionary, countyDictionary);
          
        }
        else if(menuSelection == 3){
          //user wants a list of areas in the state with the lowest walkibility
          //get the vector of area objects associated with the state of intrest
          vector<Area> targetState = areaByState[stateDictionary.getStateNumber(state)];
          //sort the vector, find the results, print the results
          quickSortIndex(targetState, 0, targetState.size() - 1);
          cout << "The counties with the lowest walkability in " << state << " are: " << endl;
          lowestWalk(targetState, stateDictionary, countyDictionary);
        }
        else
          cout << "You have entered an invalid selection! Please enter a number 1-3" << endl;

    }
    else if (menuSelection == 2) {
      //if the user selected 2, they want metrics on the county level
      //get the state of intrest
      cout << "-----------------------------------------------------------------------" << endl;
      cout << "In what state is the county you are looking for?" << endl;
      cout << "Please enter the state name with a capital first letter ex. Florida" << endl;
      string state;
      cin.ignore(); // leading whitespace was causing getline to not work so this solves that
      getline(cin, state); // use getline for states that have two words

      //check if valid state
      while(stateDictionary.getStateNumber(state) == ""){
        cout << "Invalid state entry, please type in a valid state." << endl;
        getline(cin, state); // use getline for states that have two words
      }

      //get county of intrest
      cout << "Please enter the county name with a capital first letter followed by \"County\" ex. Alachua County" << endl;
      string county;
      getline(cin, county); // use getline for states that have two words

      //get the vector of the state the county is in
      vector<Area> targetState = areaByState[stateDictionary.getStateNumber(state)];
      double countyAverage = 0;
      int countyEntries = 0;

      //iterate through all of the area objects in the state, if the county of the object matches the target county, add it to the total
      for(int i = 0; i < targetState.size(); i++){
        if(county == countyDictionary.getCountyName(targetState[i].getCounty())){
            countyAverage += targetState[i].getIndex();
            countyEntries++;
        }
      }

      //county entered was invalid if no additions were made
      if (countyEntries == 0)
        cout << "Invalid county entry, please try again." << endl;
      else{
        //calculate and print the result
        countyAverage = countyAverage / countyEntries;
        cout << "The average walkability for " << county << " is " << countyAverage << endl;
      }
    }
    else {
      cout << "You have entered an invalid selection! Please enter a number 1-3" << endl;
    }

    //print and get menu selection
    cout << "-----------------------------------------------------------------------" << endl;
    cout << "Please enter the level of which you would you like to access walkability \nor if you would like to end the program." << endl;
    cout << "1. State" << endl;
    cout << "2. County" << endl;
    cout << "3. Exit" << endl;
    cin >> menuSelection;
  }

  //thank the user and exit
  cout << "-----------------------------------------------------------------------" << endl;
  cout << "Thank you for using our program, happy walking!" << endl;

  return 0;

}

//--------------------------------FUNCTION DEFINITIONS--------------------------------------------

//Reference: adapted from "Quick Sort Code"- Lecture 6-Sorting slide 122
void swap(Area& a, Area& b) {
  Area t = a;
  a = b;
  b = t;
}

//Reference: adapted from "Quick Sort Code"- Lecture 6-Sorting slide 122
//break vector up acoring to pivot element
int partition(vector<Area>& unsorted, int low, int high) {
  // Select the pivot element
  Area pivot = unsorted[low];
  int up = low, down = high;

  while (up < down){
    for (int j = up; j < high; j++){
      if (unsorted[up].getIndex() > pivot.getIndex())
        break;
        up++;
      }
    for (int j = high; j > low; j--){
      if (unsorted[down].getIndex() < pivot.getIndex())
        break;
      down--;
    }
    if (up < down)
      swap(unsorted[up], unsorted[down]);
  }
  
  swap(unsorted[low], unsorted[down]);
  return down;
}

//Reference: adapted from "Quick Sort Code"- Lecture 6-Sorting slide 122
void quickSortIndex(vector<Area>& unsorted, int low, int high) {
  if (low < high){
    int pivot = partition(unsorted, low, high);
    quickSortIndex(unsorted, low, pivot - 1);
    quickSortIndex(unsorted, pivot + 1, high);
  }
}

//Reference: adapted from "Insertion Sort Code"- Lecture 6-Sorting slide 38
void insertionSort(vector<Area>& unsorted) {
  for (int i = 1; i < unsorted.size(); i++) {
    Area key = unsorted[i];
    int j = i - 1;

    // Compare key with each element in sorted till smaller value is found
    while (j >= 0 && key.getIndex() < unsorted[j].getIndex()) {
      unsorted[j + 1] = unsorted[j];
      j--;
    }
    unsorted[j + 1] = key;
  }
}

//Reference: adapted from Geeks for Geeks: Bucket Sort - https://www.geeksforgeeks.org/bucket-sort-2/
void bucketSort(vector<Area>& unsorted) {
  //number of data points we have
  const int n = 220740;

  // our walkability index can range from 1-20, so we will have a bucket for 1, 2, 3, ... 20
  vector<Area> b[21];

  //iterate through each Area object in the vector, add it into the respective bucket
  for (int i = 0; i < n; i++) {
    int bi = unsorted[i].getIndex(); // Index in bucket
    b[bi].push_back(unsorted[i]);
  }

  //sort each bucket
  for (int i = 0; i < 21; i++) {
    if (b[i].size() > 1) {
      insertionSort(b[i]);
    }
  }

  //combind all of the buckets
  int index = 0;
  for (int i = 0; i < 21; i++) {
    for (int j = 0; j < b[i].size(); j++) {
      unsorted[index] = b[i][j];
      index++;
    }
  }
}

// open csv file, load data, and read rows to create Area class objects
// used Lab 4 from Programming Fundamentals 2 as reference for reading from csv file
void readFile(vector<Area>& areaObjectsVector, map <string, vector<Area>>& areaObjectsByStateMap, map <string, vector<Area>>& areaObjectsByCountyMap) {

  //open file
  fstream inFile;
  inFile.open("EPA_SmartLocationDatabase_V3_Jan_2021_Final.csv");

  // get rid of header
  string line;
  getline(inFile, line);

  int objectID;
  string stateFIPS;
  string countyFIPS;
  double natWalkIndex;

  //loop through the end of the file
  while (getline(inFile, line)) {
    //make a stringstream object out of the curent line
    stringstream s(line);
    string tempObjectID;
    getline(s, tempObjectID, ',');
    objectID = stoi(tempObjectID);

    //seperate the state FIPS code and update if missing beginning 0's
    getline(s, stateFIPS, ',');
    if(stateFIPS.length() < 2)
      stateFIPS = "0" + stateFIPS;

    //seperate the county FIPS code and update if missing beginning 0's
    getline(s, countyFIPS, ',');
    if(countyFIPS.length() == 1)
      countyFIPS = "00" + countyFIPS;
    else if(countyFIPS.length() == 2)
      countyFIPS = "0" + countyFIPS;
    countyFIPS = stateFIPS + countyFIPS;

    //seperate the walking index, and convert the string to a double
    string tempNatWalkIndex;
    getline(s, tempNatWalkIndex, ',');
    natWalkIndex = stod(tempNatWalkIndex);

    //create an area object with the new infromation and add object into the vector and maps
    Area areaObj(objectID, stateFIPS, countyFIPS, natWalkIndex);
    areaObjectsVector.push_back(areaObj);
    areaObjectsByStateMap[stateFIPS].push_back(areaObj);
    areaObjectsByCountyMap[countyFIPS].push_back(areaObj);
  }
}

//function to print out the areas with the highest walkibility from the sorted area vector
void highestWalk(vector<Area>& sorted, StateFIPS& stateDictionary, CountyFIPS& countyDictionary){
  //create a set to keep track of what has been printed
  set<pair<string, string>> printed;
  int i = sorted.size() - 1;
  double largest = sorted[i].getIndex();

  //loop through the vector, starting from the largest walkibilities, print at least 5 objects
  //note- loop will run more than 5 times if there are more than 5 areas tied for highest walkibility
  while(sorted[i].getIndex() == largest || printed.size() < 5){
    if(printed.count(make_pair(sorted[i].getCounty(), sorted[i].getState())) == 0){
      //if the current object has not been printed, print it and add it to the set 
      cout << countyDictionary.getCountyName(sorted[i].getCounty()) << " in " << stateDictionary.getStateName(sorted[i].getState()) << endl;
      printed.insert(make_pair(sorted[i].getCounty(), sorted[i].getState()));
    }
    i--;
  }
}

//function to print out the areas with the lowest walkibility from the sorted area vector
void lowestWalk(vector<Area>& sorted, StateFIPS& stateDictionary, CountyFIPS& countyDictionary){
  //create a set to keep track of what has been printed
  set<pair<string, string>> printed;
  int i = 0;
  double smallest = sorted[0].getIndex();

  //loop through the vector, starting from the smallest walkibilities, print at least 5 objects
  //note- loop will run more than 5 times if there are more than 5 areas tied for lowest walkibility
  while(sorted[i].getIndex() == smallest || printed.size() < 5){
    if(printed.count(make_pair(sorted[i].getCounty(), sorted[i].getState())) == 0){
      //if the current object has not been printed, print it and add it to the set 
      cout << countyDictionary.getCountyName(sorted[i].getCounty()) << " in " << stateDictionary.getStateName(sorted[i].getState()) << endl;
      printed.insert(make_pair(sorted[i].getCounty(), sorted[i].getState()));
    }
    i++;
  }
}