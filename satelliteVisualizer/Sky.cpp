#include "Sky.h"
#include <iostream>
#include <fstream>

Sky::Sky() {
	processTLE();
}

Sky::~Sky() {}


void Sky::processTLE()
{
	ifstream file;
	file.open("tle.txt");

	if (!file) { 
		cout << "Cannot open input file"; 
	}
	
	std::string line;

	while (std::getline(file, line))
	{
		string str1 = line;
		std::getline(file, line);
		string str2 = line;
		std::getline(file, line);
		string str3 = line;

		cTle tle(str1, str2, str3);
		cSatellite sat(tle);
		satellites.push_back(sat);
	}
}

	vector<MapCoordinates> Sky::GetSATPos(int timeDelta)
	{
		vector<MapCoordinates> mapcoordinates;
		auto max = satellites.size();
		for (auto i = 0; i < max; i++) {
			
			cEciTime eci = satellites[i].PositionEci(timeDelta);
			Coordinates coordinates = eciToGeodetic(eci);
			MapCoordinates coord = getCoordinatesFromGPSData(coordinates);
			mapcoordinates.push_back(coord);
		}
		return mapcoordinates;
	}

	
	
	Coordinates Sky::eciToGeodetic(const cEci &eciCoords) const {
		Coordinates result;
		const double a = 6378.137;
		const double b = 6356.7523142;
		const double R = sqrt((eciCoords.Position().m_x * eciCoords.Position().m_x) + (eciCoords.Position().m_y * eciCoords.Position().m_y));
		const double f = (a - b) / a;
		const double e2 = ((2 * f) - (f * f));
		double longitude = atan2(eciCoords.Position().m_y, eciCoords.Position().m_x);
		const double kmax = 20;
		auto k = 0;
		auto latitude = atan2(
			eciCoords.Position().m_z,
			sqrt((eciCoords.Position().m_x * eciCoords.Position().m_x) + (eciCoords.Position().m_y * eciCoords.Position().m_y)));
		double C;
		while (k < kmax) {
			C = 1 / sqrt(1 - (e2 * (sin(latitude) * sin(latitude))));
			latitude = atan2(eciCoords.Position().m_z + (a * C * e2 * sin(latitude)), R);
			k += 1;
		}
		const double height = (R / cos(latitude)) - (a * C);
		longitude = longitude * 180 / pi;
		latitude = latitude * 180 / pi;
		result.first = latitude;
		result.second = longitude;
		//return { longitude, latitude, height };
		return result;
	}

	MapCoordinates Sky::getCoordinatesFromGPSData(Coordinates coordinates) {
		double mapWidth = 823;
		double mapHeight = 698;
		//float mapWidth = 2058;
		//float mapHeight = 1746;

		int x = (coordinates.second + 180) * (mapWidth / 360);
		double latRad = coordinates.first * pi / 180;
		double mercN = log(tan((pi / 4) + (latRad / 2)));
		int y = (mapHeight / 2) - (mapWidth*mercN / (2 * pi));
		MapCoordinates result;
		result.first = x;
		result.second = y;
		return result;
	}