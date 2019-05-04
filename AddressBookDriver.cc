#include <ctime>
#include <iostream>
using namespace std;
#include "Person.h"
#include "AddressBook.h"

void displayMenu();
int promptMenuChoice();
void updateAddressBook(AddressBook *addressBook);
void searchForContact(AddressBook*);
void searchAndDeletePerson(AddressBook *addressBook);
void addPersonFromUserInput(AddressBook *addressBook);

const string ADDRESS_BOOK = "Address Book";
const string SEARCH_RESULTS = "Search Results";

int main() {
    AddressBook *addressBook = new AddressBook();
    AddressBook *searchResults;
    string searchTerms;
    srand (time(NULL));
    int menuInput;
    bool isQuit = false;
    do {
        displayMenu();
        menuInput = promptMenuChoice();
        cout << "You entered: " << menuInput << endl << endl;
        switch(menuInput) {
            case 0: //Print AddressBook
                addressBook->print(ADDRESS_BOOK);
                break;
            case 1: //Add a new contact (User Input)
                addPersonFromUserInput(addressBook);
                break;
            case 2: //Add a new contact (Pre-filled data)
                addressBook->addPerson(new Person());
                break;
            case 3: //Update an existing contact
                updateAddressBook(addressBook);
                break;
            case 4: //Delete a contact
                searchAndDeletePerson(addressBook);
                break;
            case 5: //List all added contacts in sorted order
                addressBook->sort();
                addressBook->print(ADDRESS_BOOK);
                break;
            case 6: //Search for a given contact
                searchForContact(addressBook);
                break;
            case 7: //Quit
                isQuit = true;
                break;
        }
    } while (!isQuit);
    cout << "Thank you for using AddressBook. Good bye!\n\n";
	delete addressBook;
    return 0;
}


void displayMenu() {
    cout << "==============================================\n"
        << "\t\t Menu \n"
        << "==============================================\n"
        << "  0. Print AddressBook\n"
        << "  1. Add a new contact (User Input)\n"
        << "  2. Add a new contact (Pre-Filled Data)\n"
        << "  3. Update an existing contact\n"
        << "  4. Delete a contact\n"
        << "  5. List all added contacts in sorted order\n"
        << "  6. Search for a given contact\n"
        << "  7. Quit\n"
        << "==============================================\n"
        << endl;
}


int promptMenuChoice() {
    bool isValidInput = true,
         isUnexpectedInput = false;
    int menuInput;
    do {
        cout << "What would you like to do? ";
        cin >> menuInput;
        if (cin.fail()) {
            //Validate input data type; e.g. Did cin get an integer?
            isUnexpectedInput = true;
            isValidInput = false;
        }
        //Avoid infinite loop in case cin failed.
        cin.clear();
        cin.ignore(numeric_limits<int>::max(), '\n');
        if (isUnexpectedInput) {
            cout << "Opps. Please choose from the menu number.\n";
            isUnexpectedInput = false;
        } else if (menuInput < 0 || menuInput > 7) {
            //Validate numerical ranges.
            cout << "The number you entered, " << menuInput
                << " is out of range. Please try again.\n";
            isValidInput = false;
        } else
           isValidInput = true;
    } while (!isValidInput);
    return menuInput;
}


void updateAddressBook(AddressBook *addressBook) {
    string searchTerms;
    int index;
    AddressBook *searchResults;
    Person *target;
    Person *tmp_person;
    cout << "Who's entry would you like to update? (Case-Sensitive) ";
    getline(cin, searchTerms);
    cout << "You entered: " << searchTerms << "\n\n";
    searchResults = addressBook->searchFor(searchTerms);
    searchResults->print(SEARCH_RESULTS);
    if (!searchResults->isEmpty()) {
        target = searchResults->getNth(1);
        if (searchResults->getLength() > 1) {
            //More than one matches
            cout << "Which one? (index number) ";
            cin >> index;
            cin.clear();
            cin.ignore(numeric_limits<int>::max(), '\n');
            target = searchResults->getNth(index);
        }
        cout << "\nThe following entry will be updated: \n"
            << target->toString() << "\n\n";
        tmp_person = new Person;
        string s;
        cout << "First name (Press ENTER to skip): ";
        getline(cin, s);
        tmp_person->setFirstName(s);
        if (tmp_person->getFirstName() != "")
            cout << "You entered: '" << tmp_person->getFirstName() << "'\n";
        else
            cout << "Skipping; First name will not be updated.\n";
        cout << endl;
        //
        cout << "Last name (Press ENTER to skip): ";
        getline(cin, s);
        tmp_person->setLastName(s);
        if (tmp_person->getLastName() != "")
            cout << "You entered: '" << tmp_person->getLastName() << "'\n";
        else
            cout << "Skipping; Last name will not be updated.\n";
        cout << endl;
        //
        cout << "Phone Number (Press ENTER to skip): ";
        getline(cin, s);
        tmp_person->setPhone(s);
        if (tmp_person->getPhone() != "")
            cout << "You entered: '" << tmp_person->getPhone() << "'\n";
        else
            cout << "Skipping; Phone number will not be updated.\n";
        cout << endl;
        //
        cout << "Address (Press ENTER to skip): ";
        getline(cin, s);
        tmp_person->setAddress(s);
        if (tmp_person->getAddress() != "")
            cout << "You entered: " << tmp_person->getAddress() << "'\n";
        else
            cout << "Skipping; Address field will not be updated.\n";
        cout << endl;
        //
        addressBook->updatePerson(target, tmp_person);
        cout << "\n" << target->getFirstName() << " " << target->getLastName() << "'s entry has successfully updated.\n\n";
        //
        delete tmp_person;
        tmp_person = nullptr;
        delete searchResults;
        searchResults = nullptr;
    } else {
        cout << "No matching records to update.\n";
    }
}


void searchAndDeletePerson(AddressBook *addressBook) {
    AddressBook *searchResults;
    string searchTerms;
    cout << "Which entry would you like to delete? ";
    getline(cin, searchTerms);
    searchResults = addressBook->searchFor(searchTerms);
    if ( !searchResults->isEmpty() ) {
        string personStr = addressBook->remove(searchTerms);
        cout << "The following entry was removed from the Address Book.\n"
            << personStr << "\n\n";
    }
    else
        cout << searchTerms << " was not found. No entry was deleted.\n\n";
}


void addPersonFromUserInput(AddressBook *addressBook) {
    string firstname,
           lastname,
           phone,
           address;
    cout << "First name? ";
    getline(cin, firstname);
    cout << "You entered: " << firstname << "\n\n";
    cout << "Last name? ";
    getline(cin, lastname);
    cout << "You entered: " << lastname << "\n\n";
    cout << "Phone? ";
    getline(cin, phone);
    cout << "You entered: " << phone << "\n\n";
    cout << "Address? ";
    getline(cin, address);
    cout << "You entered: " << address << "\n\n";
    addressBook->addPerson(
        firstname,
        lastname,
        phone,
        address
    );
}


void searchForContact(AddressBook *addressBook) {
    string searchTerms;
    AddressBook *searchResults = nullptr;
    cout << "Search (Case-Sensitive): ";
    getline(cin, searchTerms);
    cout << "Searching for: " << searchTerms << endl;
	searchResults = addressBook->searchFor(searchTerms);
	searchResults->print(SEARCH_RESULTS);
    if (searchResults->isEmpty()
            && searchTerms.find(" ") != string::npos)
        cout << "No results were found. "
            << "Try narrowing the search. "
            << "e.g. Just one word."
            << endl;
	delete searchResults;
}


