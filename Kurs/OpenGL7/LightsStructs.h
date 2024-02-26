#pragma once
#include "globals.h"
#define MAX_NUM_LIGHTS 10
using namespace glm;
struct DirLight //������� ���������
{
	vec3 direction; //����������� �����

	//��������� ��������� �����
	vec3 ambient; //������� ����
	vec3 diffuse; //�������� ����
	vec3 specular; //���������� ����
};
struct PointLight //�������� �������� ���������
{
	vec3 position; //�������
	//��������� ���������
	float constant; //����������� �����������
	float linear; //����������� ��������� ���������
	float quadratic; //����������� ������������� ���������

	//��������� ��������� �����
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
struct SpotLight //������������ �������� ���������
{
	vec3 position; //�������
	vec3 direction; //����������� �����
	//��������� ����
	float cutOff; //������� �����, �� ���������� �������� ���� �������� ������ ��������
	// �� ���������� ���������� ����
	float outerCutOff; //������� ��������� ����

	//��������� ���������
	float constant;
	float linear;
	float quadratic;

	//��������� ��������� �����
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct LightsInfo {
	DirLight dirLight; //������� ���������
	PointLight pointLights[MAX_NUM_LIGHTS];//�������� ��������� ���������
	SpotLight spotLights[MAX_NUM_LIGHTS];// ������������ ��������� ���������
	int numPLights; //���-�� �������� ����������
	int numSLights; //���-�� ������������ ����������
};
struct Material {
	GLuint texture; //id ��������
	GLuint specularmap; //id �������� ����� ���������
	vec3 specular; //���������� ���� ���������
	float shininess; //������� ���������
};