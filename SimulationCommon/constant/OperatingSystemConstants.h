#pragma once

 

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    #define WINDOWS
#endif

#if __APPLE__
    #define APPLE
#endif