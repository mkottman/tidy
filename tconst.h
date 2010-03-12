#ifdef __cplusplus
extern "C" {
#endif

#include "htmltidy.h"

void export_tidy_info(lua_State *L);
void export_tidy_nodeType ( lua_State * L);
void export_tidy_options(lua_State *L);

#ifdef __cplusplus
}
#endif
