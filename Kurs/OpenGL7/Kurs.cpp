#define TINYOBJLOADER_IMPLEMENTATION

#include "Model.h"
#include "func.h"
#include "globals.h"
#include "LightsStructs.h"
#include <Windows.h>
#include <ctime>
#include <math.h>

int WinWidth;
int WinHeight;



GLFWwindow* ReOpenWindow(GLFWwindow* window)
{
    glfwDestroyWindow(window);
    window = glfwCreateWindow(WinWidth, WinHeight, "Capybara OpenGL", NULL, NULL);
    glfwSetWindowSizeCallback(window, window_size_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwMakeContextCurrent(window);
    glfwHideWindow(window);
    return window;
}

GLFWwindow* fun1(GLFWwindow* window)
{
    Model Earth(window);
    Model Space(window);
    Model Desk(window);
    Model Lamp(window);
    Model Car(window);
    Model Duck(window);

    std::vector<GLuint> indices;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> textures;
    std::vector<glm::vec3> normals;
 
    GLuint earthTexture = LoadTexture("earthtexture.jpg");
    GLuint earthTexture_specular_map = LoadTexture("earthtexture_SpecularMap.jpg");

    GLuint spaceTexture = LoadTexture("space.jpg");
    GLuint spaceTexture_specular_map = LoadTexture("space.jpg");

    GLuint deskTexture = LoadTexture("redwood.jpg");

    GLuint goldTexture = LoadTexture("gold.jpg");

    GLuint greyTexture = LoadTexture("grey.jpg");

    GLuint yellowTexture = LoadTexture("yellow.jpg");

    genSphere(indices, vertices, textures, normals, 50.0f, 60, 60);
    Earth.load_coords(vertices);
    Earth.load_normals(normals);
    Earth.load_indices(indices);
    Earth.load_texture_coords(textures);
    Earth.load_shaders("vs.txt", "fs.txt");

    genSphere(indices, vertices, textures, normals, 400.0f, 60, 60);
    Space.load_coords(vertices);
    Space.load_normals(normals);
    Space.load_indices(indices);
    Space.load_texture_coords(textures);
    Space.load_shaders("vs.txt", "fs.txt");

    std::vector<GLuint> indices2;
    std::vector<glm::vec3> vertices2;
    std::vector<glm::vec2> textures2;
    std::vector<glm::vec3> normals2;

    loadNew("desk.obj", vertices2, textures2, normals2);
    Desk.load_coords(vertices2);
    Desk.load_normals(normals2);
    Desk.load_texture_coords(textures2);
    Desk.load_shaders("vs.txt", "fs.txt");

    std::vector<GLuint> indices3;
    std::vector<glm::vec3> vertices3;
    std::vector<glm::vec2> textures3;
    std::vector<glm::vec3> normals3;

    loadNew("lamp.obj", vertices3, textures3, normals3);
    Lamp.load_coords(vertices3);
    Lamp.load_normals(normals3);
    Lamp.load_texture_coords(textures3);
    Lamp.load_shaders("vs.txt", "fs.txt");

    std::vector<GLuint> indices4;
    std::vector<glm::vec3> vertices4;
    std::vector<glm::vec2> textures4;
    std::vector<glm::vec3> normals4;

    loadNew("car.obj", vertices4, textures4, normals4);
    Car.load_coords(vertices4);
    Car.load_normals(normals4);
    Car.load_texture_coords(textures4);
    Car.load_shaders("vs.txt", "fs.txt");

    std::vector<GLuint> indices5;
    std::vector<glm::vec3> vertices5;
    std::vector<glm::vec2> textures5;
    std::vector<glm::vec3> normals5;

    loadNew("duck.obj", vertices5, textures5, normals5);
    Duck.load_coords(vertices5);
    Duck.load_normals(normals5);
    Duck.load_texture_coords(textures5);
    Duck.load_shaders("vs.txt", "fs.txt");

    glm::mat4 ProjectionMatrix = glm::perspective(
        glm::radians(50.0f), 	// угол обзора в радианах обычно берётся в диапазоне 30-120 градусов
        (float)WinWidth / WinHeight,       // соотношение сторон экрана
        0.01f,              // расстояние от наблюдателя до ближней плоскости отсечения
        1000.0f             //расстояние от наблюдателя до дальней плоскости отсечения
    );

    glm::vec3 CAM(0.0f, 0.0f, 0.0f);
    glm::mat4 ViewMatrix = glm::lookAt(CAM, CAM + glm::vec3(0.0f,0.0f,-1.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    glm::mat4 ModelMatrix(1);
    glm::mat4 ModelMatrix2(2);
    glm::mat4 ModelMatrix3(3);
    glm::mat4 ModelMatrix4(4);
    glm::mat4 ModelMatrix5(5);
    glm::mat4 ModelMatrix6(6);

    ModelMatrix = glm::translate(ModelMatrix, glm::vec3(-65.0f, 0.0f, -30.0f));
    ModelMatrix = glm::rotate(ModelMatrix, radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    ModelMatrix2 = glm::rotate(ModelMatrix2, radians(69.0f), glm::vec3(1.0f, 1.0f, 1.0f));
    
    ModelMatrix3 = glm::translate(ModelMatrix3, glm::vec3(0.0f, -1.8f, -1.0f));
    ModelMatrix3 = glm::scale(ModelMatrix3, glm::vec3(0.2f));

    ModelMatrix4 = glm::translate(ModelMatrix4, glm::vec3(0.4f, -0.175f, -1.0f));
    ModelMatrix4 = glm::scale(ModelMatrix4, glm::vec3(0.001f));
    ModelMatrix4 = glm::rotate(ModelMatrix4, radians(-95.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    ModelMatrix5 = glm::translate(ModelMatrix5, glm::vec3(0.0f, -0.175f, -0.7f));
    ModelMatrix5 = glm::scale(ModelMatrix5, glm::vec3(0.001f));
    ModelMatrix5 = glm::rotate(ModelMatrix5, radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    ModelMatrix6 = glm::translate(ModelMatrix6, glm::vec3(-0.4f, -0.175f, -1.5f));
    ModelMatrix6 = glm::scale(ModelMatrix6, glm::vec3(0.01f));
    ModelMatrix6 = glm::rotate(ModelMatrix6, radians(69.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    LightsInfo LI;
    LI.dirLight.direction = glm::vec3(0.0f, -1.0f, 0.0f);
    LI.dirLight.ambient = glm::vec3(0.2f, 0.2f, 0.2f);
    LI.dirLight.diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
    LI.dirLight.specular = glm::vec3(0.5f, 0.5f, 0.5f);


    LI.numPLights = 1;
    LI.numSLights = 0;

    LI.pointLights[0].position = glm::vec3(0.58f, 0.49f, -3.7f);
    LI.pointLights[0].constant = 1.0f;
    LI.pointLights[0].linear = 1.0f;
    LI.pointLights[0].quadratic = 0.1f;
    LI.pointLights[0].ambient = glm::vec3(0.9f, 0.9f, 0.9f);
    LI.pointLights[0].diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
    LI.pointLights[0].specular = glm::vec3(0.2f, 0.2f, 0.2f);


    Material earthMaterial, spaceMaterial, deskMaterial, goldMaterial, greyMaterial, yellowMaterial;
    earthMaterial.texture = earthTexture;
    earthMaterial.specularmap = earthTexture_specular_map;
    earthMaterial.specular = glm::vec3(0.6f, 0.5f, 0.5f);
    earthMaterial.shininess = 0.99f;
    glTextureParameteri(earthMaterial.texture, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(earthMaterial.texture, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    spaceMaterial.texture = spaceTexture;
    spaceMaterial.specularmap = spaceTexture_specular_map;
    spaceMaterial.specular = glm::vec3(0.6f, 0.5f, 0.5f);
    spaceMaterial.shininess = 0.99f;
    glTextureParameteri(spaceMaterial.texture, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(spaceMaterial.texture, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    deskMaterial.texture = deskTexture;
    deskMaterial.specularmap = 0;
    deskMaterial.specular = glm::vec3(0.5f, 0.6f, 0.4f);
    deskMaterial.shininess = 0.5f;
    glTextureParameteri(deskMaterial.texture, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(deskMaterial.texture, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    goldMaterial.texture = goldTexture;
    goldMaterial.specularmap = 0;
    goldMaterial.specular = glm::vec3(0.5f, 0.6f, 0.4f);
    goldMaterial.shininess = 0.5f;
    glTextureParameteri(goldMaterial.texture, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(goldMaterial.texture, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    greyMaterial.texture = greyTexture;
    greyMaterial.specularmap = 0;
    greyMaterial.specular = glm::vec3(0.5f, 0.6f, 0.4f);
    greyMaterial.shininess = 0.9f;
    glTextureParameteri(greyMaterial.texture, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(greyMaterial.texture, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    yellowMaterial.texture = yellowTexture;
    yellowMaterial.specularmap = 0;
    yellowMaterial.specular = glm::vec3(0.5f, 0.6f, 0.4f);
    yellowMaterial.shininess = 2.0f;
    glTextureParameteri(yellowMaterial.texture, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(yellowMaterial.texture, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    glLineWidth(5);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glfwShowWindow(window);

    bool flag2 = false;
    double dx = 0.0f;

    while (!glfwWindowShouldClose(window)) {

        if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
        {
            if (flag2)
                LI.numPLights = 1;
            else
                LI.numPLights = 0;
            flag2 = !flag2;
            Sleep(200);
        }

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            ViewMatrix = glm::translate(ViewMatrix, glm::vec3(0.0f, 0.0f, 0.1f));
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            ViewMatrix = glm::translate(ViewMatrix, glm::vec3(0.0f, 0.0f, -0.1f));
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            ViewMatrix = glm::translate(ViewMatrix, glm::vec3(0.1f, 0.0f, 0.0f));
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            ViewMatrix = glm::translate(ViewMatrix, glm::vec3(-0.1f, 0.0f, 0.0f));
        }
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        {
            ViewMatrix = glm::translate(ViewMatrix, glm::vec3(0.0f, -0.1f, 0.0f));
        }
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        {
            ViewMatrix = glm::translate(ViewMatrix, glm::vec3(0.0f, 0.1f, 0.0f));
        }

        ModelMatrix = glm::rotate(ModelMatrix, radians(-0.01f), glm::vec3(0.0f, 1.0f, 0.0f));
        ModelMatrix = glm::rotate(ModelMatrix, radians(0.03f), glm::vec3(1.0f, 0.0f, 0.0f));
        ModelMatrix2 = glm::rotate(ModelMatrix2, radians(0.02f), glm::vec3(1.0f, 1.0f, 0.0f));
        ViewMatrix = glm::rotate(ViewMatrix, glm::radians(0.5f * getDirection()), glm::vec3(0.0f, 0.05f, 0.0f));
        if (!(getDirection() < 0 && dx < -280) && !(getDirection() > 0 && dx > 160))
        {
            ModelMatrix5 = glm::translate(ModelMatrix5, glm::vec3(0.0f, 0.0f, getDirection() * 4.0f));
            dx += getDirection() * 4.0f;
        }
        glViewport(0, 0, WinWidth, WinHeight);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        Earth.render(LI, earthMaterial, CAM, ProjectionMatrix, ViewMatrix, ModelMatrix, GL_TRIANGLES);
        Space.render(LI, spaceMaterial, CAM, ProjectionMatrix, ViewMatrix, ModelMatrix2, GL_TRIANGLES);
        Desk.render(LI, deskMaterial, CAM, ProjectionMatrix, ViewMatrix, ModelMatrix3, GL_TRIANGLES);
        Lamp.render(LI, goldMaterial, CAM, ProjectionMatrix, ViewMatrix, ModelMatrix4, GL_TRIANGLES);
        Car.render(LI, greyMaterial, CAM, ProjectionMatrix, ViewMatrix, ModelMatrix5, GL_TRIANGLES);
        Duck.render(LI, yellowMaterial, CAM, ProjectionMatrix, ViewMatrix, ModelMatrix6, GL_TRIANGLES);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    window = ReOpenWindow(window);


    return window;
}
int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand((int)time(0));
    double start_time = glfwGetTime();
    GLFWwindow* window = InitAll(1280, 720, false);
    if (window == nullptr) { EndAll(); return -1; }
    glfwHideWindow(window);



    int menu;
    do
    {
        Model main(window);
        glm::vec3* vertexes = nullptr;
        glm::vec3* colors = nullptr;
        GLuint* indices = nullptr;


        std::cout << "Меню выбора программы:" << std::endl;
        std::cout << "1) Запустить сцену" << std::endl;
        std::cout << "2) Выход" << std::endl;

        std::cin >> menu;
        switch (menu) {
        case 1:
            window = fun1(window);
            break;
        }




        system("cls");
    } while (menu != 2);







    EndAll();

}

