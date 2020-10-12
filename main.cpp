#include <iostream>
#include <string>
#include <vector>

#include "TST.h"

using namespace std;

string look_up(string key, const TST& tree){
  node* n = tree.look_up(key);
  if(!n){
    return key + " not found\n";
  }else{
    int count;
    if(n->left_item->first == key){
      count = n->left_item->second;
    }else{
      count = n->right_item->second;
    }
    return key + " found, count = " + to_string(count) + "\n";
  }
}

string insert(string key, TST& tree){
  int count = tree.insert(key);
  return key + " inserted, new count = " + to_string(count) + "\n";
}

string remove(string key, TST& tree){
  int count = tree.remove(key);
  if(!count){
    return key + " deleted\n";
  }
  if(count >= 1){
    return key + " deleted, new count = " + to_string(count) + "\n";
  }
  return "";
}

string range_search(string l, string r, const TST& tree){
  auto v = tree.look_up_in_range(l, r);
  string output = "";
  for(string str : v){
    output += str + "\n";
  }
  return output;
}

vector<string> split(string arg, char delim){
  vector<string> v;
  size_t from = 0, to = 0;
  string str = arg + delim;
  while(to < str.length()){
    to = arg.find(delim, from);
    if(to != from)
      v.push_back(arg.substr(from, to - from));
    from = to + 1;
  }
  return v;
}

int main(int argc, char const *argv[]) {

  vector<string> v;
  if(argc > 1)
    v = split(argv[1], ',');
  TST tree;

  for(string cmd : v){
    auto args = split(cmd, ' ');
    if(args[0] == "lookup"){
      cout << look_up(args[1], tree);
    }    
    if(args[0] == "insert"){
      cout << insert(args[1], tree);
    }
    if(args[0] == "delete"){
      cout << remove(args[1], tree);      
    }   
    if(args[0] == "range_search"){
      cout << range_search(args[1], args[3], tree);      
    }
  }

  return 0;
}


//"insert hello, insert hello, insert yesterday, insert yesterday, insert yesterday, lookup hello, insert goodbye, delete yesterday, insert hello, delete goodbye"