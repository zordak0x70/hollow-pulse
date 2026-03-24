#ifndef RAYLIB_HELPER_H
#define RAYLIB_HELPER_H


#include "raylib.h"
#include "sv_helper.h"

/**
 * @brief This function draws a sv directly using TextFormat
 * @warning TextFormat supports only medium-sized strings, so dont use this
 *          function for very long strings!
 */
static inline void DrawSV(sv *s, int posX, int posY, int fontSize, Color color) {
    DrawText(TextFormat(SV_FMT, SV_ARG(s)), posX, posY, fontSize, color);
}


#endif // RAYLIB_HELPER_H
