#ifndef TS_NUMBER_H
#define TS_NUMBER_H

template <class T>
class TS_Number
{
    public:
        TS_Number<T>(); 
    private:
        T number = 0;  
};


template <class T>
TS_Number<T>::TS_Number()
{

}

#endif
