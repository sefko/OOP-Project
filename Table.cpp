#include "Table.h"

Table::Table()
{

}

Table::Table(const Table& other)
{
    copy(other);
}

Table& Table::operator=(const Table& rhs)
{
    if(this == &rhs) return *this;

    del();
    copy(rhs);

    return *this;
}

Table::~Table()
{
    del();
}

bool Table::open(const string& fileName)
{
    currFileName = fileName;

    int row = 0;
    int col = 0;
    string line;
    file.open(fileName.c_str(), fstream::out | fstream::app);
    file.close();
    file.open(fileName.c_str(), fstream::in);
    if(file.is_open())
    {
        while( std::getline(file, line))
        {
            vector<Element*> tempRow; //This is vector that presents one row;

            int lineSize = line.length();

            string value = "";      //Used to buffer different cells from the file; Value of said cell;
            for(int i = 0; i <= lineSize; ++i) //This buffers the value char by char;
            {
                if(line[i] == ' ')
                    if(value.find('\"') == string::npos)
                        continue;
                    else
                        value += line[i];

                else if(line[i] != ',' && line[i] != '\0')
                    value += line[i];
                else
                {
                    Element* tempEl;
                    if((tempEl = factory(value)) != nullptr) //If the cell value is in valid data type, it is added to the row;
                    {
                        tempRow.push_back(tempEl);
                        ++col;
                        value = "";
                    }
                    else
                    {
                        system("cls");
                        std::cerr << "Error: Row: " << row << ", Col: " << col << "; " << value << " is in unknown data type!";
                        exit(0);
                    }
                }
            }
            elements.push_back(tempRow); //The row is added to the other vector in the array;
            ++row;
            col = 0;
        }
        file.close();

        return true;
    }
    return false;

}

void Table::close()
{
    if(file.is_open())
    {
        file.close();
    }
    del();
}

bool Table::save()
{
    file.open(currFileName, fstream::out);

    if(file.is_open())
    {
        int rows = (int)elements.size();
        for(int i = 0; i < rows; ++i)
        {
            int cols = (int)elements[i].size();
            for(int j = 0; j < cols; ++j)
            {                                                        // |
                string tempValue = elements[i][j]->getStrValue();    //.\/ If the value of the cell is string it is formatted to fit the requirements;
                if((tempValue != " " && !isNumber(tempValue) && tempValue[0] != '=') || (isNumber(tempValue) && factory(tempValue) == nullptr))
                {
                    size_t checkSize = 0;
                    while(tempValue.find('\\', checkSize) != string::npos || tempValue.find('\"', checkSize) != string::npos)
                    {
                        int low;
                        if(tempValue.find('\\', checkSize) < tempValue.find('\"', checkSize))
                            low = tempValue.find('\\', checkSize);
                        else
                            low = tempValue.find('\"', checkSize);
                        checkSize = low;
                        tempValue.insert(checkSize, "\\");
                        checkSize += 2;
                    }

                    tempValue = "\"" + tempValue + "\"";
                }

                if(j != 0)
                    file << " ";

                file << tempValue;

                if(j != cols-1)
                    file << ",";
            }
            file << "\n";
        }
        file.close();
        return true;
    }
    else
    {
        file.close();
        return false;
    }
}

bool Table::saveAs(const string& newPath)
{
    string tempFileName = currFileName; //Remember the original file;
    currFileName = newPath;             //Replace the original file with the said one;

    if(save())                  //Save information in the said file;
    {
        currFileName = tempFileName;  //And then return the original file;
        return true;
    }
    else
    {
        currFileName = tempFileName;
        return false;
    }
}

void Table::print() const
{
    //Finding table maximums:

    int maxRows = (int)elements.size();
    int maxColumns = -1;
    int maxColumnsNum = 0;

    for(int i = 0; i < maxRows; ++i)
    {
        if((int)elements[i].size() > maxColumns)
        {
            maxColumns = (int)elements[i].size();
            maxColumnsNum = i;
        }
    }

    int columnsMaxChar[maxColumns];
    for(int i = 0; i < maxColumns; ++i)
    {
        columnsMaxChar[i] = elements[maxColumnsNum][i]->getStrValue().length();
    }

    for(int i = 0; i < maxRows; ++i)
    {
        int cols = (int)elements[i].size();
        for(int j = 0; j < cols; ++j)
        {
            string temp = elements[i][j]->getStrValue();
            if(temp.length() > (size_t)columnsMaxChar[j])
                columnsMaxChar[j] = temp.length();
        }
    }

    //Printing:

    for(int i = 0; i < maxRows; ++i)
    {
        std::cout << std::endl;
        int cols = (int)elements[i].size();
        for(int j = 0; j < maxColumns; ++j)
        {
            int elementSize;
            if(j == 0)
            {
                std::cout << "| ";

                if(j < cols)
                {
                    string temp = elements[i][j]->getStrValue();

                    elementSize = temp.length();
                    std::cout << temp;
                    printSpaces(columnsMaxChar[j] - elementSize);
                }
                else
                    printSpaces(columnsMaxChar[j]);
            }
            else if(j < cols)
            {
                elementSize = elements[i][j]->getStrValue().length();

                printSpaces(columnsMaxChar[j] - elementSize);

                std::cout << elements[i][j]->getStrValue();
            }
            else
            {
                printSpaces(columnsMaxChar[j]);
            }

            std::cout << " | ";
        }
    }
    std::cout << std::endl;
}

