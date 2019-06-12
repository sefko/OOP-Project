#include <iostream>
#include <string>
#include "Table.h"

//Във файла с описанието са описани всички класове с главните им функции;

int main()
{
    bool loop = true;
    Table currentTable;
    string command;
    string currFile = "No file";
    bool isFileOpen = false;

    while(loop)
    {
        std::cout << "\nCurrent file: " << currFile << "\n\n"
                  << "Commands:\n\n"
                  << "> open <file name>\n"
                  << "> edit\n"
                  << "> print\n"
                  << "> save\n"
                  << "> saveAs <file name>\n"
                  << "> close\n"
                  << "> exit\n\n";

        std::cout << "Enter command: \n> ";
        std::cin.clear();
        std::cin.sync();
        getline(std::cin, command);

        string checkStr;
        if(command.substr(0,(checkStr = "open ").length()) == checkStr)
        {
            system("cls");
            if(currentTable.open(command.substr(checkStr.length(),command.length() - checkStr.length())))
            {
                std::cout << "Successfully opened file " << command.substr(checkStr.length(), command.length() - checkStr.length()) << " !\n";
                currFile = command.substr(checkStr.length(), command.length() - checkStr.length());
                isFileOpen = true;
            }
            else
                std::cout << "File " << command.substr(checkStr.length(), command.length() - checkStr.length()) << " did not open!\n";
        }
        else if(command == "edit")
        {
            system("cls");
            if(isFileOpen)
            {
                int row, col;
                string newValue;
                currentTable.print();

                std::cout << "Edit:\n"
                          << "       Row: ";
                std::cin >> row;
                std::cout << "       Col: ";
                std::cin >> col;
                std::cout << " New Value: ";
                std::cin.clear();
                std::cin.sync();
                getline(std::cin, newValue);

                system("cls");

                if(currentTable.edit(row, col, newValue))
                {
                    std::cout << "Edit successful!\n";
                }
                else
                {
                    std::cout << "Edit unsuccessful!\nMake sure that row and col are 1 or above!\n";
                }
            }
            else
                std::cout << "Please open file first!\n";
        }
        else if(command == "print")
        {
            system("cls");
            if(isFileOpen)
            {
                currentTable.print();
            }
            else
                std::cout << "Please open file first!\n";
        }
        else if(command == "close")
        {
            system("cls");

            if(isFileOpen)
            {
                currentTable.close();
                isFileOpen = false;
                currFile = "No file";
            }
            else
            {
                std::cout << "Please open file first!\n";
            }
        }
        else if(command == "save")
        {
            system("cls");
            if(isFileOpen)
            {
                if (currentTable.save())
                {
                    std::cout << "File saved!\n";
                }
                else
                    std::cout << "File did not save!";
            }
            else
            {
                std::cout << "Please open file first!\n";
            }
        }
        else if(command.substr(0,(checkStr = "saveAs ").length()) == checkStr)
        {
            system("cls");
            if(isFileOpen)
            {
                if(currentTable.saveAs(command.substr(checkStr.length(), command.length() - checkStr.length())))
                {
                    std::cout << "File saved as " << command.substr(checkStr.length(), command.length() - checkStr.length()) << " !\n";
                }
                else
                    std::cout << "File did not save!\n";
            }
            else
                std::cout << "Please open file first!\n";
        }
        else if(command == "exit")
        {
            loop = false;
        }
        else
        {
            system("cls");
            std::cout << "Unknown command!\n";
        }
    }
}


