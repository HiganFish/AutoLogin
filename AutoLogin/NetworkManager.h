#pragma once
#include <string>
#include "Curl.h"

/*
网络管理类
*/
class NetworkManager
{
public:
    NetworkManager() = default;
    ~NetworkManager() = default;

    /*
    校园网登录的用户名这一项 是学号+ @ + 运行商缩写
    */
    bool Login(const std::string& username, const std::string& password);

    bool Logout();

private:
    Curl curl_;
};

