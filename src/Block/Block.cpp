//
// Created by Sarathkrishnan Ramesh on 1/1/20.
//
#include "Block.h"
#include <utility>
#include <jsoncpp/json/json.h>

void Block::reset_block() {
  this->vertices = {
      // Front.             Normals              Texture Coordinates
      -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,
       0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.5f, 0.0f,
       0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.5f, 0.5f,
      -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.5f,
      // Back
       0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
      -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.5f, 0.0f,
      -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.5f, 0.5f,
       0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.5f,
      // Left
      -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
      -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.5f, 0.0f,
      -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.5f, 0.5f,
      -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.5f,
      // Right
       0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
       0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.5f, 0.0f,
       0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.5f, 0.5f,
       0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.5f,
      // Top
      -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
       0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.5f, 0.0f,
       0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.5f, 0.5f,
      -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.5f,
      // Bottom
      -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
       0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.5f, 0.0f,
       0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.5f, 0.5f,
      -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.5f
  };
}

Block::Block() {
  this->reset_block();

  this->indices = {
      // Front
      0, 1, 2,
      2, 3, 0,
      // Back
      4, 5, 6,
      6, 7, 4,
      // Left
      8, 9, 10,
      10, 11, 8,
      // Right
      12, 13, 14,
      14, 15, 12,
      // Top
      16, 17, 18,
      18, 19, 16,
      // Bottom
      20, 21, 22,
      22, 23, 20
  };
}

Block::Block(std::string block_name, unsigned int block_id, Json::Value &root)
    : name(std::move(block_name)), id(block_id) {

  this->vertices = {
      // Front.             Normals              Texture Coordinates
      -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,
       0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.5f, 0.0f,
       0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.5f, 0.5f,
      -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.5f,
      // Back
       0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
      -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.5f, 0.0f,
      -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.5f, 0.5f,
       0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.5f,
      // Left
      -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
      -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.5f, 0.0f,
      -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.5f, 0.5f,
      -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.5f,
      // Right
       0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
       0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.5f, 0.0f,
       0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.5f, 0.5f,
       0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.5f,
      // Top
      -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
       0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.5f, 0.0f,
       0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.5f, 0.5f,
      -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.5f,
      // Bottom
      -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
       0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.5f, 0.0f,
       0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.5f, 0.5f,
      -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.5f
  };

  update_texture(this->name, this->id, root);

  this->indices = {
      // Front
      0, 1, 2,
      2, 3, 0,
      // Back
      4, 5, 6,
      6, 7, 4,
      // Left
      8, 9, 10,
      10, 11, 8,
      // Right
      12, 13, 14,
      14, 15, 12,
      // Top
      16, 17, 18,
      18, 19, 16,
      // Bottom
      20, 21, 22,
      22, 23, 20
  };
}

void Block::block_description() {
  std::cout << "Block ID: " << this->id << " Name: " << this->name << std::endl;
}

unsigned int Block::get_vertex_size() {
  return this->vertices.size() * sizeof(float);
}

unsigned int Block::get_index_size() {
  return this->indices.size();
}

void Block::update_texture(std::string block_name, unsigned int block_id, Json::Value root){
  int face_id = 0;
  float x, y;

  this->name = std::move(block_name);
  this->id = block_id;

  int rows = root["texture_atlas"].get("rows", 1).asInt();
  int cols = root["texture_atlas"].get("columns", 1).asInt();

  auto width = 1.0f/(float)cols;
  auto height = 1.0f/(float)rows;

  for(auto face : root["blocks"][this->name]){
    x = face[0].asFloat(); y = face[1].asFloat();

    for(int i=0;i < 8*4;i+=8*4) {
      this->vertices[(face_id * 8 * 4) + i + 06] = (x * width) + 0.0f;
      this->vertices[(face_id * 8 * 4) + i + 07] = (y * height) + 0.0f;
      this->vertices[(face_id * 8 * 4) + i + 14] = (x * width) + width;
      this->vertices[(face_id * 8 * 4) + i + 15] = (y * height) + 0.0f;
      this->vertices[(face_id * 8 * 4) + i + 22] = (x * width) + width;
      this->vertices[(face_id * 8 * 4) + i + 23] = (y * height) + width;
      this->vertices[(face_id * 8 * 4) + i + 30] = (x * width) + 0.0f;
      this->vertices[(face_id * 8 * 4) + i + 31] = (y * height) + width;
    }
    face_id++;
  }
}

std::string Block::get_name() {
  return this->name;
}

void Block::set_top_face_height(float height) {
  for(int i=0;i<4;i++) {
    this->vertices[(static_cast<int>(Face::TOP) * 8 * 4) + (i * 8) + 1] = height;
  }
}

void Block::set_side_face_distance(float distance) {
  for(int i=0;i<4;i++) {
    this->vertices[(static_cast<int>(Face::RIGHT) * 8 * 4) + (i * 8)] = -distance;
    this->vertices[(static_cast<int>(Face::FRONT) * 8 * 4) + (i * 8) + 2] = distance;
    this->vertices[(static_cast<int>(Face::BACK) * 8 * 4) + (i * 8) + 2] = -distance;
    this->vertices[(static_cast<int>(Face::LEFT) * 8 * 4) + (i * 8)] = distance;
  }
}
