#pragma once
#include <GL/glew.h> 
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "LightsStructs.h"


using namespace std;

class Model
{
public:
    /// <summary>
    /// ������� ����������� - ������ ������ ������, ���� ������. � ���������� ����.
    /// </summary>
    /// <param name="w"></param>
    Model(GLFWwindow* w) {
        glGenVertexArrays(1, &vao);
        window = w;
    };

    //����������. ��� ��� ������������ ������ ���, �� �� ������ �� ������.
    ~Model() {};

    //����� ��� ����������� ������.     
    /// <summary>
    /// ������ ����� ��� ���������� - ������ ���������� ������ ������.
    /// </summary>
    /// <param name="mode">������������ �������� - ����� ���������.</param>
    void render(GLuint mode = GL_TRIANGLES, int cont_point = -1);
    //����� ��� ����������� ������ c �������������� �������.     
    /// <summary>
    /// ������ ����� ��� ���������� - ������ ���������� ������ ������.
    /// </summary>
    /// <param name="mode">������������ �������� - ����� ���������.</param>
    void render(glm::mat4 MVPMatrix, GLuint mode);
    void render(glm::mat4 ProjectionMatrix, glm::mat4 ViewMatrix, glm::mat4 ModelMatrix, GLuint mode);
    void render(LightsInfo lights, Material material, glm::vec3 campos, glm::mat4 ProjectionMatrix, glm::mat4 ViewMatrix, glm::mat4 ModelMatrix, GLuint mode);
    //����� ������� ��� �������� ������������ ������� ������
    //� ���������� ���������� ����� ��������� ����� �������

    /// <summary>
    /// ����� ��� �������� ��������� ������.
    /// </summary>
    /// <param name="verteces">������ � ������������.</param>
    /// <param name="count">������ �������.</param>
    void load_coords(std::vector<glm::vec3> verteces);
    /// <summary>
    /// ����� ��� �������� ������ ������.
    /// </summary>
    /// <param name="colors">������ ������.</param>
    /// <param name="count">������ �������.</param>
    void load_colors(std::vector<glm::vec3> colors);

    void load_texture_coords(std::vector<glm::vec2> texture_coords);

    void load_normals(std::vector<glm::vec3> normals);

    /// <summary>
    /// ����� ��� �������� ������� ��������.
    /// </summary>
    /// <param name="indices">������ ��������.</param>
    /// <param name="count">������ �������.</param>
    void load_indices(std::vector<GLuint> indices);

    /// <summary>
    /// ����� ��� �������� ��������. � ����� ������� ��������� ������ ��������� � ����������� �������
    /// � ���������� ���������� ����� ������������ ��������� ���������.
    /// </summary>
    /// <param name="vect">���� � ���������� �������</param>
    /// <param name="frag">���� � ������������ �������</param>
    void load_shaders(const char* vect, const char* frag);

    /// <summary>
    /// ����� ��� �������� ��������. � ����� ������� ��������� ������ ��������� � ����������� �������
    /// � ���������� ���������� ����� ������������ ��������� ���������.
    /// </summary>
    /// <param name="vect">���� � ���������� �������</param>
    /// <param name="frag">���� � ������������ �������</param>
    void set_window(GLFWwindow* w) {
        window = w;
    };

    void LoadModelFromFile(const char* path);
    void LoadTextureCoords(std::vector<glm::vec2> texture_coords);



private:

    /// <summary>
    /// ID ������� ������
    /// </summary>
    GLuint vao = -1;
    /// <summary>
    /// ���������� ������
    /// </summary>
    size_t verteces_count = 0;
    /// <summary>
    /// ���������� ��������
    /// </summary>
    size_t indices_count = 0;

    /// <summary>
    /// ID ��������� ���������
    /// </summary>
    GLuint shader_programme = -1;

    /// <summary>
    /// ��������� �� ����
    /// </summary>
    GLFWwindow* window;
};


