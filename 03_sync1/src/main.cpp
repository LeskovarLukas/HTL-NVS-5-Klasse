#include <iostream>
#include <thread>

using namespace std;

//int main(int argc, char* argv[]) {
int main() {
    thread t{[]{ cout << "Hello"; }};
    t.join();
    cout << " world!" << endl;
    return 0;
}
