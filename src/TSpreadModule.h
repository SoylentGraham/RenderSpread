#pragma once

#include "Main.h"


namespace TSpread
{
	static const uint16	gDiscoveryPorts[] = { 2500,2501,2502,2503,2504 };
	static const uint16	gClusterPorts[] = { 2600,2601,2602,2603,2604,2605,2606,2607,2608,2609,2610,2611,2612,2613,2614 };
};


//-------------------------------------------------
//	
//-------------------------------------------------
class TSpreadModule : public SoyModule
{
public:
	TSpreadModule(const char* Name);

	virtual void						Update(float TimeStep);

	virtual BufferArray<uint16,100>		GetDiscoveryPortRange() const	{	return BufferArray<uint16,100>( TSpread::gDiscoveryPorts );	}
	virtual BufferArray<uint16,100>		GetClusterPortRange() const		{	return BufferArray<uint16,100>( TSpread::gClusterPorts );	}
	virtual void						OnNetStateChanged()				{	}

private:
	void								OnNetStateChanged(SoyModule& This)	{	OnNetStateChanged();	}

public:
	//	sync'd data
	SoyModuleMember<TString>	mText;
};


