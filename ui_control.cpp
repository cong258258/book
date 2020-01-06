#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstring>
#include "everything.h"
extern int login_stat;
void ui_control()
{
    char cmd[500];
//    char tmpcmd[30] = "su root sjtu";
//    do_it(tmpcmd);
    login_stat = 7;
    while (1)
    {
        strcpy(cmd, "");
        cin.get(cmd, 400);
        int a = do_it(cmd);
        if (cin.get() == EOF || a == 1)
            break;
    }
}