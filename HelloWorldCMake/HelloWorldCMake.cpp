// HelloWorldCMake.cpp : définit le point d'entrée de l'application.
//

#include "HelloWorldCMake.h"
#include <plog/Log.h>
#include <plog/Initializers/RollingFileInitializer.h>

using namespace std;

int main()
{
	plog::init(plog::debug, "Hello.txt");
	
	PLOGD << "Hello log!";

	cout << "Hello Aloatec" << endl;
    printSomething();
	return 0;
}
