/* HTML Tidy Lua 5.0 Bindings
   Copyright (c) 2006 Promixis, LLC 
   Author: Ron Bessems
   Date: Oct 26, 2006

   Licensed under MIT License.   
*/

// return values according to HTMLTidy.
// 0 = ok
// 1 = warning
// 2 = error
// < 0 = severe error

#include "htmltidy.h"

// create a new html tidy object.
int lua_tidy_new ( lua_State *L )
{
	pTidy t = (pTidy)lua_newuserdata(L, sizeof(sTidy));
	t->tdoc = tidyCreate();    
    t->nodeList = NULL;
    tidyBufInit(&t->errbuf);
    tidySetErrorBuffer( t->tdoc, &t->errbuf );    
	luaL_getmetatable(L, LUATIDY_HANDLE);
	lua_setmetatable(L,-2);	
	return 1;
}

static const struct luaL_reg luatidy_funcs[] =
{
	{"new", lua_tidy_new},
	{0, 0}
};


LUATIDY_API int luaopen_tidy (lua_State *L) 
{  
	createDocMetaTable(L);
	createNodeMetaTable(L);  
        
	luaL_openlib (L, LUATIDY_LIBNAME, luatidy_funcs, 0);    
    export_tidy_options(L);
    export_tidy_nodeType(L);
    export_tidy_info(L);
    
	return 1;
}

