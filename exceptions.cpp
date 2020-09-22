#include "exceptions.hpp"

namespace exceptions{
    void serverErrorCheck(const int returnValue, int const fileDescriptor){
        if(returnValue < 0){
            //throw exceptoins
            std::cout << "error!" << std::endl;
            close(fileDescriptor);
        }
    }
}




