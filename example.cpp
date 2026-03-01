#include "reflexym.h"

#include <dlfcn.h>
#include <iostream>
#include <stdexcept>
#include <string>

struct api_t {
    double (*cos)(double);
    double (*sin)(double);
    void (*sincos)(double, double*, double*);
    const char* (*zlibVersion)(void);
};

int main()
{
    try
    {
        const auto lib_name = "libz.so.1";
        void* handle = dlopen(lib_name, RTLD_LAZY);
        if (!handle)
        {
            throw std::runtime_error("Error: library " + std::string(lib_name) + " not found");
        }

        const auto compress_api = reflexym_loader<api_t>(handle);
        if (compress_api.zlibVersion)
        {
            std::cout << compress_api.zlibVersion() << "\n";
        }
        dlclose(handle);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    try
    {
        const auto lib_name = "libm.so.6";
        void* handle = dlopen(lib_name, RTLD_LAZY);
        if (!handle)
        {
            throw std::runtime_error("Error: library " + std::string(lib_name) + " not found");
        }

        const auto math_api = reflexym_loader<api_t>(handle);
        if (math_api.sin)
        {
            std::cout << math_api.sin(0.0) << "\n";
        }
        if (math_api.cos)
        {
            std::cout << math_api.cos(0.0) <<  "\n";
        }
        if (math_api.sincos)
        {
            double s = 0;
            double c = 0;
            math_api.sincos(0.0, &s, &c);
            std::cout << s << " " << c << " " <<  "\n";
        }
        dlclose(handle);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
