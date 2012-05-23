#pragma once
//#pragma comment (lib, "lua5.1.lib")
#include <lua.hpp>
#include <lauxlib.h>
#include <lualib.h>
#include "MyGameFunctions.h"

#include <string>
using std::string;
class MyGameLua
{
private:
	lua_State* luaState;

	//the C function that will be loaded automatically
/*	static int cFunction( lua_State* L );

	// the function that will be automatically called in
	// CFunction
	int (*Func)(MyGameLua* _luaScript);
*/
public:
	
	MyGameLua(void);
	~MyGameLua(void);

	void OpenLuaLibs();

	int LoadAScriptFile(/*char* _fileName*/ string _fileName);

	int RunALine(const char*);	//returns error code

	//push global value(or function- -!) to lua stack by name in script
	bool PushGlobalByName(const char* _valueName) const;

	bool RunLuaFunction(int _paraAmount, int _rsAmount) const;

	//push a c function(and rename it) MUST be call before Load Script
	//AFTER open libs
	bool PushCFunctionToLuaByName(int (*lua_CFunction)(lua_State*), string _newFunctionName/*rename the func*/) const;

	bool PushLuaFunctionToCByName(const char* _valueName) const;

//	bool PushFunction(int (*_fun)(MyGameLua* _luaScript), const char* _newFuncName);
	
	//clean the stack
	void CleanStack();

	//get integer from stack by number
	int GetIntFromStack(int _num);

	const char* GetStringFromStack(int _num);
};

