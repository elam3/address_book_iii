#include "AddressBook.h"

AddressBook :: AddressBook() { }


AddressBook :: ~AddressBook() { }


void AddressBook :: addPerson(string _firstname, string _lastname, string _phone, string _address) {
    addressBook.push_back(new Person(
            _firstname,
            _lastname,
            _phone,
            _address
        )
    );
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
    if (isEmpty()) 
        cout << "\t(Empty)\n";
    else {
        for (int i = 0; i < addressBook.size(); i++) {
            cout << setw(4) << i + 1 << ": "
                << *addressBook[i] << endl;
        }
    }
    cout << "==============================================\n\n";
}


bool sortByName(Person *lhs, Person *rhs) {
    return lhs->compare(rhs) < 0;
}
void AddressBook :: sort() {
    std::sort(addressBook.begin(), addressBook.end(), sortByName);
}


AddressBook* AddressBook::searchFor(const string query) const {
    AddressBook *results = new AddressBook();
    if (!addressBook.empty() && query.length() != 0) {
        int len = getLength();
        for (int i = 0; i < len; i++) {
            string personStr = addressBook[i]->toString();
            if (personStr.find(query) != string::npos)
                results->addPerson(addressBook[i]);
        }
    }
    return results;
}


string AddressBook::remove(const string query) {
	string personStr = "";
    for (vector<Person*>::iterator itr = addressBook.begin();
            itr < addressBook.end(); itr++) {
        personStr = (*itr)->toString();
        if (personStr.find(query) != string::npos) {
            addressBook.erase(itr);
            break;
        }
    }
	return personStr;
}


int AddressBook::getLength() const {
    return addressBook.size();
}


Person* AddressBook::getNth(const int index) const {
    if (index < 0 || index > getLength()) return nullptr;
    return addressBook[index-1];
}


void AddressBook::updatePerson(Person *target, Person *newPerson) {
    for (vector<Person*>::iterator itr = addressBook.begin();
            itr < addressBook.end(); itr++) {
        if ((*itr)->compare(target) == 0) {
            if (newPerson->getFirstName() != "")
                (*itr)->setFirstName(newPerson->getFirstName());
            if (newPerson->getLastName() != "")
                (*itr)->setLastName(newPerson->getLastName());
            if (newPerson->getPhone() != "")
                (*itr)->setPhone(newPerson->getPhone());
            if (newPerson->getAddress() != "")
                (*itr)->setAddress(newPerson->getAddress());
        }
    }
}


bool AddressBook :: isEmpty() const {
    return addressBook.empty();
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
        for (int i = 0; i < num_contacts; i++) {
            string firstname = addressBook[i]->getFirstName();
            size = firstname.size();
            file_out.write((char*)&size, sizeof(size));
            file_out.write(firstname.c_str(), size);

            string lastname = addressBook[i]->getLastName();
            size = lastname.size();
            file_out.write((char*)&size, sizeof(size));
            file_out.write(lastname.c_str(), size);

            string phone = addressBook[i]->getPhone();
            size = phone.size();
            file_out.write((char*)&size, sizeof(size));
            file_out.write(phone.c_str(), size);

            string address = addressBook[i]->getAddress();
            size = address.size();
            file_out.write((char*)&size, sizeof(size));
            file_out.write(address.c_str(), size);
        }
    } else cerr << "Could not write to file .AddressBook.dat\n";
}


