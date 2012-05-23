#include "StdAfx.h"
#include "testLoadObjFile.h"
#include <vector>
using std::vector;

testLoadObjFile::testLoadObjFile( string _meshName )
	:verticeNum(0)
{
	char objName[50];
	char mtlName[50];
	sprintf( objName, "map/%s.obj", _meshName.c_str() );
	sprintf( mtlName, "map/%s.mtl", _meshName.c_str() );
	FILE* pFile = fopen( objName, "r" );
	
	if( pFile == 0 )
		return;

	//Read  x y z
	vector<myVertex> xyzBuffer;
	myVertex newVertex;
	char str[50];
	fgets( str, 50, pFile );
	while( str[0] !='v' )
	{
		fgets( str, 50, pFile );
	}
	//Start to Read them
	while( str[0] =='v' )
	{
		sscanf( str, "v  %f %f %f", &newVertex.pos.x, &newVertex.pos.y, &newVertex.pos.z);
		xyzBuffer.push_back( newVertex );
		fgets( str, 50, pFile );
	}

	//Read  normal
	vector<myVertex> normalBuffer;
	
	while( str[0] !='v' )
	{
		fgets( str, 50, pFile );
	}
	while( str[0] == 'v' && str[1] == 'n' )
	{
		sscanf( str, "vn  %f %f %f", &newVertex.normal.x, &newVertex.normal.y, &newVertex.normal.z );
		normalBuffer.push_back( newVertex );
		fgets( str, 50, pFile );
	}

	//Read texture coordinate
	vector<myVertex> textureBuffer;
	while( str[0] !='v' && str[1] != 't' )
	{
		fgets( str, 50, pFile );
	}
	while( str[0] == 'v' && str[1] == 't' )
	{
		float z;
		sscanf( str, "vt  %f %f %f", &newVertex.texCoord.x, &newVertex.texCoord.y, &z );
		textureBuffer.push_back( newVertex );
		fgets( str, 50, pFile );
	}

		//Read material
		//map<int, string> 


	
	// Read vertex buffer
	vector<myVertex> vertexBuffer;
	int rs = 1;
	while( rs != 0 )
	{
	switch( str[0] )
	{
	case 'u':
		if( str[0] =='u' && str[1] == 's' && str[2] == 'e' )
		{
			char _mtlName[50];
			sscanf( str, "usemtl %s", _mtlName );
			materialList.push_back( _mtlName );
		}
		if( 0 == fgets( str, 50, pFile ) )
			rs = 0;
		break;/*
		while( str[0] !='f' )
		{
			fgets( str, 50, pFile );
		}*/
	case 'f':
		{
		int currentVertexNum = 0;		//����������ǰ�ۼƵ�vertex������ۼƵĶ�����������������������ĸ�һ�飩ͻȻ���ˣ��Ǿ�push_back������ݣ��������
		vector<int> verticeList;
#define FOUR true
#define THREE false
		bool currentVertexType = FOUR;
		while( str[0] == 'f')
		{
			unsigned int numVer = 0;
			for( unsigned int i = 0; str[i] != '\0'; ++ i ) 
			{
				if( str[i] == ' ' )//����ǿո�
					numVer++;
			}
			numVer--;
			unsigned int number[12];
			myVertex vert[4];
			switch( numVer )
			{
				//�����4������
			case 4:
				if( currentVertexType == FOUR )		//����ϴξ����ĸ�����
				{
					currentVertexNum +=4;
				}else	//�ϴ����������㣬push_back�ϴεĶ�������Ȼ�����¿�ʼ����
				{
					verticeList.push_back( currentVertexNum );
					currentVertexNum = 4;
					currentVertexType = FOUR;
				}
				sscanf( str, "f %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d ", &number[0], &number[1], &number[2], &number[3], &number[4], &number[5],
					&number[6], &number[7], &number[8], &number[9], &number[10], &number[11] );
				
				vert[0].pos = xyzBuffer[ number[0]-1 ].pos; vert[0].texCoord = textureBuffer[ number[1]-1 ].texCoord; vert[0].normal = normalBuffer[ number[2]-1 ].normal;
				vert[1].pos = xyzBuffer[ number[3]-1 ].pos; vert[1].texCoord = textureBuffer[ number[4]-1 ].texCoord; vert[1].normal = normalBuffer[ number[5]-1 ].normal;
				vert[2].pos = xyzBuffer[ number[6]-1 ].pos; vert[2].texCoord = textureBuffer[ number[7]-1 ].texCoord; vert[2].normal = normalBuffer[ number[8]-1 ].normal;
				vert[3].pos = xyzBuffer[ number[9]-1 ].pos; vert[3].texCoord = textureBuffer[ number[10]-1 ].texCoord; vert[3].normal = normalBuffer[ number[11]-1 ].normal;
				vertexBuffer.push_back( vert[0] ); vertexBuffer.push_back( vert[1] ); vertexBuffer.push_back( vert[2] ); vertexBuffer.push_back( vert[3] );
				verticeNum += 4;
				break;
				//�����3������
			case 3:
				if( currentVertexType == THREE )	//����ϴ�����������
				{
					currentVertexNum += 3;
				}else	//�ϴ����ĸ����㣬push_back�ϴεĶ�������Ȼ�����¿�ʼ����
				{
					verticeList.push_back( currentVertexNum );
					currentVertexNum = 3;
					currentVertexType = THREE;
				}
				sscanf( str, "f %d/%d/%d %d/%d/%d %d/%d/%d", &number[0], &number[1], &number[2], &number[3], &number[4], &number[5],
					&number[6], &number[7], &number[8] );
			
				vert[0].pos = xyzBuffer[ number[0]-1 ].pos; vert[0].texCoord = textureBuffer[ number[1]-1 ].texCoord; vert[0].normal = normalBuffer[ number[2]-1 ].normal;
				vert[1].pos = xyzBuffer[ number[3]-1 ].pos; vert[1].texCoord = textureBuffer[ number[4]-1 ].texCoord; vert[1].normal = normalBuffer[ number[5]-1 ].normal;
				vert[2].pos = xyzBuffer[ number[6]-1 ].pos; vert[2].texCoord = textureBuffer[ number[7]-1 ].texCoord; vert[2].normal = normalBuffer[ number[8]-1 ].normal;
				vertexBuffer.push_back( vert[0] ); vertexBuffer.push_back( vert[1] ); vertexBuffer.push_back( vert[2] );
				verticeNum += 3;
				break;
			default:
				break;
			}
			if( 0 == fgets( str, 50, pFile ) )
				rs = 0;
		}//����һ�в�����f��ͷ��ʱ�����While������
		verticeList.push_back(currentVertexNum);//�����һ��ŵ�verticeList

		//Ȼ��������ѹ��verticeGroupListOfMaterial
		verticeGroupListOfMaterial.push_back( verticeList );
		}
		break;
	default:
		if( 0 == fgets( str, 50, pFile ) )
			rs = 0;
	}
	}
	myVertex *pVertex = new myVertex[verticeNum];

	int i = 0;

	for( vector<myVertex>::iterator _itr = vertexBuffer.begin();
		_itr != vertexBuffer.end();
		++ _itr )
	{
		pVertex[i] = *_itr;
		++ i;
	}

	this->vertexBufferKey = MyGame3DDevice::CreateVertexBuffer( uiVertex, (void*)pVertex, sizeof(myVertex)* verticeNum );

	delete[] pVertex;

	//pTex = MyGame3DDevice::CreateMyTextureFromFile( "map/temp.jpg" );

	fclose( pFile );

	pFile = fopen( mtlName, "r" );

	//char str[50]


	while( fgets( str, 50, pFile )!=0 )
	{
		//fgets( str, 50, pFile );

		while( str[0]=='n'&&str[1]=='e'&&str[2]=='w'&&str[3]=='m'&&str[4]=='t'&&str[5]=='l' )	//����� newmtl
		{
			char mtlName[50];
			sscanf( str, "newmtl %s", &mtlName );

			if( 0==fgets( str, 50, pFile ))
				break;

			while( str[0] == '\t' )
			{
				if( str[0] == '\t'&& str[1] == 'm'&& str[6] == 'a' )	//���������Ҫ����һ��
				{
					char mtlDirectory[50];
					sscanf( str, "\tmap_Ka %s", &mtlDirectory );
					sprintf( str, "map\\%s", mtlDirectory );
					MyGameTexture* _texture = MyGame3DDevice::CreateMyTextureFromFile( str );
					textureList[mtlName] = _texture;
				}
				if( 0 == fgets( str, 50, pFile ) )
					break;
			}

		}
		//fgets( str, 50, pFile );
	}

	//while( str[0]!='n'/*&&str[1]=='e'&&str[2]=='w'&&str[3]=='m'&&str[4]=='t'&&str[5]=='l'*/)
	//{
	//	char mtlName[50];
	//	sscanf( str, "newmtl %s", mtlName );

	//	fgets( str, 50, pFile );

	//	while( str[0] == '\t'&& str[1] == 'm'&& str[6] == 'a' )
	//	{

	//	}


	//}


	fclose( pFile );

}


