#include <dlfcn.h>
#include <iostream>
#include <meta>

template <typename T>
T reflexym_loader(void* handle)
{
    T api{};

    constexpr auto ctx = std::meta::access_context::unchecked();
    template for (constexpr auto field : define_static_array(nonstatic_data_members_of(^^T, ctx)))
    {
        constexpr auto symbol_name = identifier_of(field);
        const auto sym = dlsym(handle, symbol_name.data());
        api.[:field:] = reinterpret_cast<typename[:type_of(field):]>(sym);
        if (!api.[:field:])
        {
            std::cerr << "Error: symbol " << symbol_name << " not found!\n";
        }
    }

    return api;
}
