#include "BoostPython.h"
#include "pch.h"

using namespace boost::python;

void initialize_python(const wchar_t *python_home)
{
    PyStatus status;
    PyConfig config;
    PyConfig_InitPythonConfig(&config);

    // Définir le chemin d'installation de Python
    status = PyConfig_SetString(&config, &config.home, python_home);
    if (PyStatus_Exception(status) != 0)
    {
        Py_ExitStatusException(status);
    }

    // Vous pouvez aussi configurer d'autres paramètres ici
    // config.isolated = 1;  // si vous voulez un mode isolé

    // Initialisation de l'interpréteur Python
    status = Py_InitializeFromConfig(&config);
    if (PyStatus_Exception(status) != 0)
    {
        Py_ExitStatusException(status);
    }

    PyConfig_Clear(&config); // nettoyage

}

void python_run()
{
    try
    {
        std::cout << "Running Python code..." << '\n';

        initialize_python(L"C:\\Users\\paulM\\AppData\\Local\\Programs\\Python\\Python311");
        object main_module = import("__main__");
        dict global = extract<boost::python::dict>(main_module.attr("__dict__"));

        exec("import sys; sys.path.append('.\\scripts')", global);

        exec("hello = open('hello.txt', 'w')\n"
             "hello.write('Hello world!')\n"
             "hello.close()",
             global);

        exec("import sys;\n"
             "print(sys.path)",
             global);

        exec_file("scripts/test.py", global, global);

        list keys = list(global.keys());
        std::cout << "Clés Python disponibles :\n";
        for (int i = 0; i < len(keys); ++i)
        {
            std::string strKey = extract<std::string>(keys[i]);
            std::cout << " - " << strKey << '\n';
        }

        if (extract<bool>(global.contains("faire_truc")))
        {
            object funcFaireTrue = global["faire_truc"];

            const int nNombreX1 = 10;
            const int nNombreX2 = 20;
            int result = extract<int>(funcFaireTrue(nNombreX1, nNombreX2));
            std::cout << "[C++] Résultat : " << result << '\n';
        }
        else
        {
            std::cerr << "[C++] 'faire_truc' introuvable dans le namespace Python\n";
        }

        if (extract<bool>(global.contains("Calculatrice")))
        {
            object py_class = global["Calculatrice"];

            const int nNombreInit = 10;
            object instance = py_class(nNombreInit);

            const int nNombreAdded = 32;

            object res = instance.attr("ajoute")(nNombreAdded); // équivaut à instance.ajoute(32)

            int value = extract<int>(res);
            std::cout << "[C++] Calculatrice.ajoute(32) = " << value << '\n';

            int base_val = extract<int>(instance.attr("base"));
            std::cout << "[C++] Attribut base = " << base_val << '\n';
        }

        std::cout << "Python code executed successfully." << '\n';
    }
    catch (const boost::python::error_already_set &)
    {
        PyErr_Print(); // ← ça affichera l'erreur Python dans ta console
    }
}
