// Copyright 2021 NNTU-CS
#include <string>
#include "tstack.h"

int prior(char ch) {
    switch (ch) {
    case '(':
        return 0;
    case ')':
        return 1;
    case '+':
        return 2;
    case '-':
        return 2;
    case '*':
        return 3;
    case '/':
        return 3;
    default:
        return -1;
    }
}
std::string infx2pstfx(std::string inf) {
std::string pfx;
    int i = 0;
    char ch = inf[i];
    char top = 0;
    TStack <char> stackChar;
    while (ch) {
        int priority;
        priority = prior(ch);

        if (priority > -1) {
            if ((priority == 0 || priority > prior(top) ||
                stackChar.isEmpty()) && ch != ')') {
                if (stackChar.isEmpty())
                    top = ch;
                stackChar.push(ch);
            } else if (ch == ')') {
                while (stackChar.get() != '(') {
                    pfx.push_back(stackChar.get());
                    pfx.push_back(' ');
                    stackChar.pop();
                }
                stackChar.pop();
                if (stackChar.isEmpty())
                    top = 0;
            } else {
                while (!stackChar.isEmpty() &&
                       prior(stackChar.get()) >= priority) {
                    pfx.push_back(stackChar.get());
                    pfx.push_back(' ');
                    stackChar.pop();
                }
                if (stackChar.isEmpty())
                    top = ch;
                stackChar.push(ch);
            }
        } else {
            pfx.push_back(ch);
            pfx.push_back(' ');
        }

        ch = inf[++i];
    }
    while (!stackChar.isEmpty()) {
        pfx.push_back(stackChar.get());
        pfx.push_back(' ');
        stackChar.pop();
    }
    pfx.erase(pfx.end() - 1, pfx.end());
    return pfx;
}

int eval(std::string pst) {
  std::string tstr;
  TStack<int> stack2;
  for (int i = 0; i < pst.length(); i++) {
    if (pst[i] >= '0' && pst[i] <= '9') {
      tstr = pst[i];
      stack2.push(pst[i] - '0');
    } else if (pst[i] != ' ') {
      int second = stack2.get();
      stack2.pop();
      int first = stack2.get();
      stack2.pop();
      if (pst[i] == '*') stack2.push(first * second);
      else if (pst[i] == '/') stack2.push(first / second);
      else if (pst[i] == '+') stack2.push(first + second);
      else
        stack2.push(first - second);
    }
  }
  return stack2.get();
}
