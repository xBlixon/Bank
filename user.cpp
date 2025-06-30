#include "user.h"

bool User::operator==(const User& other) const {
    return id == other.id && username == other.username && password == other.password;
}
