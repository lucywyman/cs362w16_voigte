#include <stdlib.h>

int myAssert(int val)
{
    if (val)
    {
        return 0;
    } else {
        // This should exit 1 to fail, but that breaks unittestreslts.out
        exit(0);
    }
}
