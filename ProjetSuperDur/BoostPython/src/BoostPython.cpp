#include "BoostPython.h"
#include "pch.h"

using namespace boost::python;

void python_run()
{
    try
    {
        std::cout << "Running Python code..." << std::endl;

        Py_SetPythonHome(L"C:\\Users\\paulM\\AppData\\Local\\Programs\\Python\\Python311");
        Py_Initialize();
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
            std::string k = extract<std::string>(keys[i]);
            std::cout << " - " << k << std::endl;
        }

        if (extract<bool>(global.contains("faire_truc")))
        {
            object f = global["faire_truc"];
            int result = extract<int>(f(10, 20));
            std::cout << "[C++] Résultat : " << result << std::endl;
        }
        else
        {
            std::cerr << "[C++] 'faire_truc' introuvable dans le namespace Python\n";
        }

        if (extract<bool>(global.contains("Calculatrice")))
        {
            object py_class = global["Calculatrice"];
            object instance = py_class(10);

            object res = instance.attr("ajoute")(32); // équivaut à instance.ajoute(32)

            int value = extract<int>(res);
            std::cout << "[C++] Calculatrice.ajoute(32) = " << value << std::endl;

            int base_val = extract<int>(instance.attr("base"));
            std::cout << "[C++] Attribut base = " << base_val << std::endl;
        }

        std::cout << "Python code executed successfully." << std::endl;
    }
    catch (const boost::python::error_already_set &)
    {
        PyErr_Print(); // ← ça affichera l'erreur Python dans ta console
    }
}
