#include "app/App.h"

int main(int argc, char *argv[])
{
    return App::getInstance()->execute(argc, argv);
}