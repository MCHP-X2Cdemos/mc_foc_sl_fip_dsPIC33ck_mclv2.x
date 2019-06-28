/* This file is part of X2C. http://x2c.lcm.at/                                                                       */

/* Date:  2019-06-26 09:50                                                                                            */

/* X2C-Version: 6.1.1707                                                                                              */
/* X2C-Edition: Free                                                                                                  */

#include "RamTable.h"

int16 RamTable_int16[6];

static const int16 RamTable_int16_init[6] = {0,0,0,0,0,0}; 

void initRamTables()
{
    uint16 i;

    for (i = 0; i < 6; i++)
    {
        RamTable_int16[i] = RamTable_int16_init[i];
    }
}