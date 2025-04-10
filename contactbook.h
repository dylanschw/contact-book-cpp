#ifndef CONTACTBOOK_H
#define CONTACTBOOK_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class Contact {
private:
    std::string name;
    std::string number;

public:
    Contact(std::string name, std::string number) : name(name), number(number) {}

    std::string getName() const { return name; }
    std::string getNumber() const { return number; }

    void Display() const {
        std::cout << name << ", " << number << std::endl;
    }
};

class ContactBook {
private:
    static const int MAX_SIZE = 100;
    Contact* contacts[MAX_SIZE];
    unsigned int curr_size;

public:
    ContactBook();
    ContactBook(const ContactBook& other);
    ~ContactBook();
    ContactBook& operator=(const ContactBook& other);

    Contact* Find(const std::string& query) const;
    void Add(Contact& contact);
    void AddContacts(const std::vector<Contact*>& contactsList);
    void Remove(Contact& contact);
    void Display() const;
    void Alphabetize();

    ContactBook& operator+=(Contact& contact);
    ContactBook& operator+=(const ContactBook& other);
    ContactBook operator+(const ContactBook& other) const;
    ContactBook& operator-=(Contact& contact);
    ContactBook& operator-=(const ContactBook& other);
    ContactBook operator-(const ContactBook& other) const;
    bool operator==(const ContactBook& other) const;
    bool operator!=(const ContactBook& other) const;
};

#endif
