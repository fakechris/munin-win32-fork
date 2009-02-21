#pragma once

#include "MuninNodeSettings.h"

class MuninNodePlugin {
public:
  /// This method should always be thread-safe
  virtual bool IsLoaded() = 0;
  /// This method should also always be thread-safe
  virtual const char *GetName() = 0;
  virtual int GetConfig(char *buffer, int len) = 0;
  virtual int GetValues(char *buffer, int len) = 0;  
  virtual bool IsThreadSafe();
};

/// This is a cheap locking wrapper for any MuninNodePlugin class
/// It locks the GetConfig and GetValues methods
class MuninNodePluginLockWrapper : public MuninNodePlugin, public JCCritSec {
public:
  MuninNodePluginLockWrapper(MuninNodePlugin *plugin);
  virtual const char *GetName();
  virtual int GetConfig(char *buffer, int len);
  virtual int GetValues(char *buffer, int len);
  virtual bool IsLoaded();
  virtual bool IsThreadSafe();
private:
  MuninNodePlugin *m_Plugin;
  //JCCritSec m_CritSec;
};
