#include <iostream>
#include <string>
#include <set>
#include "node.h"

int main()
{
    Node t1;
    Node t2(5, 3.9, 5.0, 5);
    t1.setPosition(1.0, 1.0);
    t1.addNeighbour(3);
    t1.addNeighbour(1);
    t1.addNeighbour(2);

    t1.setCurrentState(DOMINATOR);
    t1.setReceivedState(DOMINATEE);

    t2.addNeighbour(5);
    t2.addNeighbour(4);
    t2.addNeighbour(1);

    t1.printNode();
    t2.printNode();

    std::cout << "hello,world" << std::endl;

    return 0;

}
