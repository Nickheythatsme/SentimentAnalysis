#include <iostream>
#include <fstream>
using namespace std;

void exchange(const char *file)
{
    ofstream out(file);
    auto c_buff = cout.rdbuf(out.rdbuf());
    cout << "TESTING!" << endl;
    // This will segfault since out deletes its buff, then cout will try the same
}

int main(int argc, char *argv[])
{
    if (argc != 2) return 1;
    exchange(argv[1]);
}
