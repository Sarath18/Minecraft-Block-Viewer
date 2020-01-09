//
// Created by Sarathkrishnan Ramesh on 1/1/20.
//
#include "minecraft_block_viewer.h"
#include <algorithm>
int main() {
  std::cout << "Welcome to Minecraft Block Viewer" << std::endl;

  glewExperimental = true;

  // Initialize GLFW
  if(!glfwInit()) {
    std::cout << stderr << "Failed to initialize GLFW.\n";
    getchar();
    return -1;
  }

  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Create Window
  GLFWwindow *window;
  window = glfwCreateWindow(WIDTH, HEIGHT, "Minecraft Block Viewer", nullptr, nullptr);
  if(window == nullptr) {
    std::cout << stderr << "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible.\n";
    getchar();
    glfwTerminate();
    return -1;
  }

  glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);
  glfwMakeContextCurrent(window);

  // Initialize GLEW
  if (glewInit() != GLEW_OK) {
    std::cout << stderr << "Failed to initialize GLEW\n";
    return -1;
  }

  // Peripheral Input Configuration
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  // Set background color
  glClearColor(0.2f, 0.7f, 1.0f, 1.0f);

  GLClearError();

  {
    GLClearError();

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_CULL_FACE);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Initialize Camera
    Camera camera(glm::vec3(-3.0f, 1.5f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f), -45.0f, -20.0f);

    // Initialize Shader
    Shader shader("../shaders/block.shader");

    // Read block information from file
    Json::Reader reader;
    Json::Value root;
    std::string filename = "block_info.json";
    std::ifstream ifs("../res/" + filename);
    bool parsing_successful = reader.parse(ifs, root);
    if(!parsing_successful)  {
      std::cout << "Failed to parse " << filename << std::endl;
      glfwTerminate();
      return -1;
    }
    ifs.close();

    Json::Value specular_root;
    filename = "block_specular_info.json";
    ifs.open("../res/" + filename);
    parsing_successful = reader.parse(ifs, specular_root);
    if(!parsing_successful) {
      std::cout << "Failed to parse " << filename << std::endl;
      glfwTerminate();
      return -1;
    }

    std::vector<std::string> block_list;
    for(auto data: root["blocks"].getMemberNames()) {
      block_list.push_back(data);
    }

    std::string first_block = "beacon";
    unsigned int block_id;
    auto itr = std::find(block_list.begin(), block_list.end(), first_block);
    if ( itr != block_list.end()) {
      block_id = itr - block_list.begin();
    } else {
      block_id = 0;
      first_block = block_list.front();
    }

    // Create a block
    Block block(first_block, block_id, root);
    block.block_description();

    // Load Texture Atlas
    Texture texture_atlas("../res/minecraft_texture_atlas.png");
    texture_atlas.Bind(0);

    Texture specular_atlas("../res/specular_texture_atlas.png");
    specular_atlas.Bind(1);

    Texture break_atlas("../res/break_texture.png");

    std::vector<float> specular_texture_coordinates = {
        0.00f, 0.00f,
        0.25f, 0.00f,
        0.25f, 0.25f,
        0.00f, 0.25f,

        0.00f, 0.00f,
        0.25f, 0.00f,
        0.25f, 0.25f,
        0.00f, 0.25f,

        0.00f, 0.00f,
        0.25f, 0.00f,
        0.25f, 0.25f,
        0.00f, 0.25f,

        0.00f, 0.00f,
        0.25f, 0.00f,
        0.25f, 0.25f,
        0.00f, 0.25f,

        0.00f, 0.00f,
        0.25f, 0.00f,
        0.25f, 0.25f,
        0.00f, 0.25f,

        0.00f, 0.00f,
        0.25f, 0.00f,
        0.25f, 0.25f,
        0.00f, 0.25f
    };

    std::vector<float> break_texture_coordinates = {
        0.0f, 0.0f,
        0.1f, 0.0f,
        0.1f, 1.0f,
        0.0f, 1.0f,

        0.0f, 0.0f,
        0.1f, 0.0f,
        0.1f, 1.0f,
        0.0f, 1.0f,

        0.0f, 0.0f,
        0.1f, 0.0f,
        0.1f, 1.0f,
        0.0f, 1.0f,

        0.0f, 0.0f,
        0.1f, 0.0f,
        0.1f, 1.0f,
        0.0f, 1.0f,

        0.0f, 0.0f,
        0.1f, 0.0f,
        0.1f, 1.0f,
        0.0f, 1.0f,

        0.0f, 0.0f,
        0.1f, 0.0f,
        0.1f, 1.0f,
        0.0f, 1.0f
    };

    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    VertexBuffer vb(block.vertices.data(), block.get_vertex_size());
    vb.Bind();

    // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // Normal
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Texture
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    VertexBuffer svb(specular_texture_coordinates.data(), 2 * 6 * 4 * sizeof(float));
    svb.Bind();

    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(3);

    VertexBuffer bvb(break_texture_coordinates.data(), 2 * 6 * 4 * sizeof(float));
    bvb.Bind();

    glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(4);

    glBindVertexArray(0);

    IndexBuffer ib(block.indices.data(), block.get_index_size());

    Renderer renderer;

    glm::mat4 model(1.0f), animation_hover(1.0f), animation_rotate(1.0f);

    GLCheckError();

    bool page_up_pressed = false, page_down_pressed = false, l_pressed = false, b_pressed = false;

    glm::vec3 lightPosition(-4.0f, 5.0f, 4.0f);
    bool lighting_enabled = false;
    bool block_modified = false;

    int state = 10;
    float lastTime = 0.0f;

    do {
      GLClearError();
      renderer.Clear();

      glm::mat4 projection = glm::perspective(camera.GetZoom(), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
      glm::mat4 view = camera.GetViewMatrix();

      auto current_time = static_cast<float>(glfwGetTime());
      animation_hover = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.15f * sin(2 * current_time), 0.0f));
      animation_rotate = glm::rotate(animation_rotate, 0.02f, glm::vec3(0.0, 1.0, 0.0));

      // Render Block
      {
        texture_atlas.Bind(0);
        specular_atlas.Bind(1);
        break_atlas.Bind(2);

        shader.Bind();
        shader.SetUniformMat4f("projection", projection);
        shader.SetUniformMat4f("view", view);
        shader.SetUniformMat4f("model", animation_rotate * animation_hover * model);
        shader.SetUniform1i("breakTexture", 2);

        if(state == 10)
          shader.SetUniform1i("applyBreakTexture", 0);
        else
          shader.SetUniform1i("applyBreakTexture", 1);

        if(block_list[block_id].find("leaves") != std::string::npos)
          shader.SetUniform1i("isLeaf", 1);
        else
          shader.SetUniform1i("isLeaf", 0);

        if(lighting_enabled) {
          shader.SetUniform1i("u_Texture", 0);
          shader.SetUniform1i("lightingEnabled", 0);
        } else {
          shader.SetUniform1i("lightingEnabled", 1);

          shader.SetUniform3f("viewPos", camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
          shader.SetUniform3f("light.position", lightPosition.x, lightPosition.y, lightPosition.z);

          shader.SetUniform3f("light.ambient", 0.25f, 0.25f, 0.25f);
          shader.SetUniform3f("light.diffuse", 0.9f, 0.9f, 0.9f);

          shader.SetUniform1i("material.diffuse", 0);

          if(update_specular_texture(specular_texture_coordinates, specular_root, block_list[block_id])) {
            glBindVertexArray(vao);
            svb.Bind();
            svb.UpdateData(specular_texture_coordinates.data(), 2 * 4 * 6 * sizeof(float));
            glBindVertexArray(0);
            shader.SetUniform1i("hasSpecularTexture", 1);
            shader.SetUniform3f("light.specular", 1.0f, 1.0f, 1.0f);
            shader.SetUniform1i("material.specular", 1);
            shader.SetUniform1f("material.shininess", 64.0f);
          }

          else {
            shader.SetUniform1i("hasSpecularTexture", 0);
            shader.SetUniform3f("light.specular", 0.5f, 0.5f, 0.5f);
            shader.SetUniform1i("material.specular", 0);
            shader.SetUniform1f("material.shininess", 2.0f);
          }

        }
        renderer.Draw(vao, ib, shader);
      }

      // Rotate block
      if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        model = glm::rotate(model, -0.05f, glm::vec3(0, 1.0f, 0.0f));
      }

      if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        model = glm::rotate(model, 0.05f, glm::vec3(0, 1.0f, 0.0f));
      }

      if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        model = glm::rotate(model, -0.05f, glm::vec3(1.0f, 0.0f, 0.0f));
      }

      if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        model = glm::rotate(model, 0.05f, glm::vec3(1.0f, 0.0f, 0.0f));
      }

      // Change block
      if(glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS) {
        if(!page_up_pressed) {
          state = 10;
          page_up_pressed = true;
          block_id = (block_id + 1) % block_list.size();
          block.block_description();

          if(block_modified) {
            block.reset_block();
            block_modified = false;
          }

          if (block_list[block_id] == "enchanting_table") {
            block.set_top_face_height(0.25f);
            block_modified = true;
          }
          if (block_list[block_id] == "cactus") {
            block.set_side_face_distance(0.43f);
            block_modified = true;
          }
          if (block_list[block_id] == "cake") {
            block.set_side_face_distance(0.43f);
            block.set_top_face_height(0.0f);
            block_modified = true;
          }
          if (block_list[block_id] == "endframe") {
            block.set_top_face_height(0.3f);
            block_modified = true;
          }
          if (block_list[block_id] == "grass_path") {
            block.set_top_face_height(0.43f);
            block_modified = true;
          }

          if (is_block_translucent(block_list[block_id])) {
            glDisable(GL_DEPTH_TEST);
            glDisable(GL_CULL_FACE);
          } else {
            glEnable(GL_DEPTH_TEST);
            glEnable(GL_CULL_FACE);
          }

          block.update_texture(block_list[block_id], block_id, root);

          glBindVertexArray(vao);
          vb.Bind();
          vb.UpdateData(block.vertices.data(), block.get_vertex_size());
          glBindVertexArray(0);
        }
      }

      if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
          if(!b_pressed) {
            lastTime = glfwGetTime();
            b_pressed = true;
          }

          float currentTime = glfwGetTime();
          float speed = 0.1f;
          if(currentTime - lastTime > speed) {
            lastTime += speed;
            state = (state + 1) % 11;
            if(state != 10)
              update_break_texture(break_texture_coordinates, state);

            block.update_texture(block_list[block_id], block_id, root);

            glBindVertexArray(vao);
            bvb.Bind();
            bvb.UpdateData(break_texture_coordinates.data(), break_texture_coordinates.size() * sizeof(float));
            glBindVertexArray(0);
          }
      }

      if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
        state = 10;
        b_pressed = false;
      }

      if(glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_RELEASE) {
        page_up_pressed = false;
      }

      if(glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS) {
        if(!page_down_pressed) {
          state = 10;
          page_down_pressed = true;
          block_id = (block_id + block_list.size() - 1) % block_list.size();
          block.block_description();

          if(block_modified) {
            block.reset_block();
            block_modified = false;
          }

          if (block_list[block_id] == "enchanting_table") {
            block.set_top_face_height(0.25f);
            block_modified = true;
          }
          if (block_list[block_id] == "cactus") {
            block.set_side_face_distance(0.43f);
            block_modified = true;
          }
          if (block_list[block_id] == "cake") {
            block.set_side_face_distance(0.43f);
            block.set_top_face_height(0.0f);
            block_modified = true;
          }
          if (block_list[block_id] == "endframe") {
            block.set_top_face_height(0.3f);
            block_modified = true;
          }
          if (block_list[block_id] == "grass_path") {
            block.set_top_face_height(0.43f);
            block_modified = true;
          }

          if(is_block_translucent(block_list[block_id])){
            glDisable(GL_DEPTH_TEST);
            glDisable(GL_CULL_FACE);
          } else {
            glEnable(GL_DEPTH_TEST);
            glEnable(GL_CULL_FACE);
          }
        }

        block.update_texture(block_list[block_id], block_id, root);

        glBindVertexArray(vao);
        vb.Bind();
        vb.UpdateData(block.vertices.data(), block.get_vertex_size());
        glBindVertexArray(0);
      }

      if(glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_RELEASE) {
        page_down_pressed = false;
      }

      if(glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
        if(!l_pressed) {
          lighting_enabled = !lighting_enabled;
          l_pressed = true;
        }
      }

      if(glfwGetKey(window, GLFW_KEY_L) == GLFW_RELEASE) {
        l_pressed = false;
      }

      // Swap Buffers
      glfwSwapBuffers(window);
      glfwPollEvents();
      GLCheckError();

    } while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);
  }

  glfwTerminate();
  return 0;
}

