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
	
	//vector<int>		verticeList;//将顶点分为两种。\
	verticeList[0]表示第一次出现的构成四边形的顶点的个数，1表示第一次出现的构成三角形的顶点的个数\
	2表示第二次出现的构成四边形的顶点的个数，3表示第三次出现的构成三角形的顶点的个数\
																			以此类推
	vector<string>			materialList;
	vector<vector<int>>		verticeGroupListOfMaterial;//与materialList是一一对应的


	map<string, MyGameTexture* >	textureList;

	unsigned int	verticeNum;
public:
	testLoadObjFile( string _meshName );
	~testLoadObjFile(void);
	
	void render();

	int renderVertexListOfMaterial( string _materialName, vector<int> verticeList, int verticeNumDrawed );
};

