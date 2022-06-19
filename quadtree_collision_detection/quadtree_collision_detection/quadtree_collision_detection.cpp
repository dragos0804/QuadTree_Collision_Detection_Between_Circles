#define OLC_PGE_APPLICATION
#include "application.h"

int main()
{
    application demo;
    if (demo.Construct(433, 433, 2, 2))
        demo.Start();

    return 0;
}
