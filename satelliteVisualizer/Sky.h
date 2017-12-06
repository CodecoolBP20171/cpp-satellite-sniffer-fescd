#pragma once

#include "stdafx.h"
#include <stdio.h>
#include "coreLib.h"
#include "orbitLib.h"

class Sky
{
public:
	Sky();
	~Sky();

	void evaluate();
	void PrintPosVel(const cSatellite& sat);

};

