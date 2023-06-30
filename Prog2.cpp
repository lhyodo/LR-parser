#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>

int reduce(std::vector<char> &s) {
  char term = s.back();
  s.pop_back();
  char st = s.back();
  s.push_back(term);

  switch(term) {
    case 'E': {
      switch(st) {
        case '0': s.push_back('1'); break;
        case '4': s.push_back('a'); break;
        default: std::cout << "\nrejected.aaaaaa\n\n"; return 0;
      }
    }break;
    case 'T': {
      switch(st) {
        case '0': case '4': s.push_back('2'); break;
        case '6': s.push_back('b'); break;
        case '7': s.push_back('c'); break;
        default: std::cout << "\nrejected.aaab\n\n"; return 0;
      }
    }break;
    case 'F': {
      switch(st) {
        case '0': case '4': case '6': case '7': s.push_back('3'); break;
        case '8': s.push_back('d'); break;
        case '9': s.push_back('e'); break;
        default: std::cout << "\nrejected.aaaada\n\n"; return 0;
      }
    }break;
    default: std::cout << "\nrejected.aaafaa\n\n"; return 0;
  }
}

int main() {

  //declaration
  std::unordered_set<char> terminals{'i', '+', '-', '*', '/', ')', '(', '$'};
  std::unordered_set<char> nonterms{'E', 'T', 'F'};
  std::vector<char> stk{'0'};
  std::string str{};
  std::cin >> str;
  char state{'0'};
  auto it = str.begin();

  for (auto i = str.begin(); i != str.end(); ++i) {
    if (terminals.contains(*i) != true) {
      std::cout << "\ninvalid character entered. rejected.\n\n"; return 0;
      return 0;
    }
  }

  std::cout << "stack\t\t\t\tinput\n-------------------------------------------\n";
  std::vector<char> acc{'0', 'E', '1'}; // when the stack is equal to this vector, the string is accepted.
  while (stk != acc) {
    for (auto i : stk) {
      std::cout << i;
    }
    std::cout << "\t\t\t\t";
    for (auto i = it; i != str.end(); ++i) {
      std::cout << *i;
    }
    std::cout << '\n';

    switch(stk.back()) {
      case '0': case '4': case '6': case '7': case '8': case '9': {
        switch (*it) {
          case 'i': stk.push_back(*it++); stk.push_back('5'); break; //S5
          case '(': stk.push_back(*it++); stk.push_back('4'); break; //S4
          default: std::cout << "\nrejected.\n\n"; return 0;
        }
      }break;
      
      case '1': {
        switch (*it) {
          case '+': stk.push_back(*it++); stk.push_back('6'); break; //S6
          case '-': stk.push_back(*it++); stk.push_back('7'); break; //S7
          default: std::cout << "\nrejected.\n\n"; return 0;
        }
      }break;

      case '2': {
        switch (*it) {
          case '*': stk.push_back(*it++); stk.push_back('8'); break; //S8
          case '/': stk.push_back(*it++); stk.push_back('9'); break; //S9
          case '+': case '-': case ')': case '$': stk.pop_back(); stk.pop_back(); stk.push_back('E'); reduce(stk); break; //R3
          default: std::cout << "\nrejected.\n\n"; return 0;
        }
        
      }break;

      case '3': {
        switch(*it) {
          case '+': case '-': case '*': case '/': case ')': case '$': stk.pop_back(); stk.pop_back(); stk.push_back('T'); reduce(stk); break; //R6
          default: std::cout << "\nrejected.\n\n"; return 0;
        }
      }break;
      
      case '5': {
        switch(*it) {
          case '+': case '-': case '*': case '/': case ')': case '$': stk.pop_back(); stk.pop_back(); stk.push_back('F'); reduce(stk); break; //R8
          default: std::cout << "\nrejected.\n\n"; return 0;
        }
      }break;

      case 'a': {
        switch(*it) {
          case '+': stk.push_back(*it++); stk.push_back('6'); break; //S6
          case '-': stk.push_back(*it++); stk.push_back('7'); break; //S7
          case ')': stk.push_back(*it++); stk.push_back('f'); break; //S15
          default: std::cout << "\nrejected.\n\n"; return 0;
        }
      }break;

      case 'b': {
        switch(*it) {
          case '*': stk.push_back(*it++); stk.push_back('8'); break; //S8
          case '/': stk.push_back(*it++); stk.push_back('9'); break; //S9
          case '+': case '-': case ')': case '$': stk.pop_back(); stk.pop_back(); stk.pop_back(); stk.pop_back(); break; //R1
          default: std::cout << "\nrejected.\n\n"; return 0;

        }
      }break;

      case 'c': {
        switch(*it) {
          case '*': stk.push_back(*it++); stk.push_back('8'); break; //S8
          case '/': stk.push_back(*it++); stk.push_back('9'); break; //S9
          case '+': case '-': case ')': case '$': stk.pop_back(); stk.pop_back(); stk.pop_back(); stk.pop_back(); break; //R2
          default: std::cout << "\nrejected.\n\n"; return 0;
        }
      }break;

      case 'd': {
        switch(*it) {
          case '+': case '-': case '*': case '/': case ')': case '$': stk.pop_back(); stk.pop_back(); stk.pop_back(); stk.pop_back(); break; //R4
          default: std::cout << "\nrejected.\n\n"; return 0;
        }
      }break;

      case 'e': {
        switch(*it) {
          case '+': case '-': case '*': case '/': case ')': case '$': stk.pop_back(); stk.pop_back(); stk.pop_back(); stk.pop_back(); break;
          default: std::cout << "\nrejected.\n\n"; return 0;
        }
      }break;

      case 'f': {
        switch(*it) {
          case '+': case '-': case '*': case '/': case ')': case '$': stk.pop_back(); stk.pop_back(); stk.pop_back(); stk.pop_back(); stk.pop_back(); stk.pop_back(); stk.push_back('F'); reduce(stk); break;
          default: std::cout << "\nrejected.\n\n"; return 0;
        }
      }break;

      default: std::cout << "\nrejected.\n\n"; return 0;

    }
  }

  for (auto i : stk) {
      std::cout << i;
  }
    std::cout << "\t\t\t\t";
    for (auto i = it; i != str.end(); ++i) {
      std::cout << *i;
    }
    std::cout << '\n';

  std::cout << "\naccepted.\n\n";

  return 0;
}