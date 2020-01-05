#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstring>
#include "everything.h"
using namespace std;
class myex
{
public:
    string what = "no type";
    myex(string s){what = s;}
};
void initialize(){throw myex("init");};
void addBook(){throw myex("add");};
void borrowBook(){throw myex("borrow");};
void returnBook(){throw myex("return");};
void displayBook(){throw myex("dis");};
extern int login_stat;
int do_it(char* cmd)
{
    stringstream cmdd(cmd);
    string cmd_head = "";
    cmdd >> cmd_head;
    if(cmd_head == "su" || cmd_head == "logout" || cmd_head == "useradd" || cmd_head == "register" || cmd_head == "delete" || cmd_head == "passwd")
        cmd_user_man(cmd);
    else if(cmd_head == "exit")
    {
        cout << "goodbye!" << endl;
        return 1;
    }
    else if(cmd_head.length() == 0)
        return 1;
    else
        cout << "Invalid cmd" << endl;
    cmdd.str("");
    cmdd.clear();
    return 0;
}