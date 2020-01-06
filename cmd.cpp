#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstring>
#include "everything.h"
using namespace std;
extern int login_stat;
int do_it(char* cmd)
{
    stringstream cmdd(cmd);
    string cmd_head = "";
    cmdd >> cmd_head;
    if(cmd_head == "load")
    {
        if(login_stat < 7)
            cout << "Invalid load no auth" << endl;
        else
        {
            char filename[500] = "";
            char file_rubbish[500] = "";
            cmdd >> filename >> file_rubbish;
            if(strlen(file_rubbish))
                cout << "Invalid too many arguments in load" << endl;
            else if(strlen(filename) == 0)
                cout << "Invalid too few arguments in load" << endl;
            else
            {
                file_control(filename);
                login_stat = 7;
            }
        }
    }
    else if(cmd_head == "su" || cmd_head == "logout" || cmd_head == "useradd" || cmd_head == "register" || cmd_head == "delete" || cmd_head == "passwd")
        cmd_user_man(cmd);
    else if(cmd_head == "select" || cmd_head == "modify" || cmd_head == "import" || cmd_head == "show" || cmd_head == "buy")
        cmd_book_man(cmd);
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