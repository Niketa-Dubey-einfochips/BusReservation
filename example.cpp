#include <iostream>
#include <functional>
using namespace std;

struct A
{
    int a = 10;
};

class Test1
{
    public:
        void registerCb( std::function<void(A&)> fn )
        {
            std::cout<<"callback"<<std::endl;
            A a;
            fn(a);
        }
};

class Test2
{
    public:
    Test2( Test1& t1 )
    {
        std::cout<<"registering"<<std::endl;
        t1.registerCb( std::bind(&Test2::testBind, this, std::placeholders::_1 ) );
    }
    public:
    void testBind( A& a )
    {
        std::cout<<"binding"<<std::endl;
        std::cout << a.a << std::endl;
    }   
};

int main()
{
    std::cout<<"main"<<std::endl;
    Test1 t1;
    Test2 t2(t1);
    return 0;
}