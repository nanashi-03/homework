#include <iostream>
#include <string>
#include <ctime>

using namespace std;

class Person {
private:
  string name;
  int day, month, year;
  int age;

public:
  Person(string n, int d, int m, int y) {
    name = n;
    day = d;
    month = m;
    year = y;
  }

  void calculateAge();
  string getAgeCategory();

  void display() {
    calculateAge();
    cout << "\nName: " << name << endl;
    cout << "Date of Birth: " << day << "/" << month << "/" << year << endl;
    cout << "Age: " << age << endl;
    cout << "Category: " << getAgeCategory() << endl;
  }
};

void Person::calculateAge(){
  time_t now = time(NULL);
  tm* ltm = localtime(&now);

  int cday = ltm->tm_mday;
  int cmonth = ltm->tm_mon + 1;
  int cyear = ltm->tm_year + 1900;

  age = cyear - year;

  if(cmonth < month || (cmonth == month && cday < day))
    age--;
}

string Person::getAgeCategory(){
  if(age < 0)
    return "Invalid Age";
  else if(age >= 0 && age < 18)
    return "Under Age";
  else if(age >= 18 && age < 30)
    return "Young Adult";
  else if(age >= 30 && age < 45)
    return "Matured Adult";
  else if(age >= 45 && age < 60)
    return "Middle Aged";
  else
    return "Senior Citizen";
}

int main() {
  string name;
  int d, m, y;
  char delim;

  cout << "Enter Name: ";
  getline(cin, name);

  cout << "Enter Date of Birth: ";
  cin >> d >> delim >> m >> delim >> y;

  Person p(name, d, m, y);
  p.display();

  return 0;
}
