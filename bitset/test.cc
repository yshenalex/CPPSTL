#include "mystl_bitset.hpp"
#include <iostream>
using namespace mystl;
using namespace std;
int main()
{
    bitset<20> bits;
    bits.set(0);
    bits.set(3);
    bits.set(9);
    bits.set(17);
    bits.set(19);
    bits.reset(19);

    cout << "count: " << bits.count() << endl;
    cout << "size: " << bits.size() << endl;
    cout << "toString(): " << bits.toString() << endl;
    return 0;
}