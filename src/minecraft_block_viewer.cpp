//
// Created by Sarathkrishnan Ramesh on 1/1/20.
//
#include "minecraft_block_viewer.h"

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
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

  GLClearError();

  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  // Background color: white
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

  {
    GLClearError();

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_CULL_FACE);

    Camera camera(glm::vec3(-3.0f, 1.8f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f), -45.0f, -20.0f);

    Shader shader("../shaders/block.shader");

    Block block;
    block.block_description();

    Texture texture_atlas("../res/cobble.jpg");
    texture_atlas.Bind(0);

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

    glBindVertexArray(0);

    IndexBuffer ib(block.indices.data(), block.get_index_size());

    Renderer renderer;

    glm::mat4 model(1.0f), animation_hover(1.0f), animation_rotate(1.0f);

    GLCheckError();

    do {
      GLClearError();
      renderer.Clear();

      glm::mat4 projection = glm::perspective(camera.GetZoom(), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
      glm::mat4 view = camera.GetViewMatrix();

      float current_time = glfwGetTime();
      animation_hover = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.15f * sin(2 * current_time), 0.0f));
      animation_rotate = glm::rotate(animation_rotate, 0.02f, glm::vec3(0.0, 1.0, 0.0));

      // Render Block
      {
        texture_atlas.Bind(0);

        shader.Bind();
        shader.SetUniformMat4f("projection", projection);
        shader.SetUniformMat4f("view", view);
        shader.SetUniformMat4f("model", animation_rotate * animation_hover * model);

        shader.SetUniform1i("u_Texture", 0);

        renderer.Draw(vao, ib, shader);
      }

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

      // Swap Buffers
      glfwSwapBuffers(window);
      glfwPollEvents();
      GLCheckError();

    } while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);
  }

  return 0;
}
