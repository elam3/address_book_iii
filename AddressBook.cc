#include "AddressBook.h"

AddressBook :: AddressBook() {
    head = nullptr;
}


AddressBook :: ~AddressBook() {
    if (head != nullptr) {
        Person *current = head;
        while (head != nullptr) {
            head = head->getNext();
            delete current;
            current = head;
        }
    }
    head = nullptr;
}


void AddressBook :: addPerson(string _firstname, string _lastname, string _phone, string _address) {
    if (head == nullptr) {
        head = new Person(
            _firstname,
            _lastname,
            _phone,
            _address
        );
    } else {
        Person *curr = head;
        while (curr->getNext() != nullptr)
            curr = curr->getNext();
        curr->setNext(new Person(
            _firstname,
            _lastname,
            _phone,
            _address
		));
    }
}


void AddressBook :: addPerson(Person *source) {
    addPerson(
        source->getFirstName(),
        source->getLastName(),
        source->getPhone(),
        source->getAddress()
    );
}


void AddressBook :: print(const string title) const {
    cout << "==============================================\n"
        << "\t\t" << title << "\n"
        << "==============================================\n";
    if (head == nullptr) 
        cout << "\t(Empty)\n";
    else {
        Person *current = head;
        int index = 0;
        while (current != nullptr) {
            cout << setw(4) << ++index << ": "
                << *current << endl;
            current = current->getNext();
        }
    }
    cout << "==============================================\n"
        << endl;
}


void AddressBook :: sort() {
    if (head == nullptr || head->getNext() == nullptr)
        return; //Ignore empty list, or singletons.
    else {
        //There are at least 2 nodes.
        Person *current = head,
               *next,
               *prev;
        int len = 0;
        while (current != nullptr) {
            len++;
            current = current->getNext();
        }
        //Bubble Sort
        for (int i = 0; i < len; i++) {
            prev = head;
            current = head->getNext();
            next = head->getNext()->getNext();
            //If the first two nodes need to swap, head needs to be updated.
            if (prev->compare(current) > 0) {
                head = current;
                current->setNext(prev);
                prev->setNext(next);
                //Re-align the pointers
                prev = head;
                current = head->getNext();
                next = head->getNext()->getNext();
            }
            while (next != nullptr) {
                if (current->compare(next) > 0) {
                    struct Person *tmp = next->getNext();
                    prev->setNext(next);
                    next->setNext(current);
                    current->setNext(tmp);
                    //Re-aligni pointers
                    current = prev->getNext();
                    next = prev->getNext()->getNext();
                }
                prev = prev->getNext();
                current = current->getNext();
                next = next->getNext();
            }
        }
    }
    return;
}


AddressBook* AddressBook::searchFor(const string query) const {
    AddressBook *results = new AddressBook();
    if (head != nullptr && query.length() != 0) {
        Person *current = head;
        while (current != nullptr) {
            string personStr = current->toString();
            if (personStr.find(query) != string::npos)
                results->addPerson(current);
            current = current->getNext();
        }
    }
    return results;
}


string AddressBook::remove(const string query) {
	string personStr = "";
    if (head != nullptr) {
		// Remove first node?
        personStr = head->toString();
        if (personStr.find(query) != string::npos) {
			Person *tmp = head;
            head = head->getNext();
			delete tmp;
        } else {
		// Or remove other nodes?
            Person *current = head;
            while (current->getNext() != nullptr) {
                personStr = current->getNext()->toString();
                if (personStr.find(query) != string::npos) {
                    Person *tmp = current->getNext();
                    current->setNext(current->getNext()->getNext());
                    delete tmp;
                    break;
                }
                current = current->getNext();
            }
        }
    }
	return personStr;
}


int AddressBook::getLength() const {
    int len = 0;
    Person *current = head;
    while (current != nullptr) {
        len++;
        current = current->getNext();
    }
    return len;
}


Person* AddressBook::getNth(const int index) const {
    if (index < 0 || index > getLength()) return nullptr;
    Person *result = head;
    for (int i = 0; i < index - 1; i++)
        result = result->getNext();
    return result;
}


void AddressBook::updatePerson(Person *target, Person *newPerson) {
    Person *current = head;
    while (current != nullptr) {
        if (current->compare(target) == 0) {
            if (newPerson->getFirstName() != "")
                current->setFirstName(newPerson->getFirstName());
            if (newPerson->getLastName() != "")
                current->setLastName(newPerson->getLastName());
            if (newPerson->getPhone() != "")
                current->setPhone(newPerson->getPhone());
            if (newPerson->getAddress() != "")
                current->setAddress(newPerson->getAddress());
        }
        current = current->getNext();
    }
}


bool AddressBook :: isEmpty() const {
    return head == nullptr;
}


void AddressBook :: load(ifstream &file_in) {
    size_t size;
    if (file_in.is_open()) {
        int num_contacts;
        file_in.read((char*)&num_contacts, sizeof(num_contacts));
        for (int i = 0; i < num_contacts; i++) {
            string firstname;
            file_in.read((char*)&size, sizeof(size));
            firstname.resize(size);
            file_in.read((char*)&firstname[0], size);

            string lastname;
            file_in.read((char*)&size, sizeof(size));
            lastname.resize(size);
            file_in.read((char*)&lastname[0], size);

            string phone;
            file_in.read((char*)&size, sizeof(size));
            phone.resize(size);
            file_in.read((char*)&phone[0], size);

            string address;
            file_in.read((char*)&size, sizeof(size));
            address.resize(size);
            file_in.read((char*)&address[0], size);

            addPerson(firstname, lastname, phone, address);
        }
        file_in.close();
    } else cerr << "Could not read from file .AddressBook.dat\n";
}


void AddressBook :: save(ofstream &file_out) {
    size_t size;
    if (file_out.is_open()) {
        int num_contacts = getLength();
        file_out.write((char*)&num_contacts, sizeof(num_contacts));
        Person *curr = head;
        while (curr != nullptr) {
            string firstname = curr->getFirstName();
            size = firstname.size();
            file_out.write((char*)&size, sizeof(size));
            file_out.write(firstname.c_str(), size);

            string lastname = curr->getLastName();
            size = lastname.size();
            file_out.write((char*)&size, sizeof(size));
            file_out.write(lastname.c_str(), size);

            string phone = curr->getPhone();
            size = phone.size();
            file_out.write((char*)&size, sizeof(size));
            file_out.write(phone.c_str(), size);

            string address = curr->getAddress();
            size = address.size();
            file_out.write((char*)&size, sizeof(size));
            file_out.write(address.c_str(), size);

            curr = curr->getNext();
        }
    } else cerr << "Could not write to file .AddressBook.dat\n";
}


