#include "stdexcept"
#include "iostream"

#include "Application.h"

int main()
{
    try
    {
        Application app;
        app.Run();
    }
    catch (std::runtime_error &err)
    {
        std::cerr << "[ERROR]: " << err.what() << std::endl;
        return 1;
    }
}