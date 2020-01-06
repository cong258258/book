#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include "everything.h"
using namespace std;
extern int login_stat;
extern int user_total;
extern int user_del;
extern int now_select;
extern int book_total;
extern double book_sold_money;
extern double book_import_money;
fstream user_table_cnt;
fstream user_table;
class User
{
public:
    char id[100];
    char passwd[100];
    int stat;
    char name[100];
    User(const char* idd, const char* passwdd, const int statt = 0, const char* namee = "")
    {
        strcpy(id, idd);
        strcpy(passwd, passwdd);
        strcpy(name, namee);
        stat = statt;
    }
    User() = default;
};
void no_user_init()
{
    ofstream create_user_table;
    create_user_table.open("user_table.txt");
    create_user_table.seekp(0);
    User *default_user = new User("root", "sjtu", 7, "root");
    create_user_table.write(reinterpret_cast<char *>(default_user), sizeof(User));
    delete default_user;
    create_user_table.close();
    ofstream create_user_table_cnt;
    create_user_table_cnt.open("user_table_cnt.txt");
    user_total = 1;
    user_del = 0;
    create_user_table_cnt.seekp(0);
    create_user_table_cnt.write(reinterpret_cast<char *>(&user_total), sizeof(int));
    create_user_table_cnt.seekp(sizeof(int));
    create_user_table_cnt.write(reinterpret_cast<char *>(&user_del), sizeof(int));
    create_user_table_cnt.close();
    ofstream create_book_table_cnt;
    create_book_table_cnt.open("book_table_cnt.txt");
    now_select = -1;
    book_total = 0;
    book_sold_money = 0;
    book_import_money = 0;
    create_book_table_cnt.seekp(0);
    create_book_table_cnt.write(reinterpret_cast<char *>(&book_total), sizeof(int));
    create_user_table_cnt.seekp(sizeof(int));
    create_book_table_cnt.write(reinterpret_cast<char *>(&book_sold_money), sizeof(double));
    create_book_table_cnt.seekp(sizeof(double) + sizeof(int));
    create_book_table_cnt.write(reinterpret_cast<char *>(&book_import_money), sizeof(double));
    create_book_table_cnt.close();
    ofstream create_book_table;
    create_book_table.open("book_table.txt");
    create_book_table.close();
}
int find_user(char* idd)
{
    user_table.seekg(0);
    User finding;
    for(int i = 0; i < user_total + user_del; i++)
    {
        user_table.seekg(i * sizeof(User));
        user_table.read(reinterpret_cast<char*>(&finding), sizeof(User));
        if(strcmp(idd, finding.id) == 0 && finding.stat >= 0)
            return 1;
    }
    return 0;
}
int find_user_stat(char* idd)
{
    user_table.seekg(0);
    User finding;
    for(int i = 0; i < user_total + user_del; i++)
    {
        user_table.seekg(i * sizeof(User));
        user_table.read(reinterpret_cast<char*>(&finding), sizeof(User));
        if(strcmp(idd, finding.id) == 0 && finding.stat >= 0)
            return finding.stat;
    }
    return 0;
}
void cmd_user_man(char* cmd)
{
    user_table_cnt.open("user_table_cnt.txt");
    user_table_cnt.seekg(0);
    user_table_cnt.read(reinterpret_cast<char *>(&user_total), sizeof(int));
    user_table_cnt.seekg(sizeof(int));
    user_table_cnt.read(reinterpret_cast<char *>(&user_del), sizeof(int));
    user_table.open("user_table.txt");
    user_table.seekg(0);
    stringstream cmdd(cmd);
    char cmd_head[100] = "";
    char cmd_rest_id[100] = "";
    char cmd_rest_passwd[100] = "";
    char cmd_rest_name[100] = "";
    char cmd_rest_rubbish[100] = "";
    int cmd_rest_stat = 1;
    cmdd >> cmd_head;
    cmdd.get();
    if(strcmp(cmd_head, "useradd") == 0)
    {
        if (login_stat < 3)
            cout << "Invalid add no auth" << endl;
        else
        {
            cmdd >> cmd_rest_id >> cmd_rest_passwd >> cmd_rest_stat >> cmd_rest_name >> cmd_rest_rubbish;
            if(login_stat <= cmd_rest_stat)
                cout << "Invalid add over auth" << endl;
            else if(find_user(cmd_rest_id))
                cout << "Invalid double_add" << endl;
            else if(strlen(cmd_rest_id) == 0 || strlen(cmd_rest_name) == 0 || strlen(cmd_rest_passwd) == 0)
                cout << "Invalid too few arguments in add" << endl;
            else if(strlen(cmd_rest_rubbish))
                cout << "Invalid too many arguments in add" << endl;
            else
            {
                User *new_user = new User(cmd_rest_id, cmd_rest_passwd, cmd_rest_stat, cmd_rest_name);
                user_table.seekp(0, ios::end);
                user_table.write(reinterpret_cast<char *>(new_user), sizeof(User));
                user_total++;
                user_table_cnt.seekp(0);
                user_table_cnt.write(reinterpret_cast<char *>(&user_total), sizeof(int));
                delete new_user;
            }
        }
    }
    if(strcmp(cmd_head, "logout") == 0)
    {
        if(login_stat != 0)
            login_stat = 0;
        else
            cout << "Invalid have alreadt logged out" << endl;
    }
    if(strcmp(cmd_head, "register") == 0)
    {
        cmdd >> cmd_rest_id >> cmd_rest_passwd >> cmd_rest_name >> cmd_rest_rubbish;
        if(strlen(cmd_rest_id) == 0 || strlen(cmd_rest_name) == 0 || strlen(cmd_rest_passwd) == 0)
            cout << "Invalid too few arguments in reg" << endl;
        else if(strlen(cmd_rest_rubbish))
            cout << "Invalid too many arguments in reg" << endl;
        else if(find_user(cmd_rest_id))
            cout << "Invalid double_register" << endl;
        else
        {
            User *new_user = new User(cmd_rest_id, cmd_rest_passwd, 1, cmd_rest_name);
            user_table.seekp(0, ios::end);
            user_table.write(reinterpret_cast<char *>(new_user), sizeof(User));
            user_total++;
            user_table_cnt.seekp(0);
            user_table_cnt.write(reinterpret_cast<char *>(&user_total), sizeof(int));
            delete new_user;
        }
    }
    if(strcmp(cmd_head, "su") == 0)
    {
        cmdd >> cmd_rest_id;
        int tologin_stat = find_user_stat(cmd_rest_id);
        if (tologin_stat < login_stat)
            login_stat = tologin_stat;
        else
        {
            cmdd >> cmd_rest_passwd >> cmd_rest_rubbish;
            if (strlen(cmd_rest_id) == 0 || strlen(cmd_rest_passwd) == 0)
                cout << "Invalid too few arguments in login" << endl;
            else if (strlen(cmd_rest_rubbish))
                cout << "Invalid too many arguments in login" << endl;
            else
            {
                int login_success = 0;
                User finding;
                for (int i = 0; i < user_total + user_del; i++)
                {
                    user_table.seekg(i * sizeof(User));
                    user_table.read(reinterpret_cast<char *>(&finding), sizeof(User));
                    if (strcmp(cmd_rest_id, finding.id) == 0 && strcmp(cmd_rest_passwd, finding.passwd) == 0 &&
                        finding.stat >= 0)
                    {
                        login_success = 1;
                        break;
                    }
                }
                if (login_success == 0)
                    cout << "Invalid login" << endl;
                else
                {
                    login_stat = finding.stat;
                    //    cout << "login success" << finding.name << finding.stat << endl;
                }
            }
        }
    }
    if(strcmp(cmd_head, "delete") == 0)
    {
        if(login_stat != 7)
            cout << "Invalid delete no auth" << endl;
        else
        {
            cmdd >> cmd_rest_id;
            User finding;
            int delete_success = 0;
            for(int i = 0; i < user_total + user_del; i++)
            {
                user_table.seekg(i * sizeof(User));
                user_table.read(reinterpret_cast<char*>(&finding), sizeof(User));
                if(strcmp(cmd_rest_id, finding.id) == 0 && finding.stat >= 0)
                {
                    delete_success = 1;
                    user_del++;
                    user_total--;
                    user_table_cnt.seekp(0);
                    user_table_cnt.write(reinterpret_cast<char*>(&user_total), sizeof(int));
                    user_table_cnt.seekp(sizeof(int));
                    user_table_cnt.write(reinterpret_cast<char*>(&user_del), sizeof(int));
                    finding.stat = -1;
                    user_table.seekp(i * sizeof(User));
                    user_table.write(reinterpret_cast<char*>(&finding), sizeof(User));
                    break;
                }
            }
            if(delete_success == 0)
                cout << "Invalid find nothing to delete" << endl;
        }
    }
    if(strcmp(cmd_head, "passwd") == 0)
    {
        if (login_stat < 1)
            cout << "Invalid passwd modify no auth" << endl;
        else if (login_stat < 7)
        {
            char new_passwd[100];
            cmdd >> cmd_rest_id >> cmd_rest_passwd >> new_passwd >> cmd_rest_rubbish;
            if(strlen(cmd_rest_id) == 0 || strlen(cmd_rest_passwd) == 0 || strlen(new_passwd) == 0)
                cout << "Invalid too few arguments in passwd" << endl;
            else if(strlen(cmd_rest_rubbish))
                cout << "Invalid too many arguments in passwd" << endl;
            else
            {
                User finding;
                int modify_passwd_success = 0;
                for (int i = 0; i < user_total + user_del; i++)
                {
                    user_table.seekg(i * sizeof(User));
                    user_table.read(reinterpret_cast<char *>(&finding), sizeof(User));
                    if (strcmp(cmd_rest_id, finding.id) == 0 && strcmp(cmd_rest_passwd, finding.passwd) == 0 && finding.stat >= 0)
                    {
                        strcpy(finding.passwd, new_passwd);
                        user_table.seekp(i * sizeof(User));
                        user_table.write(reinterpret_cast<char *>(&finding), sizeof(User));
                        modify_passwd_success = 1;
                        //           cout << "modified" << finding.passwd << endl;
                        break;
                    }
                }
                if (modify_passwd_success == 0)
                    cout << "Invalid fail to modify" << endl;
            }
        }
        else if (login_stat == 7)
        {
            char new_passwd[100] = "";
            cmdd >> cmd_rest_id >> new_passwd >> cmd_rest_rubbish;
            if(strlen(cmd_rest_id) == 0 || strlen(new_passwd) == 0)
                cout << "Invalid too few arguments in passwd" << endl;
            else if(strlen(cmd_rest_rubbish))
                cout << "Invalid too many arguments in passwd" << endl;
            else
            {
                User finding;
                int modify_passwd_success = 0;
                for (int i = 0; i < user_total + user_del; i++)
                {
                    user_table.seekg(i * sizeof(User));
                    user_table.read(reinterpret_cast<char *>(&finding), sizeof(User));
                    if (strcmp(cmd_rest_id, finding.id) == 0 && finding.stat >= 0)
                    {
                        strcpy(finding.passwd, new_passwd);
                        user_table.seekp(i * sizeof(User));
                        user_table.write(reinterpret_cast<char *>(&finding), sizeof(User));
                        modify_passwd_success = 1;
                        //           cout << "modified" << finding.id << "   and    " << finding.passwd << endl;
                        break;
                    }
                }
                if (modify_passwd_success == 0)
                    cout << "Invalid fail to modify" << endl;
            }
        }
        else
            cout << "unknown" << endl;
    }
//    cout << user_total << user_del << endl << endl << endl;
//    User *finding = new User();
//    for(int i = 0; i < user_total + user_del; i++)
//    {
//        user_table.seekg(i * sizeof(User));
//        user_table.read(reinterpret_cast<char *>(finding), sizeof(User));
//        cout << finding->id << "    list    " << finding->passwd << "        " << finding->name << finding->stat << endl;
//    }
    user_table.close();
    user_table_cnt.close();
}