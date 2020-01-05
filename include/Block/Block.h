//
// Created by Sarathkrishnan Ramesh on 1/1/20.
//
#pragma once

#include <iostream>
#include <cstring>
#include <vector>
#include <jsoncpp/json/json.h>

enum class Face {
  FRONT,
  BACK,
  RIGHT,
  LEFT,
  TOP,
  BOTTOM
};

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
  std::string get_name();
  void block_description();
  void update_texture(std::string block_name, unsigned int block_id, Json::Value root);
  void set_top_face_height(float height);
  void set_side_face_distance(float distance);
  void reset_block();
};
