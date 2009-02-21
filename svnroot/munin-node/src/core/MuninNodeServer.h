#pragma once

#include "MuninPluginManager.h"
#include "MuninNodeClient.h"

class MuninNodeServer : public JCThread {
  MuninPluginManager m_PluginManager;
public:
  virtual void *Entry();
};
