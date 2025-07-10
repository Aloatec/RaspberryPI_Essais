// ProjetSuperDur.cpp : définit le point d'entrée de l'application.
//

#include "ProjetSuperDurDll.h"
//#include <boost/test/unit_test.hpp>

#include <plog/log.h>
#include <plog/Initializers/RollingFileInitializer.h>

#include <boost/locale.hpp>


using namespace std;
using namespace boost::locale;

int test()
{
	cout << "Hello CMake." << endl;
    cout << "test" << endl;

    generator gen;
    gen.add_messages_path("locales");
    gen.add_messages_domain("ProjetSuperDurDll");
    // Generate locales and imbue them to iostream

    locale::global(gen("fr"));
    cout.imbue(locale());


    // Test traduction simple
    std::cout << translate("Hello") << std::endl;

    // Test avec variable et format
    int n = 3;
    std::cout << format(translate("You have {1} apple.")) % n << std::endl;

    // Test du pluriel
    std::cout << format(ngettext("{1} file", "{1} files", n)) % n << std::endl;

	return 0;
}

void create_log()
{
	plog::init(plog::debug, "Hello.txt");

	PLOGD << "Hello log!";
    PLOGI << "This is an info message.";
} 

int MYLIBRARY_API addition(int x1, int x2)
{
	return x1 + x2;
}
