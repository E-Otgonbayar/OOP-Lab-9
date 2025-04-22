#include <iostream>
#include <vector>
using namespace std;

class Person {
protected:
    string name;
    string ssn;
    int age;
public:
    Person(string name = "", string ssn = "", int age = 0)
        : name(name), ssn(ssn), age(age) {}

    virtual void print() {
        cout << "Name: " << name << ", SSN: " << ssn << ", Age: " << age << endl;
    }
};

class Spouse : public Person {
    string anniversaryDate;
public:
    Spouse(string name = "", string ssn = "", int age = 0, string date = "")
        : Person(name, ssn, age), anniversaryDate(date) {}

    void print() override {
        Person::print();
        cout << "Anniversary Date: " << anniversaryDate << endl;
    }
};

class Child : public Person {
    string favoriteToy;
public:
    Child(string name = "", string ssn = "", int age = 0, string toy = "")
        : Person(name, ssn, age), favoriteToy(toy) {}

    void print() override {
        Person::print();
        cout << "Favorite Toy: " << favoriteToy << endl;
    }
};

class Division {
    string divisionName;
public:
    Division(string name = "") : divisionName(name) {}

    void print() {
        cout << "Division: " << divisionName << endl;
    }
};

class JobDescription {
    string description;
public:
    JobDescription(string desc = "") : description(desc) {}

    void print() {
        cout << "Job Description: " << description << endl;
    }
};

class Employee : public Person {
    string companyID;
    string title;
    string startDate;
    Spouse* spouse; // 0..1
    vector<Child> children; // 0..n
    Division* division; // 1
    vector<JobDescription*> jobDescriptions; // 1..n
public:
    Employee(string name, string ssn, int age,
             string companyID, string title, string startDate,
             Division* div, vector<JobDescription*> jds)
        : Person(name, ssn, age), companyID(companyID), title(title),
          startDate(startDate), spouse(nullptr), division(div),
          jobDescriptions(jds) {}

    void setSpouse(Spouse* s) { spouse = s; }
    void addChild(Child c) { children.push_back(c); }

    void print() override {
        Person::print();
        cout << "Company ID: " << companyID << ", Title: " << title
             << ", Start Date: " << startDate << endl;
        if (division) division->print();

        cout << "Job Descriptions:\n";
        for (auto jd : jobDescriptions) {
            jd->print();
        }

        if (spouse) {
            cout << "Spouse:\n";
            spouse->print();
        } else {
            cout << "No Spouse\n";
        }

        cout << "Children:\n";
        if (children.empty()) cout << "No children\n";
        for (auto& c : children) {
            c.print();
        }
        cout << "---------------------------\n";
    }
};
int main() {
    Division d1("IT"), d2("Management");

    JobDescription jd1("Developer"), jd2("Team Lead"), jd3("Manager");

    vector<JobDescription*> jobs1 = { &jd1, &jd2 };
    vector<JobDescription*> jobs2 = { &jd3 };

    Employee e1("Otgonbayar", "123456", 30, "C001", "Engineer", "2020-01-01", &d1, jobs1);
    Employee e2("Telmuun", "789101", 28, "C002", "Manager", "2021-05-15", &d2, jobs2);

    Spouse s1("Munhjin", "222333", 29, "2019-06-20");
    e1.setSpouse(&s1);

    Child c1("Bayaraa", "999000", 5, "Lego Togloom"), c2("Temuujin", "888777", 3, "Uraldaanii mashin");
    e1.addChild(c1);
    e1.addChild(c2);

    e1.print();
    e2.print();

    return 0;
}
