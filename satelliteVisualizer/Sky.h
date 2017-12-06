#pragma once

#include "stdafx.h"
#include <stdio.h>
#include "coreLib.h"
#include "orbitLib.h"

typedef std::pair<double, double> Coordinates;
typedef std::pair<int, int> MapCoordinates;

class Sky
{
public:
	Sky();
	~Sky();

	void evaluate();
	void PrintPosVel(const cSatellite& sat);
	Coordinates eciToGeodetic(const cEci &eciCoords) const;
	MapCoordinates getCoordinatesFromGPSData(Coordinates coordinates);
private:
	const double pi = atan(1) * 4;
};

