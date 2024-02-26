#pragma once
#include "globals.h"
#define MAX_NUM_LIGHTS 10
using namespace glm;
struct DirLight //Фоновый освещение
{
	vec3 direction; //Направление света

	//Параметры компонент света
	vec3 ambient; //Фоновый цвет
	vec3 diffuse; //Дифузный цвет
	vec3 specular; //Зеркальный цвет
};
struct PointLight //Точечный источник освещения
{
	vec3 position; //Позиция
	//Параметры затухания
	float constant; //Константный коэффициент
	float linear; //Коэффициент линейного затухания
	float quadratic; //Коэффициент квадратичного затухания

	//Параметры компонент света
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
struct SpotLight //Направленный источник освещения
{
	vec3 position; //Позиция
	vec3 direction; //Направление света
	//Параметры угла
	float cutOff; //Косинус угола, по достижении которого свет начинает плавно затухать
	// до достижения порогового угла
	float outerCutOff; //Косинус Пороговый угол

	//Параметры затухания
	float constant;
	float linear;
	float quadratic;

	//Параметры компонент света
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct LightsInfo {
	DirLight dirLight; //Фоновое освещение
	PointLight pointLights[MAX_NUM_LIGHTS];//Точечные источники освещения
	SpotLight spotLights[MAX_NUM_LIGHTS];// Направленные источники освещения
	int numPLights; //Кол-во точечных источников
	int numSLights; //Кол-во направленных источников
};
struct Material {
	GLuint texture; //id текстуры
	GLuint specularmap; //id текстуры карты отражений
	vec3 specular; //Зеркальный цвет отражения
	float shininess; //Степень отражения
};