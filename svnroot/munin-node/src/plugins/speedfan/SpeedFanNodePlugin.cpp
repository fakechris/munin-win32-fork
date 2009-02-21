/* This file is part of munin-node-win32
 * Copyright (C) 2006-2008 Jory Stone (jcsston@jory.info)
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
#include "SpeedFanNodePlugin.h"

SpeedFanNodePlugin::SpeedFanNodePlugin()
{	
	m_Listener = new ListenerThread();
	m_Listener->JCThread_AddRef();
	m_Listener->Run();
}

SpeedFanNodePlugin::~SpeedFanNodePlugin()
{
	m_Listener->Stop();
	m_Listener->JCThread_RemoveRef();
}

void *SpeedFanNodePlugin::ListenerThread::Entry()
{
	// Listen on port 3639 UDP
	/** Sample xAP SpeedFan output
	xAP-header
	{
	v=12
	hop=1
	uid=FF671100
	class=PC.status
	source=Almico.SpeedFan.JCSSTON
	}
	temp.1
	{
	id=Case
	curr=38.0
	want=40
	warn=50
	}
	temp.2
	{
	id=CPU
	curr=39.0
	want=40
	warn=50
	}
	temp.4
	{
	id=Core 0
	curr=48.0
	want=40
	warn=50
	}
	temp.5
	{
	id=Core 1
	curr=52.0
	want=40
	warn=50
	}
	fan.1
	{
	id=Fan1
	curr=2689
	}
	fan.2
	{
	id=Fan2
	curr=1412
	}
	fan.3
	{
	id=Fan3
	curr=0
	}
	fan.4
	{
	id=Fan4
	curr=0
	}
	*/
	while (!TestDestroy()) {
		Sleep(0);
	}
	return NULL;
}