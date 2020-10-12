#include "TST.h"
#include <iostream>

int TST::insert(std::string key){
  if(!head)
    head = new node();
  return insert_at(key, head);
}

int TST::insert_at(std::string key, node* n){

  if(!n->left_item && !n->right_item){
    n->left_item = new std::pair<std::string, int>(key, 1);
    return 1;
  }

  int left_comp;
  if(n->left_item){
    left_comp = key.compare(n->left_item->first);
    if(!left_comp){
      n->left_item->second++;
      return n->left_item->second;
    }
    if(left_comp < 0){
      if(!n->left_tree)
        n->left_tree = new node();
      return insert_at(key, n->left_tree);
    }
    if(!n->right_item){
      n->right_item = new std::pair<std::string, int>(key, 1);
      return 1;
    }
  }

  int right_comp;
  if(n->right_item){
    right_comp = key.compare(n->right_item->first);
    if(!right_comp){
      n->right_item->second++;
      return n->right_item->second;
    }
    if(right_comp > 0){
      if(!n->right_tree)
        n->right_tree = new node();
      return insert_at(key, n->right_tree);
    }
    if(!n->left_item){
      n->left_item = new std::pair<std::string, int>(key, 1);
      return 1;
    }
  }

  if(!n->mid_tree)
    n->mid_tree = new node();
  return insert_at(key, n->mid_tree);

}

int TST::remove(std::string key){
  node* elem = look_up(key);

  if(!elem)
    return -1;


  if(elem->left_item && elem->left_item->first == key){
    if(elem->left_item->second >= 2){
      elem->left_item->second--;
      return elem->left_item->second;
    }else{
       remove_and_replace(elem, true);
       delete elem->left_item;
       elem->left_item = 0;
       return 0;
    }
  }

  if(elem->right_item && elem->right_item->first == key){
    if(elem->right_item->second >= 2){
      elem->right_item->second--;
      return elem->right_item->second;
    }else{
       remove_and_replace(elem, false);
       delete elem->right_item;
       elem->right_item = 0;
       return 0;
    }
  }

  return -2;
}

void TST::remove_and_replace(node* n, bool left_item){

  if(left_item){
    node* path = n->left_tree ? n->left_tree : n->mid_tree;
    bool left_path = n->left_tree ? n->left_tree : n->mid_tree;
    
    if(!path){
      return;
    }
    
    if(left_path){
      n->left_item = path->right_item ? path->right_item : path->left_item;
      remove_and_replace(path, !path->right_item);

      if(!path->left_tree && !path->mid_tree && !path->right_tree && (((bool)path->left_item) != ((bool)path->right_item))){
        path->left_item = 0;
        path->right_item = 0;
        delete path;
      }
    }
  }else{
    node* path = n->right_tree ? n->right_tree : n->mid_tree;
    bool right_path = n->right_tree ? n->right_tree : n->mid_tree;
    if(!path){
      return;
    }
    if(right_path){
      n->right_item = path->left_item ? path->left_item : path->right_item;
      remove_and_replace(path, path->right_item);

      if(!path->left_tree && !path->mid_tree && !path->right_tree && (((bool)path->left_item) != ((bool)path->right_item))){
        path->left_item = 0;
        path->right_item = 0;
        delete path;
      }
    }
  }

}

node* TST::look_up(std::string key) const{
  return look_up_from(key, head);
}

node* TST::look_up_from(std::string key, node* n) const{
  if(!n)
    return 0;

  if(n->left_item){
    if(n->left_item->first == key)
      return n;
    if(key.compare(n->left_item->first) < 0)
      return look_up_from(key, n->left_tree);    
  }

  if(n->right_item){
    if(n->right_item->first == key)
      return n;
    if(key.compare(n->right_item->first) > 0)
        return look_up_from(key, n->right_tree);
  }

  return look_up_from(key, n->mid_tree);

}

std::vector<std::string> TST::look_up_in_range(std::string l_key,
                                               std::string r_key) const{
  std::vector<std::string> v;
  look_up_in_range(l_key, r_key, head, v);
  return v;
}

void TST::look_up_in_range(std::string l_key, std::string r_key, const node* n,
                                              std::vector<std::string>& v) const{
                                      
  if(!n)
    return;
  
  if(n->left_item && l_key.compare(n->left_item->first) < 0)
    look_up_in_range(l_key, r_key, n->left_tree, v);

  if(n->left_item && in_range(l_key, r_key, n->left_item->first))
    v.push_back(n->left_item->first);

  if((n->left_item && l_key.compare(n->left_item->first) > 0) ||
     (n->right_item && r_key.compare(n->right_item->first) < 0))
    look_up_in_range(l_key, r_key, n->mid_tree, v);

  if(n->right_item && in_range(l_key, r_key, n->right_item->first))
      v.push_back(n->right_item->first);

  if(n->right_item && r_key.compare(n->right_item->first) > 0)
    look_up_in_range(l_key, r_key, n->right_tree, v);

}

bool TST::in_range(std::string l, std::string u, std::string val) const{
  return val.compare(l) >= 0
      && val.compare(u) <= 0;
}
