#include "Model.h"
#include "func.h"
#include "globals.h"

void Model::render(GLuint mode,int cont_point)
{
    //Самый простой вариант - просто рисует, ничего в шейдер не передаёт.
    //Выбираем шейдерную программу
    glUseProgram(shader_programme);
    //Активируем массив вершин
    glBindVertexArray(vao);
    //Если индексы есть - рисуем по ним

    if (indices_count > 0)
        glDrawElements(mode, (cont_point != -1) ? cont_point : indices_count, GL_UNSIGNED_INT,0);
    else
        glDrawArrays(mode, 0, verteces_count);

    glBindVertexArray(0);
}
void Model::render(glm::mat4 MVPMatrix, GLuint mode)
{
    //Более сложный вариант - с использованием матрицы преобразований

    //Сначала всегда выбираем программу
    glUseProgram(shader_programme);

    //Теперь надо поискать в ней матрицу
    GLuint MVP = glGetUniformLocation(shader_programme, "transform");
    //Как нашли - передаём в неё значения
    glUniformMatrix4fv(MVP, 1, GL_FALSE, &MVPMatrix[0][0]);

    //А дальше всё так же как и в простом случае
    glBindVertexArray(vao);
    if (indices_count > 0)
        glDrawElements(mode, indices_count, GL_UNSIGNED_INT, 0);
    else
        glDrawArrays(mode, 0, verteces_count);

}
void Model::render(glm::mat4 ProjectionMatrix, glm::mat4 ViewMatrix ,glm::mat4 ModelMatrix, GLuint mode)
{
    //Более сложный вариант - с использованием матрицы преобразований

    //Сначала всегда выбираем программу
    glUseProgram(shader_programme);

    //Теперь надо поискать в ней матрицу
    GLuint PML = glGetUniformLocation(shader_programme, "projection");
    //Как нашли - передаём в неё значения
    glUniformMatrix4fv(PML, 1, GL_FALSE, &ProjectionMatrix[0][0]);

    GLuint VML = glGetUniformLocation(shader_programme, "view");
    glUniformMatrix4fv(VML, 1, GL_FALSE, &ViewMatrix[0][0]);

    GLuint MML = glGetUniformLocation(shader_programme, "model");
    glUniformMatrix4fv(MML, 1, GL_FALSE, &ModelMatrix[0][0]);

    //А дальше всё так же как и в простом случае
    glBindVertexArray(vao);
    if (indices_count > 0)
        glDrawElements(mode, indices_count, GL_UNSIGNED_INT, 0);
    else
        glDrawArrays(mode, 0, verteces_count);

}