testLoadObjFile::~testLoadObjFile(void)
{
	for( map< string, MyGameTexture* >::iterator _itr = textureList.begin();
		_itr != textureList.end(); ++ _itr )
	{
		delete (*_itr).second;
	}
	MyGame3DDevice::DestroyVertexBuffer( this->vertexBufferKey );
	//delete pTex;
}

void testLoadObjFile::render()
{
	//MyGame3DDevice::EnableMyUITexture( pTex );
	MyGame3DDevice::SetVertexBuffer( this->vertexBufferKey );

	int verticeNumDrawed = 0;

	//for( vector<int>::iterator _itr = verticeList.begin();
	//	_itr != verticeList.end();
	//	++ _itr )
	//{
	//	//MyGame3DDevice::DrawTrianglePrimitive( D3DPT_TRIANGLEFAN, verticeNumDrawed, (*_itr)/2 );//�����ˣ������û������εķ����������ı��Σ���

	//	verticeNumDrawed +=  *_itr;
	//	++ _itr;
	//	if( _itr == verticeList.end() )
	//	{
	//		break;
	//	}
	//	else{
	//		MyGame3DDevice::DrawTrianglePrimitive( D3DPT_TRIANGLELIST, verticeNumDrawed, (*_itr)/3 );
	//	}
	//}

	
	vector< vector<int> >::iterator _itr2 = verticeGroupListOfMaterial.begin();


	for( vector< string >::iterator _itr = materialList.begin();
		_itr != materialList.end();
		++ _itr )
	{


		verticeNumDrawed = renderVertexListOfMaterial( *_itr, *_itr2, verticeNumDrawed );


		++_itr2;
	}
}

int testLoadObjFile::renderVertexListOfMaterial( string _materialName, vector<int> verticeList, int verticeNumDrawed )
{
	//Enabe materiall(TODO:)
	if( textureList.count(_materialName) )
		MyGame3DDevice::EnableMyUITexture( textureList[ _materialName] );



	for( vector<int>::iterator _itr = verticeList.begin();
		_itr != verticeList.end();
		++ _itr )
	{
		//MyGame3DDevice::DrawTrianglePrimitive( D3DPT_TRIANGLEFAN, verticeNumDrawed, (*_itr)/2 );//�����ˣ������û������εķ����������ı��Σ���

		verticeNumDrawed +=  *_itr;
		++ _itr;
		if( _itr == verticeList.end() )
		{
			break;
		}
		else{
			MyGame3DDevice::DrawTrianglePrimitive( D3DPT_TRIANGLELIST, verticeNumDrawed, (*_itr)/3 );
		}
		verticeNumDrawed +=  *_itr;
	}

	return verticeNumDrawed;

}