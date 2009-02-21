#pragma once
#include "../../core/MuninNodePlugin.h"

class DiskMuninNodePlugin : public MuninNodePlugin {
  char drives[32][4];
public:
  DiskMuninNodePlugin();
  ~DiskMuninNodePlugin();

  virtual const char *GetName() { return "df"; };
  virtual int GetConfig(char *buffer, int len);
  virtual int GetValues(char *buffer, int len);
  virtual bool IsLoaded() { return true; };
};
