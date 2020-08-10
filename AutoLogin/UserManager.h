#pragma once

#include <string>

struct UserInfo
{
    std::string username;
    std::string password;
};

class UserManager
{
public:
    UserManager(const std::string& file_name);
    ~UserManager();

    bool ReadUserInfo(UserInfo* info);

    bool WriteUserInfo(UserInfo* info);

    bool OperateChangeUserInfo(UserInfo* info);

private:

    std::string file_name_;
};

