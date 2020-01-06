#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstring>
#include "everything.h"
extern int login_stat;
extern int user_total;
extern int user_del;
extern int now_select;
extern int book_total;
extern double book_sold_money;
extern double book_import_money;
fstream book_table_cnt;
fstream book_table;
class book
{
public:
    char ISBN[30];
    char name[100];
    char author[100];
    char keyword[100];
    int quantity;
    double price;
    book(const char* ISBNN, const char* namee = "", const char* authorr = "", const char* keywordd = "", int quantityy = 0, double pricee = 0.0)
    {
        strcpy(ISBN, ISBNN);
        strcpy(name, namee);
        strcpy(author, authorr);
        strcpy(keyword, keywordd);
        quantity = quantityy;
        price = pricee;
    };
    book() = default;
};
void test_auth(int needed_stat)
{
    if(login_stat < needed_stat)
        throw needed_stat;
}
int find_book(char* ISBNN)
{
    book_table.seekg(0);
    book finding;
    for(int i = 0; i < book_total; i++)
    {
        book_table.seekg(i * sizeof(book));
        book_table.read(reinterpret_cast<char*>(&finding), sizeof(book));
        if(strcmp(ISBNN, finding.ISBN) == 0)
            return i;
    }
    return -1;
}
void cmd_book_man(char* cmd)
{
    try
    {
        book_table_cnt.open("book_table_cnt.txt");
        book_table_cnt.seekg(0);
        book_table_cnt.read(reinterpret_cast<char *>(&book_total), sizeof(int));
        book_table_cnt.seekg(sizeof(int));
        book_table_cnt.read(reinterpret_cast<char *>(&book_sold_money), sizeof(double));
        book_table_cnt.seekg(sizeof(int) + sizeof(double));
        book_table_cnt.read(reinterpret_cast<char *>(&book_import_money), sizeof(double));
        book_table.open("book_table.txt");
        book_table.seekg(0);
        stringstream cmdd(cmd);
        string cmd_head = "";
        cmdd >> cmd_head;
        if (cmd_head == "select")
        {
            test_auth(3);
            char ISBNN[30];
            cmdd >> ISBNN;
            now_select = find_book(ISBNN);
            if (now_select == -1)
            {
                book *new_book = new book(ISBNN);
                book_table.seekp(0, ios::end);
                book_table.write(reinterpret_cast<char *>(new_book), sizeof(book));
                now_select = book_total;
                book_total++;
                delete new_book;
            }
        }
        else if (cmd_head == "show")
        {
            test_auth(1);
            char ISBNN[30];
            cmdd >> ISBNN;
            now_select = find_book(ISBNN);
        }
        else if (cmd_head == "modify")
        {
            test_auth(3);
            book_table.seekp(now_select * sizeof(book));
            book now_book;
            book_table.read(reinterpret_cast<char *>(&now_book), sizeof(book));
            char what_to_modify[10], after_modify[100];
            while (1)
            {
                char got = cmdd.get();
                if (got == -1)
                    break;
                cmdd.get();
                cmdd.get(what_to_modify, 9, '=');
                cmdd.get();
                if (strcmp(what_to_modify, "price") == 0)
                {
                    double price_after_modify;
                    cmdd >> price_after_modify;
                    now_book.price = price_after_modify;
                }
                else if (strcmp(what_to_modify, "ISBN") == 0)
                {
                    cmdd >> after_modify;
                    strcpy(now_book.ISBN, after_modify);
                }
                else if (strcmp(what_to_modify, "name") == 0)
                {
                    cmdd.get();
                    cmdd.get(after_modify, 100, '\"');
                    cmdd.get();
                    strcpy(now_book.name, after_modify);
                }
                else if (strcmp(what_to_modify, "author") == 0)
                {
                    cmdd.get();
                    cmdd.get(after_modify, 100, '\"');
                    cmdd.get();
                    strcpy(now_book.author, after_modify);
                }
                else if (strcmp(what_to_modify, "keyword") == 0)
                {
                    cmdd.get();
                    cmdd.get(after_modify, 100, '\"');
                    cmdd.get();
                    strcpy(now_book.keyword, after_modify);
                }
                else
                    cout << "Invalid can't modify book info" << endl;
            }
            book_table.seekg(now_select * sizeof(book));
            book_table.write(reinterpret_cast<char *>(&now_book), sizeof(book));
        }
        book_table_cnt.seekp(0);
        book_table_cnt.write(reinterpret_cast<char *>(&book_total), sizeof(int));
        book_table_cnt.seekp(sizeof(int));
        book_table_cnt.write(reinterpret_cast<char *>(&book_sold_money), sizeof(double));
        book_table_cnt.seekp(sizeof(int) + sizeof(double));
        book_table_cnt.write(reinterpret_cast<char *>(&book_import_money), sizeof(double));
        book_table.close();
        book_table_cnt.close();
    }
    catch(int ex_needed_auth)
    {
        cout << "Invalid book info no auth, needed auth" << ex_needed_auth << endl;
    }
}