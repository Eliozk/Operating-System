#include <iostream>

void infiniteRecurs(int counter)
{
    counter += 1;
    infiniteRecurs(counter);
}

int main()
{
    int counter = 0;
    infiniteRecurs(counter);
    return 0;
}