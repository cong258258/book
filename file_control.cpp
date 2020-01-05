#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstring>
#include "everything.h"
extern int login_stat;
void file_control(char* filename)
{
    fstream f;
    f.open(filename);
    if(!f)
    {
        cout << "loading... No such file found!" << endl;
        f.close();
        return;
    }
    char cmd[500];
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