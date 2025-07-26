#ifndef TS_STRING_H
#define TS_STRING_H
#include <string>
#include <mutex>

class TS_String
{
    public:
        TS_String();
        void setString(const std::string string);
        std::string getString();
        virtual ~TS_String();
   private:
        std::string m_string;
        std::mutex mutex;
};

#endif

