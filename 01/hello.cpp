#include <iostream>
using namespace std;
#include <cstring>
#include "hello.h"

void hello (const char * name, int count) {
  if (count > 0){
    cout << "Hello,";
    for (int i = 0; i < count; i++) {
      cout << " " << name;
    }
    cout << "!" << endl;
  }
}

std::pair<const char *, int> parse_args (int argc, char * argv[]) {
  if  (argc < 2) return std::make_pair("world", 1);  // No argument
  else if (argc == 2) return std::make_pair(argv[1], 1);  // One argument, print once
  else if (argc == 3) { // Two arguments, check second is int
    int arglen = strlen(argv[2]);
    for (int i=0; i < arglen; i++){
      if(!isdigit(argv[2][i])){
        cerr << "error: 2nd argument must be an integral greater than zero!" << endl;
        return std::make_pair("", -1);
      }
    }
  }
  else {  // 3 or more arguments, error
    cerr << "error: Too many arguments!" << endl;
    return std::make_pair("", -1);
  }

  int count = atoi(argv[2]);
  return std::make_pair(argv[1], count);
}
