#include <iostream>
#include "determinant.h"

int main()
{
    Determinant det;
    std::cin>>det;
    std::cout<<std::endl<<det<<std::endl;
    std::cout<<"sum: "<<det.get_sum()<<std::endl;

    return 0;
}

