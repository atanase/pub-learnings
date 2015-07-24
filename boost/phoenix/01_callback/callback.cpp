#include <iostream>
#include <boost/phoenix/core.hpp>

template<typename F>
void print(F f)
{
    std::cout << f() << std::endl;
}

int main()
{
    using boost::phoenix::val;

    print( val(3) );
    print( val("Hello, World!") );
    std::cout << val(3)() << std::endl;

    return 0;
}