bool is_block_translucent(std::basic_string<char> &block_name) {
  return (block_name.find("glass") && block_name.find("mob_spawner") && block_name.find("slime")
      && block_name.find("leaves")) == 0;
}


bool update_specular_texture(std::vector<float> &texture_coordinates, Json::Value root, const std::string& block_name) {
  if(!root.isMember(block_name))
    return false;

  float x = root[block_name][0].asFloat();
  float y = root[block_name][1].asFloat();

  for(int i=0;i<6;i++) {
    texture_coordinates[(i * 8)] = (x * 0.25f);
    texture_coordinates[(i * 8) + 1] = (y * 0.25f);
    texture_coordinates[(i * 8) + 2] = (x * 0.25f) + 0.25f;
    texture_coordinates[(i * 8) + 3] = (y * 0.25f);
    texture_coordinates[(i * 8) + 4] = (x * 0.25f) + 0.25f;
    texture_coordinates[(i * 8) + 5] = (y * 0.25f) + 0.25f;
    texture_coordinates[(i * 8) + 6] = (x * 0.25f);
    texture_coordinates[(i * 8) + 7] = (y * 0.25f) + 0.25f;
  }
  return true;
}

bool update_break_texture(std::vector<float> &texture_coordinates, const int state) {
  for(int i=0;i<6;i++) {
    texture_coordinates[(i * 8) + 0] = (static_cast<float>(state) * 0.1f);
    texture_coordinates[(i * 8) + 2] = (static_cast<float>(state) * 0.1f) + 0.1f;
    texture_coordinates[(i * 8) + 4] = (static_cast<float>(state) * 0.1f) + 0.1f;
    texture_coordinates[(i * 8) + 6] = (static_cast<float>(state) * 0.1f);
  }
  return true;
}