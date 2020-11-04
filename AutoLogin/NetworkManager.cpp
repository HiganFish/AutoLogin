#include <map>
#include <iostream>
#include "NetworkManager.h"

const std::string LOGIN_URL_PREFIX = "http://10.2.5.251:801/eportal/?c=Portal&a=login&login_method=1";
const std::string LOGIN_URL_USERNAME = "&user_account=";
const std::string LOGIN_URL_PASSWORD = "&user_password=";

const std::string LOGOUT_URL = "http://10.2.5.251:801/eportal/?c=Portal&a=logout";

extern std::string error_msg;

bool NetworkManager::Login(const std::string& username, const std::string& password)
{
    std::string url = LOGIN_URL_PREFIX + LOGIN_URL_USERNAME + username + LOGIN_URL_PASSWORD + password;

    std::string login_result = curl_.GetUrl(url);

    if (login_result.empty())
    {
        error_msg = "�޷����ӵ�10.2.5.251 ��ȷ������ѧУ����";
        
        return false;
    }

    if (login_result == R"(({"result":"0","msg":"","ret_code":"2"}))" || 
        login_result== R"(({"result":"1","msg":"认证成功"}))")
    {
        return true;
    }
    else if (login_result == R"(({"result":"0","msg":"UmFkOkxpbWl0IFVzZXJzIEVycg==","ret_code":"1"}))")
    {
        error_msg = "�û�����";
        return false;
    }
    else if (login_result == R"(({"result":"0","msg":"dXNlcmlkIGVycm9yMg==","ret_code":"1"}))")
    {
        error_msg = "�����˺����������Ӫ��";
    }
    else
    {
        error_msg = login_result;
        return false;
    }
}

bool NetworkManager::Logout()
{
    std::string logout_result = curl_.GetUrl(LOGOUT_URL);
    if (logout_result.empty())
    {
        error_msg = "�޷����ӵ�10.2.5.251 ��ȷ������ѧУ����";
        
        return false;
    }

    if (logout_result == R"(({"result":"1","msg":"注销成功"}))")
    {
        return true;
    }
    else 
    {
        error_msg = logout_result;
        return false;
    }
}
