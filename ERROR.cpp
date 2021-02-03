#ifndef error_cpp

#define error_cpp

#include<bits/stdc++.h>

using namespace std;


class Error
{

private:
    string message;
public:
    Error(string messsage)
    {

        this->message= message;
    }
    string getMessage() const
    {

        return this->message;
    }
};

class IOError : public Error
{
public:
    IOError():
        Error("I/O Error could not open or process file make sure 'vehicle.txt' , 'tripe.txt' and 'user.txt' file exists in this directory")
        {

        };


};
class MemoryError: public Error
{

public:
    MemoryError() : Error("System out of memory") {};
};
#endif // error_cpp

