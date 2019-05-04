#ifndef ADDRESS_BOOK_H
#define ADDRESS_BOOK_H
#include "Person.h"
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;
class AddressBook {

public:
    AddressBook();
    ~AddressBook();

    /** Appends source to the end */
	void addPerson(Person *source);

    void addPerson(string _firstname, string _lastname, string _phone,
            string _address);
	void print(const string title) const;
	bool isEmpty() const;
	string remove(const string query);

    /** sorts in ascending order by Person::compare */
	void sort();

    /** appends a copy of Person nodes that had a match
     *      between its toString and query using string::find
     * returns an addressbook containing copies of Person nodes
     *      that matched the query string. */
	AddressBook* searchFor(const string query) const;

    /** First Person node that has a match with query is removed.
     * Return an empty string on a failed match, otherwise, returns
     *   a string representation of the removed Person node. */
    int getLength() const;

    /** The range of index is not checked.
     *    Index is not zero-based, and should be in the range of 1 to 
     *    getLength inclusively. i.e. [1, getLength]
     * Returns the Nth Person node in the address book, or nullptr if
     *    index is out of bounds. */
    Person* getNth(const int index) const;

    /** Updates on the first matching node.
     * target - is the Person node to find an exact match with
     * newPerson - data from newPerson will overwrite existing data
     * Note: blank entries in newPerson is skipped. */
    void updatePerson(Person *target, Person *newPerson);

private:
    Person *head;
};
#endif
