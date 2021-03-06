// Copyright 2013 Karl Skomski - GPL v3
#include "dota2-lua-engine/commands.h"

#include "source-sdk/global_instance_manager.h"
#include "lua/lua_engine.h"

#include <string>
#include <fstream>
#include <streambuf>

namespace commands {
  CON_COMMAND(set_var, "Change cvar value") {
    if (args.ArgC() < 3) {
      Msg("Usage: set_var <cvarname> <value>\n");
      return;
    }
    ConVar* temp = g_pCVar->FindVar(args.Arg(1));
    if (temp == nullptr) {
      Warning("set_var: Could not find cvar");
      return;
    }

    temp->SetValue(atoi(args.Arg(2)));
  }

  CON_COMMAND(lua_load, "Load lua script") {
    if (args.ArgC() < 2) {
      Msg("Usage: lua_loadscript <script_name>\n");
      return;
    }
    lua::LuaEngine::GetInstance().LoadScript(args.Arg(1));
  }

  CON_COMMAND(lua_unload, "Unload lua script") {
    if (args.ArgC() < 2) {
      Msg("Usage: lua_unloadscript <script_name>\n");
      return;
    }
    lua::LuaEngine::GetInstance().UnloadScript(args.Arg(1));
  }

  CON_COMMAND(lua_execute, "Execute lua script") {
    if (args.ArgC() < 2) {
      Msg("Usage: lua_executescript <script_name>\n");
      return;
    }
    lua::LuaEngine::GetInstance().LoadScript(args.Arg(1));
    lua::LuaEngine::GetInstance().ExecuteScript(args.Arg(1));
  }

  void Register() {
    GlobalInstanceManager::GetCVar()
      ->RegisterConCommand(&set_var_command);
    GlobalInstanceManager::GetCVar()
      ->RegisterConCommand(&lua_load_command);
    GlobalInstanceManager::GetCVar()
      ->RegisterConCommand(&lua_unload_command);
    GlobalInstanceManager::GetCVar()
      ->RegisterConCommand(&lua_execute_command);
  }
  void Unregister() {
    GlobalInstanceManager::GetCVar()
      ->UnregisterConCommand(&set_var_command);
    GlobalInstanceManager::GetCVar()
      ->UnregisterConCommand(&lua_load_command);
    GlobalInstanceManager::GetCVar()
      ->UnregisterConCommand(&lua_unload_command);
    GlobalInstanceManager::GetCVar()
      ->UnregisterConCommand(&lua_execute_command);
  }
}  // namespace commands
