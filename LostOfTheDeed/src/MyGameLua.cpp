#include "StdAfx.h"
#include "MyGameLua.h"


MyGameLua::MyGameLua(void)
	:luaState(0)
{
	//MessageBoxA(0,"囧，MyGameLua构造函数开始",0,0);
		
	luaState = luaL_newstate();
	//MessageBoxA(0,"囧，luaL_newstate()调用成功",0,0);
#ifdef _DEBUG
	luaL_openlibs(luaState);
#endif
}

void MyGameLua::OpenLuaLibs()
{
#ifndef _DEBUG
	luaL_openlibs(luaState);
#endif
}

MyGameLua::~MyGameLua(void)
{
	lua_close(luaState);
	luaState = NULL;
}

int MyGameLua::RunALine(const char* _buf)
{
	int errorCode;
	
	errorCode = luaL_loadbuffer(luaState, _buf, strlen(_buf), "line") || 
				//_buf is a buffer, don't regard it as a string, so the third parameter is strlen(_buf)
                lua_pcall(luaState, 0, 0, 0);
	return errorCode;
}

int MyGameLua::LoadAScriptFile(/*char* _fileName*/ string _fileName)
{
	int errorCode = luaL_loadfile(luaState, _fileName.c_str()) || lua_pcall( luaState, 0, 0, 0);

	if ( !errorCode )
	{
		MyGameMessage(_fileName<<"--Loaded successfully");
	}
	else		//rs!=0, error
		MyGameMessage(_fileName<<"--Load failed,error code:"<<errorCode);
	return errorCode;
}

bool MyGameLua::PushGlobalByName(const char* _valueName) const
{
	lua_getglobal(luaState, _valueName);

	//get the variabal that was currently pushed
	int _index = lua_gettop (luaState);//get index
	if(lua_isnil (luaState,  _index))
	{
		lua_pop (luaState, 1);
		return false;
	}
	return true;
}

bool MyGameLua::PushLuaFunctionToCByName(const char* _valueName) const
{
	lua_getglobal(luaState, _valueName);

	//get the variabal that was currently pushed
	int _index = lua_gettop (luaState);//get index
	if(lua_isnil (luaState,  _index))
	{
		lua_pop (luaState, 1);
		return false;
	}
	return true;
}

bool MyGameLua::PushCFunctionToLuaByName(int (*lua_CFunction)(lua_State*),/* const char* _newName*/ string _newFunctionName) const
{
	if( !lua_CFunction )
		return false;
	lua_pushcfunction( luaState, lua_CFunction );
	lua_setglobal( luaState,_newFunctionName.c_str() );
	return true;
}
/*
int MyGameLua::cFunction( lua_State* L)
{
	return Func(this);
}

bool MyGameLua::PushFunction( int (*_fun)(MyGameLua* _luaScript), const char* _newFuncName)
{
	if( !_fun )
		return false;
	this->Func = _fun;
	lua_pushcfunction( luaState, cFunction );
	lua_setglobal( luaState, _newFuncName);
	return true;
}
*/
void MyGameLua::CleanStack()
{
	lua_settop(luaState, 0);
}

int MyGameLua::GetIntFromStack(int _num)
{
	// test if it is an Integer value
	if(!lua_isnumber(luaState, _num))
		::MessageBox( 0, L"it is not a number", L"error", 0);

	return lua_tointeger(luaState, _num);
}

const char* MyGameLua::GetStringFromStack(int _num)
{
	// test if it is a string value
	if(!lua_isstring(luaState, _num))
		::MessageBox( 0, L"it is not a number", L"error", 0);

	const char* _tring = lua_tostring(luaState, _num);

	//int len = strlen(_tring);

	//char* newString = new char[len];

	//strcpy(newString, _tring);

	return _tring;
}

bool MyGameLua::RunLuaFunction(int _paraAmount, int _rsAmount) const
{
	if( lua_pcall( luaState, _paraAmount, _rsAmount, 0 ) )
	{
		MyGameMessage( "lua function run error" );
		return false;
	}
	return true;
}