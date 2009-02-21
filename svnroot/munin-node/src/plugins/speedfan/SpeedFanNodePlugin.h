#pragma once
#include "../../core/MuninNodePlugin.h"

class SpeedFanNodePlugin : public MuninNodePlugin
{
public:
	SpeedFanNodePlugin();
	~SpeedFanNodePlugin();

private:
	class ListenerThread : public JCThread {
	public:		
		virtual void *Entry();
	};
	JCThread *m_Listener;
};

