#include <stdio.h>
#include "relational.h"

int GRT(int x, int y){/*Greater than or equal To*/
    if(x>y)
        return x;
    else
        return y;
}
int LST(int x, int y){/*Lesser than or equal To*/
    if(x<y)
        return x;
    else
        return y;
}

int LSE(int x, int y){/*Lesser than or equal To*/
    if(x<=y)
        return x;
    else
        return y;
}

int GRE(int x, int y){/*Greater than or equal to*/
    if(x>=y)
        return x;
    else
        return y;
}

int EQ(int x, int y){/*Greater than or equal to*/
    if(x==y)
        return 1;
    else
        return 0;
}