#pragma once

#ifdef _WIN32
#include "glad/glad.h"
#elif _WIN64
#include "glad/glad.h"
#elif __CYGWIN__
#include "glad/glad.h"
#elif __ANDROID__
#include <GLES3/gl3.h>
#include <GLES2/gl2ext.h>
#include <GLES3/gl31.h>
#include <GLES3/gl32.h>
#include <GLES3/gl3ext.h>
#elif __ARM_ARCH //for 树梅派
#include "glad/glades.h"
#elif __linux__
#include "glad/glad.h"
#elif _UNIX
#include "glad/glad.h"
#elif __APPLE__
#include "glad/glad.h"
#endif


// #ifndef _GLAD_
// #define _GLAD_
// #include "glad/glad.h"
// #endif





