#include <stdlib.h>

int myAssert(int val)
{
    if (val)
    {
        return 0;
    } else {
        exit(1);
    }
}
