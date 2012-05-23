#pragma once
#include "MyGame3DDevice.h"
#include <map>
using std::map;
//typedef struct type_cout{
//	string type;
//	int		count;
//}type_count;

class testLoadObjFile
{
private:
	unsigned int vertexBufferKey;

	//MyGameTexture* pTex;
	
	//vector<int>		verticeList;//�������Ϊ���֡�\
	verticeList[0]��ʾ��һ�γ��ֵĹ����ı��εĶ���ĸ�����1��ʾ��һ�γ��ֵĹ��������εĶ���ĸ���\
	2��ʾ�ڶ��γ��ֵĹ����ı��εĶ���ĸ�����3��ʾ�����γ��ֵĹ��������εĶ���ĸ���\
																			�Դ�����
	vector<string>			materialList;
	vector<vector<int>>		verticeGroupListOfMaterial;//��materialList��һһ��Ӧ��


	map<string, MyGameTexture* >	textureList;

	unsigned int	verticeNum;
public:
	testLoadObjFile( string _meshName );
	~testLoadObjFile(void);
	
	void render();

	int renderVertexListOfMaterial( string _materialName, vector<int> verticeList, int verticeNumDrawed );
};

