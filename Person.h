#ifndef PERSON_H
#define PERSON_H
#include <cstdlib>
#include <ctime>
#include <string>
#include <iostream>
using namespace std;
class Person {
public:
    Person();
    Person(string first, string last, string phone, string address);
	string  getFirstName() const;
    string  getLastName() const;
    string  getPhone() const;
    string  getAddress() const;
    Person* getNext() const;
    void setFirstName(const string);
    void setLastName(const string);
    void setPhone(const string);
    void setAddress(const string);
    void setNext(Person*);

    /**
     * Short-circuit comparison by last name, first name, phone, and
     *   finally by address.
     * Returns:
     *   neg if this is smaller than other.
     *     0 if this is the same as other.
     *   pos if this is larger than other.  */
    int compare(Person *other);

    string toString();
    friend ostream& operator<<(ostream&, const Person&);
    ~Person();
private:
    string firstname;
    string lastname;
    string phone;
    string address;
    Person* next;
    string getRandFirstName() const;
    string getRandLastName() const;
    string getRandPhone() const;  // format "(###) ###-####"
    string getRandAddress() const;
};
#endif
