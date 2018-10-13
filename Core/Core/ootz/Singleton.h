#pragma once

#include <cassert>
#include <memory>

#include <boost/noncopyable.hpp>

#include <iostream>

namespace ootz
{

template<typename T>
class Singleton : private boost::noncopyable
{
public:
    static T& GetInstance()
    {
        static T _instance(Token{});
        return _instance;
    }

protected:

    // this token is used by constructor of the inherited class.
    struct Token {};

    Singleton() {};
};

class Derived final : public Singleton<Derived>
{
public:
    Derived(Token) 
    {
        std::cout << "constructor\n";
    };


};

} // namespace ootz