#include "VGCVirtualGameConsole.h"
#include "PathEvolver.h"
//------------------------------------------------------------------------------
using namespace std;
//------------------------------------------------------------------------------
int VGCMain(const VGCStringVector &arguments)
{
	const string applicationName = "Obstacle Field";
	const int DISPLAY_WIDTH = 1280;
	const int DISPLAY_HEIGHT = 720;
	VGCVirtualGameConsole::initialize(applicationName, DISPLAY_WIDTH, DISPLAY_HEIGHT);
	
	VGCVector start(0.0,0.0);
	VGCVector finish(500.0, 500.0);

	PathEvolver pathEvolver(start, finish);

	while(VGCVirtualGameConsole::beginLoop())
	{

		pathEvolver.EvolveGeneration(3);
		if(VGCDisplay::beginFrame())
		{
			const VGCColor backgroundColor = VGCColor(255, 255, 255, 255);
			VGCDisplay::clear(backgroundColor);

			pathEvolver.Paint();
		
			VGCDisplay::endFrame();
		}
		VGCVirtualGameConsole::endLoop();
	}
	VGCVirtualGameConsole::finalize();
	return 0;
}
//------------------------------------------------------------------------------