void Model::render(LightsInfo lights, Material material,glm::vec3 campos
        ,glm::mat4 ProjectionMatrix, glm::mat4 ViewMatrix, glm::mat4 ModelMatrix, GLuint mode)
{
    //Более сложный вариант - с использованием матрицы преобразований

    //Сначала всегда выбираем программу
    glUseProgram(shader_programme);
    //lights
    
    //dirLight
    //  direction
    GLuint DirLight_direction = glGetUniformLocation(shader_programme, "lights.dirLight.direction");
    glUniform3fv(DirLight_direction,1, &lights.dirLight.direction[0]);
    //  ambient
    GLuint DirLight_ambient = glGetUniformLocation(shader_programme, "lights.dirLight.ambient");
    glUniform3fv(DirLight_ambient, 1, &lights.dirLight.ambient[0]);
    //  diffuse
    GLuint DirLight_diffuse = glGetUniformLocation(shader_programme, "lights.dirLight.diffuse");
    glUniform3fv(DirLight_diffuse, 1, &lights.dirLight.diffuse[0]);
    //  specular
    GLuint DirLight_specular = glGetUniformLocation(shader_programme, "lights.dirLight.specular");
    glUniform3fv(DirLight_specular, 1, &lights.dirLight.specular[0]);

    //numPLights
    GLuint numPLights = glGetUniformLocation(shader_programme, "lights.numPLights");
    glUniform1i(numPLights, lights.numPLights);
    string a;

    for (int i = 0; i < lights.numPLights; i++)
    {
        //pointLights
        //  position
        GLuint pointLights_position = glGetUniformLocation(shader_programme, (std::string( "lights.pointLights[") + std::to_string(i) + "].position").c_str());
        a = (std::string("lights.pointLights[") + std::to_string(i) + "].position").c_str();
        glUniform3fv(pointLights_position, 1, &lights.pointLights[i].position[0]);
        //  constant
        GLuint pointLights_constant = glGetUniformLocation(shader_programme, (std::string("lights.pointLights[") + std::to_string(i) + "].constant").c_str());
        glUniform1f(pointLights_constant, lights.pointLights[i].constant);
        //  linear
        GLuint pointLights_linear = glGetUniformLocation(shader_programme, (std::string("lights.pointLights[") + std::to_string(i) + "].linear").c_str());
        glUniform1f(pointLights_linear, lights.pointLights[i].linear);
        //  quadratic
        GLuint pointLights_quadratic = glGetUniformLocation(shader_programme, (std::string("lights.pointLights[") + std::to_string(i) + "].quadratic").c_str());
        glUniform1f(pointLights_quadratic, lights.pointLights[i].quadratic);
        //  ambient
        GLuint pointLights_ambient = glGetUniformLocation(shader_programme, (std::string("lights.pointLights[") + std::to_string(i) + "].ambient").c_str());
        glUniform3fv(pointLights_ambient, 1, &lights.pointLights[i].ambient[0]);
        //  diffuse
        GLuint pointLights_diffuse = glGetUniformLocation(shader_programme, (std::string("lights.pointLights[") + std::to_string(i) + "].diffuse").c_str());
        glUniform3fv(pointLights_diffuse, 1, &lights.pointLights[i].diffuse[0]);
        //  specular
        GLuint pointLights_specular = glGetUniformLocation(shader_programme, (std::string("lights.pointLights[") + std::to_string(i) + "].specular").c_str());
        glUniform3fv(pointLights_specular, 1, &lights.pointLights[i].specular[0]);
    }

    
    //numSLights
    GLuint numSLights = glGetUniformLocation(shader_programme, "lights.numSLights");
    glUniform1i(numSLights, lights.numSLights);


    for (int i = 0; i < lights.numSLights; i++)
    {
        //spotLights
        //  position
        GLuint spotLights_position = glGetUniformLocation(shader_programme, (std::string("lights.spotLights[") + std::to_string(i) + "].position").c_str());
        glUniform3fv(spotLights_position, 1, &lights.spotLights[i].position[0]);
        //  direction
        GLuint spotLights_direction = glGetUniformLocation(shader_programme, (std::string("lights.spotLights[") + std::to_string(i) + "].direction").c_str());
        glUniform3fv(spotLights_direction, 1, &lights.spotLights[i].direction[0]);
        //  constant
        GLuint spotLights_constant = glGetUniformLocation(shader_programme, (std::string("lights.spotLights[") + std::to_string(i) + "].constant").c_str());
        glUniform1f(spotLights_constant, lights.spotLights[i].constant);
        //  linear
        GLuint spotLights_linear = glGetUniformLocation(shader_programme, (std::string("lights.spotLights[") + std::to_string(i) + "].linear").c_str());
        glUniform1f(spotLights_linear, lights.spotLights[i].linear);
        //  quadratic
        GLuint spotLights_quadratic = glGetUniformLocation(shader_programme, (std::string("lights.spotLights[") + std::to_string(i) + "].quadratic").c_str());
        glUniform1f(spotLights_quadratic, lights.spotLights[i].quadratic);
        //  ambient
        GLuint spotLights_ambient = glGetUniformLocation(shader_programme, (std::string("lights.spotLights[") + std::to_string(i) + "].ambient").c_str());
        glUniform3fv(spotLights_ambient, 1, &lights.spotLights[i].ambient[0]);
        //  diffuse
        GLuint spotLights_diffuse = glGetUniformLocation(shader_programme, (std::string("lights.spotLights[") + std::to_string(i) + "].diffuse").c_str());
        glUniform3fv(spotLights_diffuse, 1, &lights.spotLights[i].diffuse[0]);
        //  specular
        GLuint spotLights_specular = glGetUniformLocation(shader_programme, (std::string("lights.spotLights[") + std::to_string(i) + "].specular").c_str());
        glUniform3fv(spotLights_specular, 1, &lights.spotLights[i].specular[0]);
        //  cutOff
        GLuint spotLights_cutOff = glGetUniformLocation(shader_programme, (std::string("lights.spotLights[") + std::to_string(i) + "].cutOff").c_str());
        glUniform1f(spotLights_cutOff, lights.spotLights[i].cutOff);
        //  outerCutOff
        GLuint spotLights_outerCutOff = glGetUniformLocation(shader_programme, (std::string("lights.spotLights[") + std::to_string(i) + "].outerCutOff").c_str());
        glUniform1f(spotLights_outerCutOff, lights.spotLights[i].outerCutOff);
    }


    //material
    //  texture
    GLuint material_texture = glGetUniformLocation(shader_programme, "material.texture");
    glUniform1i(material_texture, material.texture);// я конечно это осуждаю
    //  specularmap
    GLuint material_specularmap = glGetUniformLocation(shader_programme, "material.specularmap");
    glUniform1i(material_specularmap, material.specularmap);// я конечно это осуждаю
  
    //  shininess
    GLuint material_shininess = glGetUniformLocation(shader_programme, "material.shininess");
    glUniform1f(material_shininess, material.shininess);



    GLuint CAM = glGetUniformLocation(shader_programme, "campos");
    glUniform3fv(CAM, 1, &campos[0]);


    //Теперь надо поискать в ней матрицу
    GLuint PML = glGetUniformLocation(shader_programme, "projection");
    //Как нашли - передаём в неё значения
    glUniformMatrix4fv(PML, 1, GL_FALSE, &ProjectionMatrix[0][0]);

    GLuint VML = glGetUniformLocation(shader_programme, "view");
    glUniformMatrix4fv(VML, 1, GL_FALSE, &ViewMatrix[0][0]);

    GLuint MML = glGetUniformLocation(shader_programme, "model");
    glUniformMatrix4fv(MML, 1, GL_FALSE, &ModelMatrix[0][0]);

    // Выбор текстуры для использования (вторичное связывание)
    glActiveTexture(GL_TEXTURE0 + material.texture);
    glBindTexture(GL_TEXTURE_2D, material.texture);
    if (material.specularmap)
    {
        glActiveTexture(GL_TEXTURE0 + material.specularmap);
        glBindTexture(GL_TEXTURE_2D, material.specularmap);
    }
    

    //А дальше всё так же как и в простом случае
    glBindVertexArray(vao);
    if (indices_count > 0)
        glDrawElements(mode, indices_count, GL_UNSIGNED_INT, 0);
    else
        glDrawArrays(mode, 0, verteces_count);

    glBindTexture(GL_TEXTURE_2D, 0);

}







