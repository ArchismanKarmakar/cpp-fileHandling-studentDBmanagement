/*
Author: Archisman Karmakar
Date Created: 25.05.2019
*/

#include <fstream>
#include <iostream>
#include <cstring>
#include <sstream>
#include <fstream>
#include <cstdlib>

using namespace std;

#define clrscr() system("cls");

class student
{
    int roll;
    char name[20];

public:
    int getroll()
    {
        return roll;
    }
    void input();
    void output();
    void modify();
};
void student::input()
{
    cout << endl;
    cout << "Enter the name: ";
    gets(name);
    cout << "Enter the roll number ";
    cin >> roll;
    cout << endl;
}
void student::output()
{
    cout << endl;
    cout << "The name is ";
    puts(name);
    cout << endl;
    cout << "the roll number is " << roll;
    cout << endl;
}
void student::modify()
{
    char nm[20];
    int r;
    cout << "Enter the new name (Enter '.' to retain old name): ";
    gets(nm);
    cout << "Enter the roll number (Enter 1 to retain old roll number): ";
    cin >> r;
    if (strcmp(nm, ".") != 0)
        strcpy(name, nm);
    if (r != 1)
        roll = r;
}
void main()
{
    clrscr();
    char cont = 'n';
    int count = 0, choice;
    student a, b, c, d, e, g;
    int pos1, pos2, i, j, flag = 0, r;
    char ch = 'n';
    ofstream fout;
    fout.open("stu.dat", ios::binary);
    do
    {
        cout << "Enter the records in 'stu.dat'  " << endl;
        a.input();
        fout.write((char *)&a, sizeof(student));
        cout << "Do you wish to enter another record?: " << endl;
        cin >> cont;
        count++;
    } while (cont == 'y');
    do
    {
        fout.close();
        cout << "MENU" << endl;
        cout << "1. Insertion \n";
        cout << "2. Deletion \n";
        cout << "3. Modification \n";
        cout << "4. Append \n";
        cout << "5. View the records \n";
        cout << "6. Searching \n";
        cout << "Enter your choice" << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            flag = 0;
            cout << "Insertion being done now...\n";
            ifstream fin;
            ofstream fout;
            fin.open("stu.dat", ios::binary);
            fout.open("temp.dat", ios::binary);
            cout << "Enter the new data " << endl;
            c.input();
            for (i = 0; i < count; i++)
            {
                fin.read((char *)&d, sizeof(student));
                if (d.getroll() < c.getroll())
                {
                    fout.write((char *)&d, sizeof(student));
                    pos2 = fin.tellg();
                }
                else
                {
                    fout.write((char *)&c, sizeof(student));
                    flag = 1;
                    break;
                }
            }
            fin.seekg(pos2);
            if (flag == 0)
                fout.write((char *)&c, sizeof(student));
            for (j = i; j < count; j++)
            {
                fin.read((char *)&g, sizeof(student));
                fout.write((char *)&g, sizeof(student));
            }
            fin.close();
            fout.close();
            remove("stu.dat");
            rename("temp.dat", "stu.dat");
            count++;
            break;
        }
        case 2:
        {
            flag = 0;
            cout << "Deletion being done...\n";
            ifstream fin;
            fin.open("stu.dat", ios::binary);
            cout << "Enter the roll number of record you wish to delete: ";
            cin >> r;
            ofstream fout;
            fout.open("temp.dat", ios::binary);
            for (i = 0; i < count; i++)
            {
                fin.read((char *)&c, sizeof(student));
                if (c.getroll() != r)
                    fout.write((char *)&c, sizeof(student));
                else
                {
                    flag = 1;
                    c.output();
                    cout << "Do you wish to delete this?: ";
                    cin >> ch;
                    if (ch != 'y')
                        fout.write((char *)&c, sizeof(student));
                }
            }
            if (flag == 0)
            {
                cout << "Record is not in the list";
            }
            fin.close();
            fout.close();
            remove("stu.dat");
            rename("temp.dat", "stu.dat");
            count--;
            break;
        }
        case 3:
        {
            flag = 0;
            cout << "Modification being done...\n"
                 << endl;
            fstream io;
            ofstream fout;
            fout.open("temp.dat", ios::binary);
            io.open("stu.dat", ios::binary | ios::in | ios::out);
            cout << "Enter the roll number you wish to modify  ";
            cin >> r;
            for (i = 0; i < count; i++)
            {
                io.read((char *)&c, sizeof(student));
                if (c.getroll() != r)
                    fout.write((char *)&c, sizeof(student));
                else
                {
                    flag = 1;
                    cout << "Record has been found! ";
                    c.output();
                    cout << "Do you wish to modify this record?: ";
                    cin >> ch;
                    if (ch == 'y')
                        c.modify();
                    fout.write((char *)&c, sizeof(student));
                }
            }
            if (flag == 0)
                cout << "Element was not found! " << endl;
            io.close();
            fout.close();
            remove("stu.dat");
            rename("temp.dat", "stu.dat");
            break;
        }
        case 4:
        {
            cout << "Appending done...\n"
                 << endl;
            ofstream fout;
            fout.open("stu.dat", ios::binary | ios::app);
            do
            {
                cout << "Enter the data you want to append" << endl;
                c.input();
                fout.write((char *)&c, sizeof(student));
                cout << "Do you wish to enter another record?: ";
                cin >> ch;
                count++;
            } while (ch == 'y');
            fout.close();
            break;
        }
        case 5:
        {
            cout << "OPENING 'stu.dat'" << endl;
            ifstream fin;
            fin.open("stu.dat", ios::binary);
            fin.seekg(0);
            for (i = 0; i < count; i++)
            {
                fin.read((char *)&c, sizeof(student));
                c.output();
            }
            break;
        }
        case 6:
        {
            flag = 0;
            cout << "Searching being done..." << endl;
            ifstream fin;
            fin.open("stu.dat", ios::binary);
            cout << "Enter the roll number you want to search: ";
            cin >> r;
            for (i = 0; i < count; i++)
            {
                fin.read((char *)&c, sizeof(student));
                if (c.getroll() == r)
                {
                    flag = 1;
                    break;
                }
            }
            if (flag == 0)
                cout << "Element was not found\n";
            else
            {
                cout << "Element has been found! \n";
                c.output();
            }
            break;
        }
        default:
            cout << "You have entered an incorrect option " << endl;
        }
        cout << "Do you wish to proceed?: " << endl;
        cin >> cont;
    } while (cont == 'y');
    fflush(stdin);
    getchar();
}
