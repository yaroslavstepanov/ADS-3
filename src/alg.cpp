// Copyright 2021 NNTU-CS
#include <string>
#include "tstack.h"


int prior(char ch)
{
switch (ch)
{
case '(': return 0;
case ')': return 1;
case '+': return 2;
case '*': return 3;
case '/': return 3;
default: return -1;
}
}

std::string infx2pstfx( std::string inf) {
std::string pfx;
int i = 0;
char ch = inf[i];
char top = 0;
TStack <char> stackCh;
while (ch) {
int prioritet;
prioritet = prior(ch);
if (prior > -1) {
if ((prioritet == 0 || prioritet > prior(top) ||
stackCh.isEmpty()) && ch != ')') {
if (stackCh.isEmpty())
top = ch;
stackCh.push(ch);
} else if (ch == ')') {
while (stackCh.get() != '(') {
pfx.push_back(stackCh.get());
pfx.push_back(' ');
stackCh.pop();
}
stackCh.pop();
if (stackCh.isEmpty())
top = 0;
} else {
while (!stackCh.isEmpty() && prior(stackCh.get()) >= prioritet) {
pfx.push_back(stackCh.get());
pfx.push_back(' ');
stackCh.pop();
}
if (stackCh.isEmpty())
top = ch;
stackCh.push(ch);
}
} else {
pfx.push_back(ch);
pfx.push_back(' ');
}
ch = inf[++i];
}
while (!stackCh.isEmpty()) {
pfx.push_back(stackCh.get());
pfx.push_back(' ');
stackCh.pop();
}
pfx.erase(pfx.end() - 1, pfx.end());
return pfx;
}
int calculator(int k1, int k2, char pst)
{
    switch (pst)
    {
    case '+': return k1 + k2;
    case '-': return k1 - k2;
    case '*': return k1 * k2;
    case '/': return k1 / k2;
    default: return -1;
    }
}

int eval(std::string pst) {
     TStack<int> stack2;
    for (int i = 0; i < pst.size(); i++)
    {
        char ch = pst[i];
        int priority = prior(ch);

        if (priority == -1)
            stack2.push(ch - 48);
        else
        {
            int  k1 = stack2.get();
            stack2.pop();

            int k2 = stack2.get();
            stack2.pop();

            int res = calculator(k2, k1, ch);
            stack2.push(res);
        }

    }
    return stack2.get();
}
