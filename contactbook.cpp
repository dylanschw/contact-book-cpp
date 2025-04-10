#include "ContactBook.h"

ContactBook::ContactBook() : curr_size(0) {
    for (int i = 0; i < MAX_SIZE; ++i) {
        contacts[i] = nullptr;
    }
}

ContactBook::ContactBook(const ContactBook& other) : curr_size(other.curr_size) {
    for (unsigned int i = 0; i < curr_size; ++i) {
        contacts[i] = other.contacts[i];  // Store the same pointers instead of deep copying
    }
}

ContactBook::~ContactBook() {
    // Do NOT delete pointers here since ContactBook does not own the Contact objects
}

ContactBook& ContactBook::operator=(const ContactBook& other) {
    if (this == &other) return *this;

    curr_size = other.curr_size;
    for (unsigned int i = 0; i < curr_size; ++i) {
        contacts[i] = other.contacts[i];  // Store the same pointers instead of deep copying
    }

    return *this;
}

// Returns a pointer to a contact if found, otherwise nullptr
Contact* ContactBook::Find(const std::string& query) const {
    for (unsigned int i = 0; i < curr_size; ++i) {
        if (contacts[i]->getName() == query || contacts[i]->getNumber() == query) {
            return contacts[i];
        }
    }
    return nullptr;
}

// Adds a contact by storing its pointer
void ContactBook::Add(Contact& contact) {
    if (curr_size < MAX_SIZE) {
        contacts[curr_size++] = &contact;
    }
}

// Adds multiple contacts while preserving their order
void ContactBook::AddContacts(const std::vector<Contact*>& contactsList) {
    for (Contact* contact : contactsList) {
        if (curr_size < MAX_SIZE) {
            contacts[curr_size++] = contact;
        }
    }
}

// Removes a contact and shifts elements to maintain order
void ContactBook::Remove(Contact& contact) {
    for (unsigned int i = 0; i < curr_size; ++i) {
        if (contacts[i] == &contact) {
            for (unsigned int j = i; j < curr_size - 1; ++j) {
                contacts[j] = contacts[j + 1];
            }
            curr_size--;
            return;
        }
    }
}

// Displays all contacts in the ContactBook
void ContactBook::Display() const {
    for (unsigned int i = 0; i < curr_size; ++i) {
        contacts[i]->Display();
    }
}

// Sorts contacts alphabetically by name
void ContactBook::Alphabetize() {
    std::sort(contacts, contacts + curr_size, [](Contact* a, Contact* b) {
        return a->getName() < b->getName();
    });
}

// Operator Overloads
ContactBook& ContactBook::operator+=(Contact& contact) {
    Add(contact);
    return *this;
}

ContactBook& ContactBook::operator+=(const ContactBook& other) {
    for (unsigned int i = 0; i < other.curr_size; ++i) {
        Add(*other.contacts[i]);
    }
    return *this;
}

ContactBook ContactBook::operator+(const ContactBook& other) const {
    ContactBook newBook(*this);
    newBook += other;
    return newBook;
}

ContactBook& ContactBook::operator-=(Contact& contact) {
    Remove(contact);
    return *this;
}

ContactBook& ContactBook::operator-=(const ContactBook& other) {
    for (unsigned int i = 0; i < other.curr_size; ++i) {
        Remove(*other.contacts[i]);
    }
    return *this;
}

ContactBook ContactBook::operator-(const ContactBook& other) const {
    ContactBook newBook(*this);
    newBook -= other;
    return newBook;
}

// Checks if two ContactBooks contain the same contacts (order does not matter)
bool ContactBook::operator==(const ContactBook& other) const {
    if (curr_size != other.curr_size) return false;

    std::vector<std::string> thisContacts, otherContacts;
    for (unsigned int i = 0; i < curr_size; ++i) {
        thisContacts.push_back(contacts[i]->getName() + contacts[i]->getNumber());
        otherContacts.push_back(other.contacts[i]->getName() + other.contacts[i]->getNumber());
    }

    std::sort(thisContacts.begin(), thisContacts.end());
    std::sort(otherContacts.begin(), otherContacts.end());

    return thisContacts == otherContacts;
}

// Checks if two ContactBooks are different
bool ContactBook::operator!=(const ContactBook& other) const {
    return !(*this == other);
}
