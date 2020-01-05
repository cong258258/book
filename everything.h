#ifndef BOOK_EVERYTHING_H
#define BOOK_EVERYTHING_H
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include "book.h"
class myex;
void file_control(char* filename);
void ui_control();
int do_it(char* cmd);
void cmd_user_man(char* cmd);
void cmd_book_man(char* cmd);
void no_user_init();
#endif