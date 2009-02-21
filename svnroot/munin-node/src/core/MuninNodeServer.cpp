/* This file is part of munin-node-win32
 * Copyright (C) 2006-2007 Jory Stone (jcsston@jory.info)
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include "StdAfx.h"
#include "MuninNodeServer.h"
#include "Service.h"

void *MuninNodeServer::Entry()
{	
  SOCKET server;
  WSADATA wsaData;
  sockaddr_in local;

  //WSAStartup initializes the program for calling WinSock.
  //The first parameter specifies the highest version of the 
  //WinSock specification, the program is allowed to use.
  int wsaret = WSAStartup(0x101, &wsaData);
  if (wsaret != 0) {
    return 0;
  }

  //Now we populate the sockaddr_in structure
  local.sin_family = AF_INET; //Address family
  local.sin_addr.s_addr = INADDR_ANY; //Wild card IP address
  local.sin_port = htons((u_short)4949); //port to use

  //the socket function creates our SOCKET
  server = socket(AF_INET, SOCK_STREAM, 0);
  if (server == INVALID_SOCKET) {
    return 0;
  }

  //bind links the socket we just created with the sockaddr_in 
  //structure. Basically it connects the socket with 
  //the local address and a specified port.
  //If it returns non-zero quit, as this indicates error
  if (bind(server, (sockaddr*)&local, sizeof(local)) != 0) {
    return 0;
  }

  //listen instructs the socket to listen for incoming 
  //connections from clients. The second arg is the backlog
  if (listen(server, 10) != 0) {
    return 0;
  }

  SOCKET client;
  sockaddr_in from;
  int fromlen = sizeof(from);

  _Module.LogEvent("Server Thread Started");

  while (!TestDestroy()) {
    // Wait for new client connection
    client = accept(server, (struct sockaddr*)&from, &fromlen);

    _Module.LogEvent("Connection from %s", inet_ntoa(from.sin_addr));
    // Start child thread to process client socket
    MuninNodeClient *clientThread = new MuninNodeClient(client, from, this, &m_PluginManager);
    clientThread->Run();
  }

  // Cleanup the server socket
  closesocket(server);
  WSACleanup();

  return 0;
}
