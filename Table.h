#ifndef TABLE_H
#define TABLE_H

#include <vector>
#include <iostream>
#include <fstream>
#include <string>

#include "Integer.h"
#include "Fraction.h"
#include "String.h"
#include "Formula.h"
#include "EmptySpace.h"

using std::vector;
using std::fstream;

class Table
{
    private:
        string currFileName;            //Keeps the name of the last opened file;
        fstream file;                   //File stream used to get and set information to files;
        vector<vector<Element*> > elements; //Used to store elements from different type(inheriting the class Element);

    public:
        Table();
        Table(const Table& other);
        Table& operator=(const Table& rhs);
        ~Table();

        bool open(const string& fileName);  //Copies the information from the said file to the elements array;
        void close();                //Deletes all information from the array elements;
        bool save();                //Saves the information of the array elements in the last opened file;
        bool saveAs(const string& newPath);  //Saves the information of the array elements in the said file path;

        void print() const;                             //Prints the array elements as full table;
        bool edit(const int row, const int col, string newValue);  //Edits the value of the cell at the said position,
                                                                   //if the cell doesn't exist it is created;

    private:
        void copy(const Table& other);
        void del();                 //Deletes the dynamic allocated memory;

        Element* factory(const string str) const;  //Returns object of the appropriate class as pointer of Element;

        void printSpaces(const int num) const;
        bool isNumber(const string& str) const; //Checks if the string contains only digits, '+', '-' or '.';
        bool isStrOnlySpaces(const string& str) const; //Checks if the string contains only spaces;
};

#endif // TABLE_H
