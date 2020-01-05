#include <iostream>
#include <fstream>
#include "everything.h"
#include <windows.h>
using namespace std;
int login_stat = 0;
void test_user_table();
int main()
{
    system("chcp 65001 > nul");
    test_user_table();
    fstream f;
    f.open("command.txt");
    char cmd[500];
    if (f)
    {
        login_stat = 7;
        while (1)
        {
            f.get(cmd, 400);
            int a = do_it(cmd);
            if (f.get() == EOF || a == 1)
                break;
        }
        f.close();
    }
    else
    {
        f.close();
        cout << "*****************using ui*****************" << endl;
        char tmpcmd[30] = "su root sjtu";
        do_it(tmpcmd);
        while (1)
        {
            cin.get(cmd, 400);
            int a = do_it(cmd);
            if (cin.get() == EOF || a == 1)
                break;
        }
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