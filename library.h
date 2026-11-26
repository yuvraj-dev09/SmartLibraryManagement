#ifndef LIBRARY_H
#define LIBRARY_H

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

struct Book {
    int id;
    string name;
    string author;
    int quantity;
    int issued = 0;
};

struct Student {
    int id;
    string name;
    string department;
};

struct IssueRecord {
    int studentID;
    int bookID;
};

#endif