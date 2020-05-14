/* This file is part of X2C. http://x2c.lcm.at/                                                                       */

/* Date:  2020-05-13 20:47                                                                                            */

/* X2C-Version: 6.2.1908                                                                                              */
/* X2C-Edition: Free                                                                                                  */

#include "RamTable.h"

int16 RamTable_int16[5];

static const int16 RamTable_int16_init[5] = {0,0,0,0,0}; 

void initRamTables()
{
    uint16 i;

    for (i = 0; i < 5; i++)
    {
        RamTable_int16[i] = RamTable_int16_init[i];
    }
}
