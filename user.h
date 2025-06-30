#ifndef USER_H
#define USER_H
#include <string>

class User
{
public:
    unsigned int id = 0;
    std::string username;
    std::string password;

    bool operator==(const User& other) const;
};

#endif // USER_H
