#include "Sky.h"



Sky::Sky()
{
}


Sky::~Sky()
{
}


void Sky::evaluate()
{

		string str1 = "SGP4 Test";
		string str2 = "1 88888U          80275.98708465  .00073094  13844-3  66816-4 0     8";
		string str3 = "2 88888  72.8435 115.9689 0086731  52.6988 110.5714 16.05824518   105";

		cTle tleSGP4(str1, str2, str3);

		cSatellite satSGP4(tleSGP4);

		PrintPosVel(satSGP4);

		printf("Example output:\n");

		cEciTime eciSDP4 = satSGP4.PositionEci(90.0);

		system("pause");
	}

	/////////////////////////////////////////////////////////////////////////////
	// Helper function to output position and velocity information
	void Sky::PrintPosVel(const cSatellite& sat)
	{
		vector<cEci> vecPos;

		// Calculate the position and velocity of the satellite for various times.
		// mpe = "minutes past epoch"
		for (int mpe = 0; mpe <= (360 * 4); mpe += 360)
		{
			// Get the position of the satellite at time "mpe"
			cEciTime eci = sat.PositionEci(mpe);

			// Push the coordinates object onto the end of the vector.
			vecPos.push_back(eci);
		}

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