void Model::load_coords(std::vector<glm::vec3> verteces)
{
    //Сохранение размера массива
    verteces_count = verteces.size();

    //Создание VBO
    GLuint coords_vbo = 0;
    glGenBuffers(1, &coords_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, coords_vbo);
    glBufferData(GL_ARRAY_BUFFER, verteces.size() * sizeof(glm::vec3), verteces.data(), GL_STATIC_DRAW);

    //Так как VAO уже создан, то можно сразу связать с ним
    glBindVertexArray(vao);

    //Собственно связь
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    //Подключение атрибута
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

}

void Model::load_colors(std::vector<glm::vec3> colors)
{
    //Аналогично координатам
    //Размер сохранять не требуется - важно только число вершин
    GLuint colors_vbo = 0;
    glGenBuffers(1, &colors_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
    glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec3), colors.data(), GL_STATIC_DRAW);

    glBindVertexArray(vao);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}
void Model::load_texture_coords(std::vector<glm::vec2> texture_coords)
{
    GLuint tex_vbo = 0;
    glGenBuffers(1, &tex_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, tex_vbo);
    glBufferData(GL_ARRAY_BUFFER, texture_coords.size() * sizeof(glm::vec2), texture_coords.data(), GL_STATIC_DRAW);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, tex_vbo);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);

}
void Model::load_normals(std::vector<glm::vec3> normals)
{

    GLuint normals_vbo = 0;
    glGenBuffers(1, &normals_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, normals_vbo);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), normals.data(), GL_STATIC_DRAW);

    glBindVertexArray(vao);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void Model::load_indices(std::vector<GLuint> indices)
{
    //Сохранение числа индексов
    indices_count = indices.size();

    //Дальше всё почти как всегда с поправкой на тип буфера
    glBindVertexArray(vao);

    GLuint elementbuffer;
    glGenBuffers(1, &elementbuffer); // Генерация одного объекта буфера вершин
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer); // Привязка элементного буфера
    //Загрузка индексов в используемый элементный буфер
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

    glBindVertexArray(0);

}

void Model::load_shaders(const char* vect, const char* frag)
{
    // Переменные под результат компиляции программы
    GLint result = GL_FALSE;
    int infoLogLength;

    //Создание шейдерной программы
    shader_programme = glCreateProgram();

    //Загрузка текстов шейдеров из файлов
    string vstext = LoadShader(vect);
    const char* vertex_shader = vstext.c_str();
    string fstext = LoadShader(frag);
    const char* fragment_shader = fstext.c_str();

    //Создание вершинного шейдера
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertex_shader, NULL);
    glCompileShader(vs);

    //Проверка результата компиляции
    glGetShaderiv(vs, GL_COMPILE_STATUS, &result);
    glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &infoLogLength);
    //Вывод сообщения об ошибке если что-то пошло не так
    if (infoLogLength > 0)
    {
        char* errorMessage = new char[infoLogLength + 1];
        glGetShaderInfoLog(vs, infoLogLength, NULL, errorMessage);
        std::cout << errorMessage;
        delete errorMessage;
    }

    //Аналогично с фрагментным шейдером
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragment_shader, NULL);
    glCompileShader(fs);

    glGetShaderiv(fs, GL_COMPILE_STATUS, &result);
    glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0)
    {
        char* errorMessage = new char[infoLogLength + 1];
        glGetShaderInfoLog(fs, infoLogLength, NULL, errorMessage);
        std::cout << errorMessage;
        delete errorMessage;
    }

    //Сборка программы
    glAttachShader(shader_programme, vs);
    glAttachShader(shader_programme, fs);

    //Тонкий момент - тут жёстко связываются названия входных переменных в шейдерах со атрибутами массива вершин
    //По хорошему, это можно вынести в отдельные функции для большей универсальности.
    //Однако так как это пример, то оставлено так
    

    //Компоновка шейдерной программы
    glLinkProgram(shader_programme);

    glDeleteShader(vs);
    glDeleteShader(fs);

}