bool Table::edit(const int row, const int col, string newValue)
{
    if(row >= 1 && col >= 1)    // |
    {                           //.\/ If the new value is string it must be formatted to fit in the function factory();
        if((newValue[0] != '=' && !isNumber(newValue) && !isStrOnlySpaces(newValue)) || (isNumber(newValue) && factory(newValue) == nullptr))
        {
            size_t checkSize = 0;
            while(newValue.find('\\', checkSize) != string::npos || newValue.find('\"', checkSize) != string::npos)
            {
                int low;
                if(newValue.find('\\', checkSize) < newValue.find('\"', checkSize))
                    low = newValue.find('\\', checkSize);
                else
                    low = newValue.find('\"', checkSize);
                checkSize = low;
                newValue.insert(checkSize, "\\");
                checkSize += 2;
            }

            newValue = "\"" + newValue + "\"";
        }

        int rows = elements.size();   //If new rows or columns must be created, they are here;
        while(row > rows)
        {
            vector<Element*> temp;
            elements.push_back(temp);
            rows = elements.size();
        }

        int cols = elements[row-1].size();
        if(col > cols)
        {
            for(int i = cols; i < col; ++i)
            {
                elements[row-1].push_back(new EmptySpace());
            }
        }

        delete elements[row-1][col-1];
        elements[row-1][col-1] = factory(newValue);

        return true;
    }
    return false;
}

void Table::copy(const Table& other)
{
    int rows = other.elements.size();
    for(int i = 0; i < rows; ++i)
    {
        int cols = other.elements[i].size();
        vector<Element*> temp;

        for(int j = 0; j < cols; ++j)
        {
            temp.push_back(other.elements[i][j]);
        }

        elements.push_back(temp);
    }
}

void Table::del()
{
    int rows = elements.size();
    for(int i = 0; i < rows; ++i)
    {
        int cols = elements[i].size();
        for(int j = 0; j < cols; ++j)
        {
            delete elements[i][j];
        }
    }

    elements.clear();
}

Element* Table::factory(string str) const  //Returns, the best data type according to the string input, as Element*;
{                                          //nullptr is for invalid objects; EmptySpace() is for empty cell;
    if(str == "\"\"" || str == "" || isStrOnlySpaces(str)) return new EmptySpace();

    else if(str[0] == '\"' && str[str.length() - 1] == '\"')
    {
        str.erase(str.begin());
        str.erase(str.end()-1);

        size_t checkSize = 0;
        while(str.find('\\', checkSize) != string::npos || str.find('\"', checkSize) != string::npos)
        {
            int low;
            if(str.find('\\', checkSize) < str.find('\"', checkSize))
                low = str.find('\\', checkSize);
            else
                low = str.find('\"', checkSize);

            checkSize = low;

            if(str[checkSize - 1] == '\\')
                str.erase(str.begin() + checkSize - 1);

            ++checkSize;

        }

        return new String(str);
    }

    else if(str[0] == '=')
    {
        return new Formula(str);
    }

    else if(isNumber(str))
    {
        if((str.find('.') == string::npos))
        {
            return new Integer(stoi(str));
        }
        else if(str.find('.' != string::npos))
        {
            if(str.find('.',str.find('.') + 1) == string::npos)
                return new Fraction(stod(str));
            else
                return nullptr;
        }
        else
            return nullptr;
    }
    else
        return nullptr;
}

void Table::printSpaces(const int num) const
{
    for(int i = 0; i < num; ++i)
        std::cout << " ";
}

bool Table::isNumber(const string& str) const
{
    int pos = 0;
    while(str[pos] != '\0' && (std::isdigit(str[pos]) || str[pos] == '+' || str[pos] == '-' || str[pos] == '.'))
    {
        ++pos;
    }

    return (!str.empty()) && ((size_t)pos == str.length());
}

bool Table::isStrOnlySpaces(const string& str) const
{
    int i = 0;
    do
    {
        if(str[i] != ' ')
            return false;

        ++i;
    } while(str[i] != '\0');
    return true;
}

