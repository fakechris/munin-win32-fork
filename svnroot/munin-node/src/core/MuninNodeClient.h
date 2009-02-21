#pragma once

#include "MuninNodePlugin.h"
#include "MuninPluginManager.h"

class MuninNodeClient : public JCThread {
  JCThread *m_Server;
  MuninPluginManager *m_PluginManager;
  SOCKET m_Client;
  sockaddr_in m_From;
public:
  MuninNodeClient(SOCKET client, sockaddr_in from, JCThread *server, MuninPluginManager *pluginManager);
  virtual ~MuninNodeClient();

  int SendLine(const char *line);
  int RecvLine(char *line, int len);

  virtual void *Entry();
};
