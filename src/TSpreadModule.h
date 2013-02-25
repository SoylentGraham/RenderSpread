#pragma once

#include "Main.h"


namespace TSpread
{
	static const uint16	gDiscoveryPorts[] = { 2500,2501,2502,2503,2504 };
	static const uint16	gClusterPorts[] = { 2600,2601,2602,2603,2604 };
};


//-------------------------------------------------
//	
//-------------------------------------------------
class TSpreadModule : public SoyModule
{
public:
	TSpreadModule(const char* Name);

	virtual BufferArray<uint16,10>		GetDiscoveryPortRange() const	{	return BufferArray<uint16,10>( TSpread::gDiscoveryPorts );	}
	virtual BufferArray<uint16,10>		GetClusterPortRange() const		{	return BufferArray<uint16,10>( TSpread::gClusterPorts );	}
	virtual void						OnNetStateChanged()				{	}

private:
	void								OnNetStateChanged(SoyModule& This)	{	OnNetStateChanged();	}

public:
	//	sync'd data
	SoyModuleMember<TString>	mText;
};


