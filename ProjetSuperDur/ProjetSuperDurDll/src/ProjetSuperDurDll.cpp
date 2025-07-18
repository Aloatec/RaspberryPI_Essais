// ProjetSuperDur.cpp : définit le point d'entrée de l'application.
//

#include "ProjetSuperDurDll.h"
// #include <boost/test/unit_test.hpp>

#include <boost/locale.hpp>

using namespace std;
using namespace boost::locale;

int test()
{
    cout << "Hello CMake." << '\n';
    cout << "test" << '\n';

    generator gen;
    gen.add_messages_path("locales");
    gen.add_messages_domain("ProjetSuperDurDll");
    // Generate locales and imbue them to iostream

    locale::global(gen("fr"));
    cout.imbue(locale());

    // Test traduction simple
    std::cout << translate("Hello") << '\n';

    // Test avec variable et format
    const int nNombreObjets = 3;
    std::cout << format(ngettext("{1} file", "{1} files", nNombreObjets)) % nNombreObjets << '\n';
    std::cout << format(translate("You have {1} apple.")) % nNombreObjets << '\n';

    // Test du pluriel

    return 0;
}

void create_log()
{
}

int MYLIBRARY_API addition(int nX1, int nX2)
{
    return nX1 + nX2;
}
