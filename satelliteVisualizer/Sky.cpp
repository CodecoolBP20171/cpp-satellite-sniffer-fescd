#include "Sky.h"
#include <iostream>

Sky::Sky()
{
}


Sky::~Sky()
{
}


void Sky::evaluate()
{
	/*
		string str1 = "SGP4 Test";
		string str2 = "1 88888U          80275.98708465  .00073094  13844-3  66816-4 0     8";
		string str3 = "2 88888  72.8435 115.9689 0086731  52.6988 110.5714 16.05824518   105";
*/
		string str1 = "ISS";
		string str2 = "1 25544U 98067A   17340.55265046  .00003773  00000-0  64291-4 0  9994";
		string str3 = "2 25544  51.6431 259.0525 0003227 200.2075 144.0367 15.54093333 88557";
					   

		cTle tleSGP4(str1, str2, str3);

		cSatellite satSGP4(tleSGP4);

		for (int i = 0; i < 30*48; i = i + 30) {
			cEciTime eci = satSGP4.PositionEci(i);
			Coordinates coordinates = eciToGeodetic(eci);
			MapCoordinates mapcoordinates = getCoordinatesFromGPSData(coordinates);
			Coordinates budapest;
			budapest.first = 47.497912;
			budapest.second = 19.040235;
			

			MapCoordinates bpmapcoordinates = getCoordinatesFromGPSData(budapest);

			std::cout << "ECI_X: " << eci.Position().m_x << " ECI_Y: " << eci.Position().m_y << " ECI_Z: " << eci.Position().m_z << std::endl;

			std::cout << "latitude: " << coordinates.first << " longitude: " << coordinates.second << std::endl;

			std::cout << "MAP_X: " << mapcoordinates.first << " MAP_Y: " << mapcoordinates.second << std::endl;

			//std::cout << "BUDAPEST_MAP_X: " << bpmapcoordinates.first << " BUDAPEST_MAP_Y: " << bpmapcoordinates.second << std::endl;

		}
		
		//PrintPosVel(satSGP4);

		printf("Example output:\n");

		cEciTime eciSDP4 = satSGP4.PositionEci(90.0);

		system("pause");
	}

	/////////////////////////////////////////////////////////////////////////////
	// Helper function to output position and velocity information
	void Sky::PrintPosVel(const cSatellite& sat)
	{
		vector<cEci> vecPos;
		/*
		// Calculate the position and velocity of the satellite for various times.
		// mpe = "minutes past epoch"
		for (int mpe = 0; mpe <= (360 * 4); mpe += 360)
		{
			// Get the position of the satellite at time "mpe"
			cEciTime eci = sat.PositionEci(mpe);

			// Push the coordinates object onto the end of the vector.
			vecPos.push_back(eci);
		}
		*/
		// Print TLE data
		printf("%s\n", sat.Name().c_str());
		printf("%s\n", sat.Orbit().TleLine1().c_str());
		printf("%s\n\n", sat.Orbit().TleLine2().c_str());

		// Header
		printf("  TSINCE            X                Y                Z\n\n");

		// Iterate over each of the ECI position objects pushed onto the
		// position vector, above, printing the ECI position information
		// as we go.
		for (unsigned int i = 0; i < vecPos.size(); i++)
		{
			printf("%8d.00  %16.8f %16.8f %16.8f\n",
				i * 360,
				vecPos[i].Position().m_x,
				vecPos[i].Position().m_y,
				vecPos[i].Position().m_z);
		}

		printf("\n                    XDOT             YDOT             ZDOT\n\n");

		// Iterate over each of the ECI position objects in the position
		// vector again, but this time print the velocity information.
		for (unsigned int i = 0; i < vecPos.size(); i++)
		{
			printf("             %16.8f %16.8f %16.8f\n",
				vecPos[i].Velocity().m_x,
				vecPos[i].Velocity().m_y,
				vecPos[i].Velocity().m_z);
		}

		printf("\n");
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
		float mapWidth = 823;
		float mapHeight = 698;
		//float mapWidth = 2058;
		//float mapHeight = 1746;

		int x = (coordinates.second + 180) * (mapWidth / 360);
		float latRad = coordinates.first * pi / 180;
		float mercN = log(tan((pi / 4) + (latRad / 2)));
		int y = (mapHeight / 2) - (mapWidth*mercN / (2 * pi));
		MapCoordinates result;
		result.first = x;
		result.second = y;
		return result;
	}

