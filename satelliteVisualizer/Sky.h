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

	void processTLE();
	vector<MapCoordinates> GetSATPos(int timeDelta);

private:
	const double pi = atan(1) * 4;
	vector<cSatellite> satellites;
	
	MapCoordinates getCoordinatesFromGPSData(Coordinates coordinates);
	Coordinates eciToGeodetic(const cEci &eciCoords) const;
};

