#ifndef TS_NUMBER_H
#define TS_NUMBER_H
#include <mutex>

template <class T>
class TS_Number
{
    public:
        TS_Number(); 
        TS_Number(const T &number); 
        T getNumber() const;
        T setNumber(const T &number);
        TS_Number<T> operator = (const TS_Number &number);
        template <class N>
        TS_Number<T> operator = (const N &number);
        template <class N>
        TS_Number<T> operator + (const N &number);
        template <class N>
        TS_Number<T> operator - (const N &number);
    private:
        T m_number = 0;  
        std::mutex mutex;
};


template <class T>
TS_Number<T>::TS_Number()
{

}

template <class T>
TS_Number<T>::TS_Number(const T &number)
{
    std::lock_guard<std::mutex> lock(mutex);
    m_number = number;
}


template <class T>
T TS_Number<T>::getNumber() const
{
    return m_number;
}


template <class T>
T TS_Number<T>::setNumber(const T &number)
{
    std::lock_guard<std::mutex> lock(mutex);
    m_number = number;
}

template <class T>
TS_Number<T> TS_Number<T>::operator = (const TS_Number &number)
{
    std::lock_guard<std::mutex> lock(mutex);
    return m_number = number.m_number;
}

template<class T>
template<class N>
TS_Number<T> TS_Number<T>::operator = (const N &number)
{
    std::lock_guard<std::mutex> lock(mutex);
    if(this != &number)
        m_number = number; 

    return m_number;
}

template<class T>
template<class N>
TS_Number<T> TS_Number<T>::operator + (const N &number)
{
    std::lock_guard<std::mutex> lock(mutex);
    return m_number + number; 
}

template<class T>
template<class N>
TS_Number<T> TS_Number<T>::operator - (const N &number)
{
    std::lock_guard<std::mutex> lock(mutex);
    return m_number - number;
}

#endif
