#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Renderer/Shader.h"
#include "Renderer/Buffer.h"
#include "Renderer/VertexArray.h"

#include "lib/stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

// temp struct
enum class Camera_Movement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void process_input(GLFWwindow* window);
void process_keyboard(Camera_Movement direction, float delta_time);
glm::mat4 look_at(glm::vec3 eye, glm::vec3 target, glm::vec3 up);

// settings
// const unsigned int SCR_WIDTH = 960;
// const unsigned int SCR_HEIGHT = 540;
const unsigned int SCR_WIDTH  = 3000;
const unsigned int SCR_HEIGHT = 2000;

// TODO: a camera sturct would probably be usefule here
// camera globals
glm::vec3 camera_pos     = glm::vec3(0.0f, -10.0f, 0.0f);
glm::vec3 camera_forward = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 camera_up      = glm::vec3(0.0f, 0.0f, 1.0f);
glm::vec3 camera_right   = glm::vec3(1.0f, 0.0f, 0.0f);

// timing
float delta_time = 0.0f;
float last_frame = 0.0f;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "opengl-renderer", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    //glEnable(GL_CULL_FACE);
    //glFrontFace(GL_CCW);
    glEnable(GL_DEPTH_TEST);

    Shader shader("assets/shaders/basic_3d_vertex_shader.glsl", "assets/shaders/basic_3d_fragment_shader.glsl");
    /*
    float vertices[] = {
        -0.5f, -0.5f,  0.0f,
        -0.5f,  0.5f,  0.0f,
        0.5f, -0.5f,  0.0f,
        0.5f,  0.5f,  0.0f
    };
    */

    float textured_cube_vertices[] = {
         // positions          // colors           // texture coords
         0.5f, -0.5f,  0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // bottom right
         0.5f,  0.5f,  0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // top right
        -0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // top left
        -0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,   // bottom left

         0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,   // bottom right (from front) 
        -0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom left  (from front)
        -0.5f,  0.5f, -0.5f,   0.0f, 0.0f, 1.0f,   1.0f, 1.0f,   // top left     (from front)
         0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top right    (from front)
    };

    unsigned int textured_cube_indices[] = {
        // front face
        0, 1, 3,
        3, 1, 2,
        // right face
        1, 0, 4,
        1, 4, 7,
        // back face
        5, 6, 4,
        4, 6, 7,
        // left face
        6, 5, 3,
        6, 3, 2,
        // top face
        6, 2, 1,
        6, 1, 7,
        // bottom face
        3, 5, 4,
        3, 4, 0
    };

    glm::vec3 cube_positions[] = {
        glm::vec3(0.0f, 0.0f, 0.0f),
        //glm::vec3(3.0f, 0.0f, 0.0f),
        //glm::vec3(-3.0f, 0.0f, 0.0f),
        //glm::vec3(0.0f, 3.0f, 0.0f),
        //glm::vec3(0.0f, -3.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 3.0f)
    };

    Vertex_Array vao;
    Vertex_Buffer vbo(textured_cube_vertices, sizeof(textured_cube_vertices));
    Index_Buffer ibo(textured_cube_indices, sizeof(textured_cube_indices));
    vao.set_vertex_buffer(&vbo);
    vao.set_index_buffer(&ibo);

    vao.unbind();

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // load texture(s)
    int width, height, number_of_channels;
    unsigned char* data = stbi_load("assets/textures/container.jpg", &width, &height, &number_of_channels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "ERROR::STB_IMAGE::IMAGE_IS_NULL\n";
    }

    stbi_image_free(data);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {

        float current_frame = glfwGetTime();
        delta_time = current_frame - last_frame;
        last_frame = current_frame;

        // input
        // -----
        process_input(window);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.bind();

        float fov = 45.0f;
        glm::mat4 projection_matrix = glm::perspective(glm::radians(fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view_matrix = look_at(camera_pos, camera_pos + camera_forward, camera_up);
        shader.set_mat4("projection", projection_matrix);
        shader.set_mat4("view", view_matrix);

        glBindTexture(GL_TEXTURE_2D, texture);
        vao.bind();

        for (unsigned int i = 0; i < 2; i++)
        {
            glm::mat4 world_matrix = glm::mat4(1.0f);
            world_matrix = glm::translate(world_matrix, cube_positions[i]);
            float angle = 180.0f * sin(glfwGetTime());
            world_matrix = glm::rotate(world_matrix, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
            shader.set_mat4("world", world_matrix);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void*)0);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void process_input(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        process_keyboard(Camera_Movement::FORWARD, delta_time);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        process_keyboard(Camera_Movement::BACKWARD, delta_time);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        process_keyboard(Camera_Movement::LEFT, delta_time);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        process_keyboard(Camera_Movement::RIGHT, delta_time);

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void process_keyboard(Camera_Movement direction, float delta_time)
{
    float movement_speed = 5.0f;
    float velocity = movement_speed * delta_time;
    if (direction == Camera_Movement::FORWARD)
        camera_pos += camera_forward * velocity;
    if (direction == Camera_Movement::BACKWARD)
        camera_pos -= camera_forward * velocity;
    if (direction == Camera_Movement::LEFT)
        camera_pos -= camera_right * velocity;
    if (direction == Camera_Movement::RIGHT)
        camera_pos += camera_right * velocity;
}

glm::mat4 look_at(glm::vec3 eye, glm::vec3 target, glm::vec3 up_dir)
{
    glm::vec3 forward = glm::normalize(target - eye);
    glm::vec3 right   = glm::normalize(glm::cross(forward, up_dir));
    glm::vec3 up      = glm::cross(right, forward);

    glm::mat4 view_matrix = glm::mat4(1.0f);
    view_matrix[0][0] = right.x;
    view_matrix[1][0] = right.y;
    view_matrix[2][0] = right.z;
    view_matrix[0][1] = up.x;
    view_matrix[1][1] = up.y;
    view_matrix[2][1] = up.z;
    view_matrix[0][2] = -forward.x;
    view_matrix[1][2] = -forward.y;
    view_matrix[2][2] = -forward.z;
    view_matrix[3][0] = -glm::dot(right, eye);
    view_matrix[3][1] = -glm::dot(up, eye);
    view_matrix[3][2] =  glm::dot(forward, eye);
    return view_matrix;
}
