#include "SOKO_GFX.h"
#include <stdint.h>
#include <fileioc.h>

#define SOKO_GFX_HEADER_SIZE 0

unsigned char *SOKO_GFX_appvar[4] =
{
    (unsigned char*)0,
    (unsigned char*)40,
    (unsigned char*)298,
    (unsigned char*)556,
};

unsigned char *tileset_tiles_data[3] =
{
    (unsigned char*)0,
    (unsigned char*)258,
    (unsigned char*)516,
};

unsigned char SOKO_GFX_init(void)
{
    uintptr_t data;
    unsigned int i;
    uint8_t appvar;

    appvar = ti_Open("SOKO_GFX", "r");
    if (appvar == 0)
    {
        return 0;
    }

    data = (uintptr_t)ti_GetDataPtr(appvar) - (uintptr_t)SOKO_GFX_appvar[0] + SOKO_GFX_HEADER_SIZE;
    for (i = 0; i < 4; i++)
    {
        SOKO_GFX_appvar[i] += data;
    }

    ti_Close(appvar);

    data = (unsigned int)SOKO_GFX_appvar[3] - (unsigned int)tileset_tiles_data[0];
    for (i = 0; i < tileset_tiles_num; i++)
    {
        tileset_tiles_data[i] += data;
    }

    return 1;
}

