
#include "AbstactVM.hpp"

int main(int argc, char *argv[])
{
    AbstactVM abstactVm;

    try
    {
        abstactVm.launch(argc, argv);
    }
    catch (std::exception &e)
    {
        std::cout  <<  "\033[4;31m" << "Line " << abstactVm.getLine() << ": " <<  e.what() << "\033[0m" << std::endl;
    }
}
