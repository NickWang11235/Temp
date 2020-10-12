#ifndef _TST_H_
#define _TST_H_

#include <string>
#include <vector>

struct node{
  std::pair<std::string, int>* left_item;
  std::pair<std::string, int>* right_item;
  node* left_tree;
  node* mid_tree;
  node* right_tree;
  node(){
    left_item = 0;
    right_item = 0;
    left_tree = 0;
    mid_tree = 0;
    right_tree = 0;
  }
  ~node(){
    delete left_item;
    delete right_item;
    delete left_tree;
    delete mid_tree;
    delete right_tree;
  }
};

class TST{
  node* head;
  int insert_at(std::string, node* n);
  void remove_and_replace(node* n, bool left_item);
  node* look_up_from(std::string key, node* n) const;
  void look_up_in_range(std::string l_key, std::string r_key, const node* n,
                                           std::vector<std::string>& v) const;
  bool in_range(std::string l, std::string u, std::string val) const;
public:
  TST(){head = 0;}
  int insert(std::string key);
  node* look_up(std::string key) const;
  int remove(std::string key);
  std::vector<std::string> look_up_in_range(std::string l_key, std::string r_key) const;
  ~TST(){delete head;}
};

#endif
