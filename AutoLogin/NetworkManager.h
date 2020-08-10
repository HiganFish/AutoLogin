#pragma once
#include <string>
#include "Curl.h"

/*
���������
*/
class NetworkManager
{
public:
    NetworkManager() = default;
    ~NetworkManager() = default;

    /*
    У԰����¼���û�����һ�� ��ѧ��+ @ + ��������д
    */
    bool Login(const std::string& username, const std::string& password);

    bool Logout();

private:
    Curl curl_;
};

