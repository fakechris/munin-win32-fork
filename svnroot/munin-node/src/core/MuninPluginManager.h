#pragma once

#include "MuninNodePlugin.h"
#include "MuninNodeSettings.h"
#include <vector>

class MuninPluginManager
{
public:
  MuninPluginManager();
  ~MuninPluginManager();

  size_t GetCount() { return m_Plugins.size(); }
  MuninNodePlugin * operator [] (int index) {
    return m_Plugins.at(index);
  }

  void AddPlugin(MuninNodePlugin *plugin);
  MuninNodePlugin *LookupPlugin(const char *name);
  void FillPluginList(char *buffer, int len);

private:
  std::vector<MuninNodePlugin *> m_Plugins;
};
