#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>

#include "window.h"


int main(int argc, char *argv[]) {
    Window window = {
        .width = 800,
        .height = 600,
        .renderer = NULL,
        .window = NULL
    };

    initWindow(&window);
    runWindow(&window);
    closeWindow(&window);
    
    return 0;
}