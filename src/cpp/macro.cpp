#include <iostream>

#define S(a) #a
#define N b
#define SS(a) S(a)

int main(void) {
    std::cout << S(N) << std::endl;
    std::cout << std::endl;
    std::cout << SS(N) << std::endl;
}
