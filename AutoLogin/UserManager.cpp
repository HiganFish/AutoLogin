#define _CRT_SECURE_NO_WARNINGS

#include "UserManager.h"
#include <iostream>

extern std::string error_msg;

UserManager::UserManager(const std::string& file_name):
    file_name_(file_name)
{
    
}

UserManager::~UserManager()
{
    
}

bool UserManager::ReadUserInfo(UserInfo* info)
{
    if (!info)
    {
        return false;
    }

    FILE* input_file_ = nullptr;
    int result = fopen_s(&input_file_, file_name_.c_str(), "r");
    if (!input_file_)
    {
        error_msg = strerror(result);
        return false;
    }

    char buffer[1024]{};
    size_t len = fread(buffer, 1, sizeof buffer, input_file_);

    const char* username_end = strchr(buffer, ' ');
    if (!username_end)
    {
        return false;
    }
    info->username = std::string(buffer, username_end - buffer);
    info->password = std::string(username_end + 1);

    fclose(input_file_);
    return !info->password.empty();
}

bool UserManager::WriteUserInfo(UserInfo* info)
{
    if (!info)
    {
        return false;
    }

    FILE* output_file = nullptr;
    int result = fopen_s(&output_file, file_name_.c_str(), "w");
    if (!output_file)
    {
        error_msg = strerror(result);
        return false;
    }

    std::string output = info->username + ' ' + info->password;
    fwrite(output.data(), 1, output.length(), output_file);

    fclose(output_file);

    return true;
}

std::string g_int_yys[] = { "@unicom", "@telecom", "@cmcc" };

bool UserManager::OperateChangeUserInfo(UserInfo* userinfo)
{
    if (!userinfo)
    {
        return false;
    }

    std::cout << "输入用户名: \r\n";
    std::cin >> userinfo->username;

    std::cout << "输入密码: \r\n";
    std::cin >> userinfo->password;

    std::cout << "输入运营商: 0-联通 1-电信 3-移动\r\n";
    int yys_sub;
    std::cin >> yys_sub;

    if (userinfo->username.empty() || userinfo->password.empty() || yys_sub < 0 || yys_sub > 3)
    {
        return false;
    }

    userinfo->username += g_int_yys[yys_sub];

    bool result = WriteUserInfo(userinfo);
    return result;
}