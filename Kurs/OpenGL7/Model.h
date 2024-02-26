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
    /// Простой конструктор - создаёт массив вершин, пока пустой. И подключает окно.
    /// </summary>
    /// <param name="w"></param>
    Model(GLFWwindow* w) {
        glGenVertexArrays(1, &vao);
        window = w;
    };

    //Деструктор. Так как динамической памяти нет, то он ничего не делает.
    ~Model() {};

    //Метод для отображения модели.     
    /// <summary>
    /// Рендер почти без параметров - просто отображает массив вершин.
    /// </summary>
    /// <param name="mode">Единственный параметр - режим рисования.</param>
    void render(GLuint mode = GL_TRIANGLES, int cont_point = -1);
    //Метод для отображения модели c использованием матрицы.     
    /// <summary>
    /// Рендер почти без параметров - просто отображает массив вершин.
    /// </summary>
    /// <param name="mode">Единственный параметр - режим рисования.</param>
    void render(glm::mat4 MVPMatrix, GLuint mode);
    void render(glm::mat4 ProjectionMatrix, glm::mat4 ViewMatrix, glm::mat4 ModelMatrix, GLuint mode);
    void render(LightsInfo lights, Material material, glm::vec3 campos, glm::mat4 ProjectionMatrix, glm::mat4 ViewMatrix, glm::mat4 ModelMatrix, GLuint mode);
    //Набор методов для загрузки составляющих массива вершин
    //В дальнейшем аналогично стоит добавлять новые функции

    /// <summary>
    /// Метод для загрузки координат вершин.
    /// </summary>
    /// <param name="verteces">Массив с координатами.</param>
    /// <param name="count">Размер массива.</param>
    void load_coords(std::vector<glm::vec3> verteces);
    /// <summary>
    /// Метод для загрузки цветов вершин.
    /// </summary>
    /// <param name="colors">Массив цветов.</param>
    /// <param name="count">Размер массива.</param>
    void load_colors(std::vector<glm::vec3> colors);

    void load_texture_coords(std::vector<glm::vec2> texture_coords);

    void load_normals(std::vector<glm::vec3> normals);

    /// <summary>
    /// Метод для загрузки массива индексов.
    /// </summary>
    /// <param name="indices">Массив индексов.</param>
    /// <param name="count">Размер массива.</param>
    void load_indices(std::vector<GLuint> indices);

    /// <summary>
    /// Метод для загрузки шейдеров. С целью примера загружает только вершинный и фрагментный шейдеры
    /// В результате выполнения будет скомпонована шейдерная программа.
    /// </summary>
    /// <param name="vect">Путь к вершинному шейдеру</param>
    /// <param name="frag">Путь к фрагментному шейдеру</param>
    void load_shaders(const char* vect, const char* frag);

    /// <summary>
    /// Метод для загрузки шейдеров. С целью примера загружает только вершинный и фрагментный шейдеры
    /// В результате выполнения будет скомпонована шейдерная программа.
    /// </summary>
    /// <param name="vect">Путь к вершинному шейдеру</param>
    /// <param name="frag">Путь к фрагментному шейдеру</param>
    void set_window(GLFWwindow* w) {
        window = w;
    };

    void LoadModelFromFile(const char* path);
    void LoadTextureCoords(std::vector<glm::vec2> texture_coords);



private:

    /// <summary>
    /// ID массива вершин
    /// </summary>
    GLuint vao = -1;
    /// <summary>
    /// Количество вершин
    /// </summary>
    size_t verteces_count = 0;
    /// <summary>
    /// Количество индексов
    /// </summary>
    size_t indices_count = 0;

    /// <summary>
    /// ID шейдерной программы
    /// </summary>
    GLuint shader_programme = -1;

    /// <summary>
    /// Указатель на окно
    /// </summary>
    GLFWwindow* window;
};


