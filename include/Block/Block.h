//
// Created by Sarathkrishnan Ramesh on 1/1/20.
//
#pragma once

#include <iostream>
#include <cstring>
#include <vector>
#include <jsoncpp/json/json.h>

class Block {
 private:
  unsigned int id;
  std::string name;
 public:
  std::vector<float> vertices;
  std::vector<unsigned int> indices;

  Block();
  Block(std::string block_name, unsigned int block_id, Json::Value &root);

  unsigned int get_vertex_size();
  unsigned int get_index_size();
  void block_description();
  void update_texture(std::string block_name, unsigned int block_id, Json::Value root);
};
