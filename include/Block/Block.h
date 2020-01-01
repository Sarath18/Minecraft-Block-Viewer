//
// Created by Sarathkrishnan Ramesh on 1/1/20.
//
#pragma once

#include <iostream>
#include <string.h>
#include <vector>

class Block {
 private:
  int id;
  std::string name;
 public:
  std::vector<float> vertices;
  std::vector<unsigned int> indices;

  Block();

  unsigned int get_vertex_size();
  unsigned int get_index_size();
  void block_description();
};
