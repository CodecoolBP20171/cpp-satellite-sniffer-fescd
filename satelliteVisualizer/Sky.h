#pragma once

#include "stdafx.h"
#include <stdio.h>
#include "coreLib.h"
#include "orbitLib.h"
#include <memory>
#include "Graphics.h"

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
	Coordinates eciToGeodeticTEST(double x, double y, double z);
	MapCoordinates getCoordinatesFromGPSData(Coordinates coordinates);
	void setGraphics(std::shared_ptr<Graphics> graphics);
private:
	const double pi = atan(1) * 4;
	std::weak_ptr<Graphics> graphics;
};

