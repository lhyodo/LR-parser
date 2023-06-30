#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>



int main() {

  //Declarations
  std::string str{};
  std::cin >> str;
  std::vector<char> stk;
  std::unordered_set<char> terminal{'=', '+', '-', '*', '/', 'a', 'b', '(', ')', '$'};
  std::unordered_set<char> nonterm{'S', 'E', 'P', 'T', 'Q', 'F'};


  //Push $ onto the stack
  stk.push_back('$');

  //Push (Starting Nonterminal) on to the stack
  stk.push_back('S');

  auto token = str.begin();
  std::cout << "stack\t\t\t\tinput\n-------------------------------------------\n";

  //While stack not empty do
  while(!stk.empty()) {

    //display
    for (auto i : stk) {
      std::cout << i;
    }
    std::cout << "\t\t\t\t";
    for (auto i = token; i != str.end(); ++i) {
      std::cout << *i;
    }
    std::cout << '\n';



    //let top = top of stack symbol and token = incoming token
    char top = stk.back();
    stk.pop_back();
    
    if (terminal.contains(top)) {
      if (top == *token) {
        ++token;
        continue;
      }
    } else if (nonterm.contains(top)) {
      switch (top) {
        case 'S': {
          switch(*token) {
            case 'a': case 'b': case '(': stk.push_back('E'); stk.push_back('='); stk.push_back('F'); break;
            default: std::cout << "\nrejected.\n\n"; return 0;
          }
        } break;
        case 'E': {
          switch (*token) {
            case 'a': case 'b': case '(': stk.push_back('P'); stk.push_back('T'); break;
            default: std::cout << "\nrejected.\n\n"; return 0;
          }
        } break;
        case 'P': {
          switch (*token) {
            case '+': stk.push_back('P'); stk.push_back('T'); stk.push_back('+'); break;
            case '-': stk.push_back('P'); stk.push_back('T'); stk.push_back('-'); break;
            case ')': case '$': break;
            default: std::cout << "\nrejected.\n\n"; return 0;
          }
        } break;
        case 'T': {
          switch (*token) {
            case 'a': case 'b': case '(': stk.push_back('Q'); stk.push_back('F'); break;
            default: std::cout << "\nrejected.\n\n"; return 0;
          }
        } break;
        case 'Q': {
          switch (*token) {
            case '+': case '-': case ')': case '$': break;
            case '*': stk.push_back('Q'); stk.push_back('F'); stk.push_back('*'); break;
            case '/': stk.push_back('Q'); stk.push_back('F'); stk.push_back('/'); break;
            default: std::cout << "\nrejected.\n\n"; return 0;
          }
        } break;
        case 'F': {
          switch (*token) {
            case 'a': stk.push_back('a'); break;
            case 'b': stk.push_back('b'); break;
            case '(': stk.push_back(')'); stk.push_back('E'); stk.push_back('('); break;
            default: std::cout << "\nrejected.\n\n"; return 0;
          }
        } break;
        default: std::cout << "\nrejected.\n\n"; return 0;
      }
    } else {
      std::cout << "\nrejected.\n\n";
      return 0;
    }


  }

  std::cout << "\naccepted.\n\n";

  return 0;
}