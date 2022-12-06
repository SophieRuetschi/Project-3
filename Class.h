#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
using namespace std;
//-------------------------------------AREA CLASS-----------------------------------
class Area{
private:
  int objectID;
  string stateFIPS;
  string countyFIPS;
  double natWalkIndex;

public:
  Area();
  Area(int object, string state, string county, double index);
  double getIndex();
  string getState();
  string getCounty();
  int getObjID();
};

//default Area constructor- initalize everything to 0
Area::Area(){
  objectID = 0;
  stateFIPS = '0';
  countyFIPS = '0';
  natWalkIndex = 0;
};

//Area constructor- initalize everything to respective arguments
Area::Area(int object, string state, string county, double index){
  objectID = object;
  stateFIPS = state;
  countyFIPS = county;
  natWalkIndex = index;
};

//index accessor
double Area::getIndex(){
  return natWalkIndex;
}

//state FIPS code accessor
string Area::getState() {
  return stateFIPS;
}

//county FIPS code accessor
string Area::getCounty() {
  return countyFIPS;
}

//object ID accessor
int Area::getObjID() {
    return objectID;
}

//-------------------------------------FIPS CLASSES-----------------------------------
//class to act as County FIPS dictionary 
class CountyFIPS{
private:
    map<string, string> FIPSData;

public:
    CountyFIPS();
    string getCountyName(string num);
    string getCountyNumber(string name);
};

//constructor
// used Lab 4 from Programming Fundamentals 2 as reference for reading from csv file
CountyFIPS::CountyFIPS(){
  
  // open file
  fstream inFile;
  inFile.open("CityCounty_FIPS.txt");

  string line;
  string num;
  string name;
  string space;

  while(getline(inFile, line)) {
    stringstream s(line);

    //read past whitespace
    getline(s, space, ' ');
    getline(s, space, ' ');
    getline(s, space, ' ');
    getline(s, space, ' ');

    //get the county FIPS code
    getline(s, num, ' ');

    //read past the white space
    getline(s, space, ' ');
    getline(s, space, ' ');
    getline(s, space, ' ');
    getline(s, space, ' ');
    getline(s, space, ' ');
    getline(s, space, ' ');
    getline(s, space, ' ');

    //get the name of the county
    getline(s, name);

    //push new infromation into the map
    FIPSData[num] = name;
  }
}

//return the string that matches the FIPS number
string CountyFIPS::getCountyName(string num){
    if(FIPSData.find(num) == FIPSData.end())
        return num;
    return FIPSData[num];
}

//returns the FIPS number associated with the string, -1 if no match found
string CountyFIPS::getCountyNumber(string name){

  for(auto it = FIPSData.begin(); it != FIPSData.end(); it++){
    if(it->second == name)
      return it->first;
  }
  return "";
}

//class to act as County FIPS dictionary 
class StateFIPS{
private:
    map<string, string> FIPSData;

public:
    StateFIPS();
    string getStateName(string num);
    string getStateNumber(string name);
};

// used Lab 4 from Programming Fundamentals 2 as reference for reading from csv file
StateFIPS::StateFIPS(){

  //open the file
  fstream inFile;
  inFile.open("StateFIPS.txt");

  string line;
  string num;
  string abv;
  string state;

  //read past the header
  getline(inFile, line);

  //loop through whole file
  while (getline(inFile, line)) {
    stringstream s(line);

    //seperate out the relevant infromation
    getline(s, num, '|');
    getline(s, abv, '|');
    getline(s, state, '|');

    //push back new info into the map
    FIPSData[num] = state;
  }
}

//function to return the string name of a state given the FIPS code
string StateFIPS::getStateName(string FIPS) {
  return FIPSData[FIPS];
}

//function to return the FIPS code of a state given the string name
string StateFIPS::getStateNumber(string name){

  for(auto it = FIPSData.begin(); it != FIPSData.end(); it++){
    if(it->second == name)
      return it->first;
  }
  return "";
}
/*
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
using namespace std;
//-------------------------------------AREA CLASS-----------------------------------
class Area{
private:
    int objectID;
    string stateFIPS;
    string countyFIPS;
    double natWalkIndex;

public:
    Area();
    Area(int object, string state, string county, double index);
    double getIndex();
    string getState();
    string getCounty();
    int getObjID();

};

Area::Area(){
    objectID = 0;
    stateFIPS = '0';
    countyFIPS = '0';
    natWalkIndex = 0;
};

Area::Area(int object, string state, string county, double index){
    objectID = object;
    stateFIPS = state;
    countyFIPS = county;
    natWalkIndex = index;
};

double Area::getIndex(){
    return natWalkIndex;
}

string Area::getState() {
    return stateFIPS;
}

string Area::getCounty() {
    return countyFIPS;
}

int Area::getObjID() {
    return objectID;
}

//-------------------------------------FIPS CLASSES-----------------------------------
class CountyFIPS{
private:
    map<string, string> FIPSData;

public:
    CountyFIPS();
    string getCountyName(string num);
    string getCountyNumber(string name);
};

//constructor
// used Lab 4 from Programming Fundamentals 2 as reference for reading from csv file
CountyFIPS::CountyFIPS(){
    // load data from file
    fstream inFile;

    // note - file is located in cmake-build-debug folder
    // open file
    inFile.open("CityCounty_FIPS.txt");

    string line;
    string num;
    string name;
    string space;

    while(getline(inFile, line)) {
        stringstream s(line);

        getline(s, space, ' ');
        getline(s, space, ' ');
        getline(s, space, ' ');
        getline(s, space, ' ');

        getline(s, num, ' ');

        getline(s, space, ' ');
        getline(s, space, ' ');
        getline(s, space, ' ');
        getline(s, space, ' ');
        getline(s, space, ' ');
        getline(s, space, ' ');
        getline(s, space, ' ');

        getline(s, name);

        FIPSData[num] = name;
    }
}

//return the string that matches the FIPS number
string CountyFIPS::getCountyName(string num){
    if(FIPSData.find(num) == FIPSData.end())
        return num;
    return FIPSData[num];
}

//returns the FIPS number associated with the string, -1 if no match found
string CountyFIPS::getCountyNumber(string name){

    for(auto it = FIPSData.begin(); it != FIPSData.end(); it++){
        if(it->second == name)
            return it->first;
    }

    return "";
}


class StateFIPS{
private:
    map<string, string> FIPSData;

public:
    StateFIPS();
    string getStateName(string num);
    string getStateNumber(string name);
};

// used Lab 4 from Programming Fundamentals 2 as reference for reading from csv file
StateFIPS::StateFIPS(){

    // load data from file
    fstream inFile;

    // note - file is located in cmake-build-debug folder
    // open file
    inFile.open("StateFIPS.txt");

    string line;
    string num;
    string abv;
    string state;

    getline(inFile, line);

    while (getline(inFile, line)) {
        stringstream s(line);

        getline(s, num, '|');
        getline(s, abv, '|');
        getline(s, state, '|');

        FIPSData[num] = state;
    }
}

string StateFIPS::getStateName(string FIPS) {
    return FIPSData[FIPS];
}

string StateFIPS::getStateNumber(string name){

    for(auto it = FIPSData.begin(); it != FIPSData.end(); it++){
        if(it->second == name)
            return it->first;
    }

    return "";
}
*/