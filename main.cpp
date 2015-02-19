#include <iostream>
#include <json/json.h>
#include <iostream>
#include <fstream>

extern "C" {
#include <luajit-2.0/lua.h>
#include "luajit-2.0/lualib.h"
#include "luajit-2.0/lauxlib.h"
}

using namespace std;

struct lua {
    lua_State *L;
    lua(std::string s) {
        L = lua_open();
        luaL_openlibs(L);

        std::string script;
        script//.append("local bit32 = require('bit32')\n")
              .append("function run(t) return ")
              .append(s).append(" end");
        //std::cout << script;
        luaL_dostring(L, script.c_str());
    }

    long run(long t) {
        lua_getglobal(L, "run");
        lua_pushinteger(L, t);
        lua_call(L, 1, 1);
        long r = lua_tointeger(L, -1);
        lua_pop(L, 1);
        return r;
    }

    ~lua() {
        lua_close(L);
    }
};

int main() {
    std::ifstream file;
    file.open("sound1.json");

    Json::Value root;
    Json::Reader reader;
    bool parsedSuccess = reader.parse(file,root,false);
    for (auto& n: root["sounds"]) {
        cout << "Hello " << n["name"].asString() << "!" << endl;
        auto script = n["data"].asString();
        lua l(script);
        for (long t= 1;t<20 ;++t)
            cout << l.run(t) << ",";
        cout << std::endl;
    }
    return 0;
}

