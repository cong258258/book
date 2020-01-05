#ifndef BOOK_BOOK_H
#define BOOK_BOOK_H
#include <cstring>
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
class Book
{
    int no;
    char name[20];
    int borrowed;
public:
    Book(const char *s = "", int total_no = 0) ;
    void borrow(int readerNo);
    void Return();
    void display() const;
};
Book::Book(const char *s,  int totalNo)
{
    no = totalNo;
    borrowed = 0;
    strcpy(name,s);
}
void Book::borrow(int readerNo)
{
    if (borrowed != 0)
        cout << "本书已被借，不能重复借\n";
    else borrowed = readerNo;
}
void Book::Return()
{
    if (borrowed == 0)
        cout << "本书没有被借，不能还\n";
    else
        borrowed = 0;
}
void Book::display() const
{
    cout << setw(10) << no << setw(20) << name << setw(10) << borrowed << endl;
}
#endif
