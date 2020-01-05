#include <iostream>
#include <fstream>
#include "everything.h"
#include <windows.h>
using namespace std;
int login_stat = 0;
void test_user_table();
int test_commandtxt();
int main()
{
    system("chcp 65001 > nul");
    test_user_table();
    if (test_commandtxt())
    {
        char cmdname[100] = "command.txt";
        file_control(cmdname);
    }
    else
    {
        cout << "*****************using ui*****************" << endl;
        ui_control();
    }
    return 0;
}
void test_user_table()
{
    ifstream test_user_table;
    test_user_table.open("user_table.txt");
    if(!test_user_table)
        no_user_init();
    test_user_table.close();
}
int test_commandtxt()
{
    fstream f;
    f.open("command.txt");
    if (!f)
    {
        f.close();
        return 0;
    }
    else
    {
        f.close();
        return 1;
    }
}