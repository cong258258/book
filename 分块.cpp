#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <vector>
#include <stack>
#include <map>
#include <cmath>
#include <cctype>
#include <bitset>
#include <ctime>
 
using namespace std;
 
#define REP(i, n) for (int i = 0; i < (n); ++i)
 
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef pair<int, int> Pair;
 
const ull mod = 1e9 + 7;
const int INF = 0x7fffffff;
const int maxn = 2e6 + 10;
const int maxblock = 9000;
 
char s[maxn], c, cmd[20];
 
struct block {
    char key[maxblock + 10];
    int len;
    block* next;
    block(){key[0] = len = 0, next = NULL;}
    void insert(int pos, int n);
    void erase(int pos, int n);
    void print(int pos, int n);
    block* find(int pos, int &k);
    void split(block *u, block *&r, int k);
    void merge(block *u, block *r);
};
 
block* head;
block List;
 
int main()
{
#ifdef __AiR_H
    freopen("in.txt", "r", stdin);
#endif // __AiR_H
    int t, cur = 0, n;
    head = new block();
    scanf("%d", &t);
    while (t--) {
        scanf("%s", cmd);
        if (cmd[0] == 'M') {
            scanf("%d", &cur);
        } else if (cmd[0] == 'I') {
            scanf("%d", &n);
            for (int i = 0; i < n;) {
                c = getchar();
                if (32 <= c && c <= 126) {
                    s[i++] = c;
                }
            }
            s[n] = '\0';
            List.insert(cur, n);
        } else if (cmd[0] == 'D') {
            scanf("%d", &n);
            List.erase(cur, n);
        } else if (cmd[0] == 'G') {
            scanf("%d", &n);
            List.print(cur, n);
        } else if (cmd[0] == 'P') {
            --cur;
        } else {
            ++cur;
        }
    }
    return 0;
}
 
block* block::find(int pos, int &k)
{
    int Count = 0;
    block* t = head;
    while (t->next) {
        if (Count+t->len >= pos) {
            break;
        }
        Count += t->len;
        t = t->next;
    }
    k = pos - Count;
    return t;
}
 
void block::split(block *u, block *&r, int k)
{
    r = new block();
    r->next = u->next, u->next = r;
    strcpy(r->key, u->key+k);
    r->len = u->len - k, u->len = k;
    u->key[k] = '\0';
}
 
void block::merge(block *u, block *r)
{
    strcat(u->key, r->key), u->len += r->len;
    u->next = r->next, free(r), r = NULL;
}
 
void block::insert(int pos, int n)
{
    int k;
    block *u = find(pos, k), *r;
    if (k == u->len) {
        r = u->next;
    } else {
        split(u, r, k);
    }
    block *t = u;
    int Count = 0;
    while (n-Count >= maxblock) {
        block *now = new block();
        strncpy(now->key, s+Count, maxblock);
        now->key[maxblock] = '\0', now->len = maxblock;
        now->next = t->next, t->next = now;
        t = now, Count += maxblock;
    }
    if (n-Count) {
        block *now = new block();
        strcpy(now->key, s+Count);
        now->len = n - Count, now->next = t->next;
        t->next = now, t = now;
    }
    if (u != head && u->next != NULL && u->len <= (maxblock/2) && u->next->len <= (maxblock/2)) {
        if (t == u->next) {
            merge(u, u->next), t = u;
        } else {
            merge(u, u->next);
        }
    }
    if (t != head && t->len <= (maxblock/2) && r != NULL && r->len <= (maxblock/2)) {
        merge(t, r);
    }
}
 
void block::erase(int pos, int n)
{
    int sk, ek;
    block *st = find(pos, sk), *sr;
    block *ed = find(pos+n, ek), *er;
    split(ed, er, ek), split(st, sr, sk);
    block *t = st->next;
    while (t != er) {
        block *t_free = t;
        t = t->next;
        free(t_free);
        t_free = NULL;
    }
    st->next = er;
    if (st->len <= (maxblock/2) && er->len <= (maxblock/2)) {
        merge(st, er);
    }
}
 
void block::print(int pos, int n)
{
    int k, Count = 0;
    block *now = find(pos+1, k);
    --k;
    while (now && Count < n) {
        while (k < now->len && Count < n) {
            putchar(now->key[k]);
            ++Count, ++k;
        }
        now = now->next, k = 0;
    }
    putchar('\n');
}
