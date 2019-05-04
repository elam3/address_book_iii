#include "Person.h"

Person :: Person() {
    firstname = getRandFirstName();
    lastname = getRandLastName();
    phone = getRandPhone();
    address = getRandAddress();
    next = nullptr;
}


Person :: Person (string firstname, string lastname, string phone, string address) {
	this->firstname = firstname;
	this->lastname = lastname;
	this->phone = phone;
	this->address = address;
	next = nullptr;
}


Person :: ~Person() {
    next = nullptr;
}


string Person :: getFirstName() const {
    return firstname;
}


string Person :: getLastName() const {
    return lastname;
}


string Person :: getPhone() const {
    return phone;
}


string Person :: getAddress() const {
    return address;
}


Person* Person :: getNext() const {
    return next;
}


void Person :: setFirstName(const string firstname) {
    this->firstname = firstname;
}


void Person :: setLastName(const string lastname) {
    this->lastname = lastname;
}


void Person :: setPhone(const string phone) {
    this->phone = phone;
}


void Person :: setAddress(const string address) {
    this->address = address;
}


void Person :: setNext(Person *next) {
    this->next = next;
}


int Person :: compare(Person *other) {
    //Primary Sort: By Last Name
    if (this->lastname < other->lastname)
        return -1;
    else if (this->lastname > other->lastname)
        return 1;
    else {
        //assert (this->lastname == other->lastname);
        //Secondary Sort: By First Name
        if (this->firstname < other->firstname)
            return -1;
        else if (this->firstname > other->firstname)
            return 1;
        else {
            //assert (this->firstname == other->firstname);
            //Tertiary Sort: By Phone Number
            if (this->phone < other->phone)
                return -1;
            else if (this->phone > other->phone)
                return 1;
            else {
                //assert (this->phone == other->phone);
                //Quarternary Sort: By Address
                if (this->address < other->address)
                    return -1;
                else if (this->address > other->address)
                    return 1;
                else {
                    //assert (this->address == other->address);
                    return 0;
                }
            } 
        }
    }
}


string Person::toString() {
    return lastname + ", " + firstname + ", " + phone + ". " + address
        + ".";
}


ostream& operator<<(ostream& os, const Person& p) {
    os << p.lastname << ", " << p.firstname << ". " << p.phone << ". " << p.address << ".";
    return os;
}


string Person :: getRandPhone() const {
    return "(" + to_string(rand()%900+100) + ") " + to_string(rand()%900+100) + "-" + to_string(rand()%10000+1000);
}


string Person :: getRandLastName() const {
    int randomIndex = rand()%50;
    string lastNames[50] = { "English", "Hall", "Levine", "Bright",
        "Mcdaniel", "Nash", "Day", "Bullock", "Robles", "Norman", "Tate",
        "Byrd", "Chavez", "Graham", "Donovan", "Holmes", "Fisher",
        "Briggs", "Ware", "Clark", "Williams", "Fleming", "Charles",
        "Myers", "Baldwin", "Doyle", "Mcclain", "Orr", "Floyd",
        "Whitehead", "Melendez", "Callahan", "Mathis", "Randall",
        "Collier", "Valentine", "Friedman", "Jacobs", "Castaneda", "Howe",
        "Gallegos", "Reid", "Riley", "Washington", "Hendrix", "Mcmahon",
        "Pollard", "Gregory", "Goodwin", "Everett"
    };
    return lastNames[randomIndex];
}


string Person :: getRandFirstName() const {
    int randomIndex = rand()%50;
    string firstNames[50] = { "Lakenya", "Anita", "Sherita", "Ezra",
        "Margeret", "Rosena", "Meridith", "Taren", "Velma", "Audra",
        "Shara", "Madison", "Bonny", "Helen", "Farah", "Danita", "Noel",
        "Marisha", "Tatum", "Catrice", "Laree", "Sanjuana", "Fidel",
        "Sang", "Teressa", "Maris", "Breanne", "Lady", "Elia", "Kelle",
        "Brandie", "Christy", "Kathlyn", "Fiona", "Eula", "Magnolia",
        "Jerrie", "Luci", "Pearline", "Giuseppina", "Michal", "Chase",
        "Jamie", "Rozella", "Arlinda", "Karena", "Jeanetta", "Aurelio",
        "Tonda", "Crista"
    };
    return firstNames[randomIndex];
}


string Person :: getRandAddress() const {
    int randomIndex = rand()%50;
    string address[50] = {
        "8684 Olive St. Floral Park, NY 11001",
        "28 Creek Ave. Milton, MA 02186",
        "773 Westminster St. Corona, NY 11368",
        "167 S. Andover Ave. Youngstown, OH 44512",
        "7658 North Hillcrest Lane everly, MA 01915",
        "96 Glenwood Ave. Norwalk, CT 06851",
        "9508 Kingston Drive evern, MD 21144",
        "552 Sunbeam Rd. Parkville, MD 21234",
        "5 Livingston Street est New York, NJ 07093",
        "6 High Ridge St. Greer, SC 29650",
        "868 W. Surrey Ave. Horn Lake, MS 38637",
        "999 Ann Drive arpentersville, IL 60110",
        "7218 Arrowhead Street ummelstown, PA 17036",
        "7300 South Lakeview Street outhfield, MI 48076",
        "85 Creek Rd. Bridgewater, NJ 08807",
        "40 Hickory Court verett, MA 02149",
        "97 John Street hevy Chase, MD 20815",
        "9013 Kingston Ave. Wilkes Barre, PA 18702",
        "7744 Catherine Ave. Fort Lauderdale, FL 33308",
        "9280 Evergreen St. Villa Rica, GA 30180",
        "884 Canterbury Street airfax, VA 22030",
        "9714 Edgewater Rd. Silver Spring, MD 20901",
        "9598 Ashley Rd. Newark, NJ 07103",
        "234 Trout Drive ake Charles, LA 70605",
        "523 Manor Station Drive indsor, CT 06095",
        "9016 Vine St. Richmond, VA 23223",
        "8889 Rockledge St. Glen Ellyn, IL 60137",
        "46 East Glenlake Ave. Collierville, TN 38017",
        "5 S. Sherwood Rd. Toms River, NJ 08753",
        "263 2nd Dr. Anaheim, CA 92806",
        "8049 South Prairie St. Santa Clara, CA 95050",
        "1 Atlantic St. Superior, WI 54880",
        "9 Mayfield St. North Haven, CT 06473",
        "875 Smith Street enatchee, WA 98801",
        "686 Wood St. Hobart, IN 46342",
        "836 South Jefferson St. New Lenox, IL 60451",
        "472 Brown St. Cherry Hill, NJ 08003",
        "64 Inverness St. Oklahoma City, OK 73112",
        "5 Canal Ave. Kalamazoo, MI 49009",
        "758 Cherry Dr. Norcross, GA 30092",
        "7473 Hilltop Lane rankfort, KY 40601",
        "454 Livingston St. Appleton, WI 54911",
        "328C Glen Ridge Dr. Ypsilanti, MI 48197",
        "64 E. High Noon Dr. Woodhaven, NY 11421",
        "768 Courtland St. Oakland, CA 94603",
        "8427 W. Lakeshore St. Apex, NC 27502",
        "8473 Union Ave. Clermont, FL 34711",
        "424 Mayfield Street umberland, RI 02864",
        "65 W. Stonybrook Ave. Tualatin, OR 97062",
        "895 Cedar Drive ort Orange, FL 32127"
    };
    return address[randomIndex];
}


