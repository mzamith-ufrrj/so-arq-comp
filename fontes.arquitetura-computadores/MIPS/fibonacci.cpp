#include <iostream>
int fib (int a, int b, int p){
    if (p == 1) 
        return (a + b);
    else
        return fib(b, a+b, p - 1);
}


int main(int ac, char **av){
    int a = 0,
        b = 1;

    std::cout << fib(0, 1, 10) << std::endl;
    return 0;
}