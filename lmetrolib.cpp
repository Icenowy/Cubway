

#define lmetrolib_cpp
#define LUA_LIB

#include "lmetrolib.h"
#include <QtCore/QProcess>
#include "metro.h"

static int luaM_dummy (lua_State *L) {
  return 0;
}

static int luaM_system (lua_State *L) {
  size_t l;
  const char *str = luaL_checklstring(L, 1, &l);
  QProcess *qp = new QProcess;
  qp->start(str);
  return 0;
}

static int luaM_load (lua_State *L) {
  size_t l;
  const char *str = luaL_checklstring(L, 1, &l);
  Metro::Mainview->load(QUrl(str));
  return 0;
}

static const luaL_Reg metrolib[] = {
  {"system",luaM_system},
  {"load",luaM_load},
  {"dummy",luaM_dummy},
  {NULL, NULL}
};

/*
** Open metro library
*/
LUAMOD_API int luaopen_metro (lua_State *L) {
  luaL_newlib(L, metrolib);
  return 1;
}

LUALIB_API void luaL_openmetrolib (lua_State *L) {
  luaL_requiref(L, "metro", luaopen_metro, 1);
  lua_pop(L, 1);  /* remove lib */
}
