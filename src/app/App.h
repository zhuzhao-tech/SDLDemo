#ifndef __APP_H__
#define __APP_H__

#include "../utils/defs.h"

class App
{
private:
    static App instance;

    GLFWwindow *window;

public:
    App() {}

    ~App();

public:
    static App *getInstance();

    int execute(int argc, char *argv[]);

public:
    void processInput();        
    
};

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

#endif