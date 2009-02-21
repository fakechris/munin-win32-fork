#pragma once
#include "../core/MuninNodePlugin.h"
#include <vector>
#include <string>
#include <PDHMsg.h>

class PerfCounterMuninNodePlugin : public MuninNodePlugin
{
public:
  /// \param sectionName The INI File section name for this plugin
  PerfCounterMuninNodePlugin(const std::string &sectionName);
  ~PerfCounterMuninNodePlugin();

  virtual const char *GetName() { return m_Name.c_str(); };
  virtual int GetConfig(char *buffer, int len);
  virtual int GetValues(char *buffer, int len);
  virtual bool IsLoaded() { return m_Loaded; };

private:
  bool OpenCounter();

  bool m_Loaded;
  std::string m_Name;
  std::string m_SectionName;
  HQUERY m_PerfQuery;
  std::vector<std::string> m_CounterNames;
  std::vector<HCOUNTER> m_Counters;
};
