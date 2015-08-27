#ifndef SINGLETON_H
#define SINGLETON_H

#include <stdlib.h>

template<class T>
class Singleton
{
public:
    static T *get()
    {
        if (_instance == NULL)
        {
            _instance = new T;
        }
        return (_instance);
    }

private:
    static T *_instance;
};

template<class T>
T *Singleton<T>::_instance = NULL;

#endif // SINGLETON_H
