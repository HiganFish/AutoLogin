#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <windows.h>
#include <locale.h>
#include <vector>
#include <string>
#include <Winerror.h>
#include "Utils.h"

extern std::string error_msg;

bool Utils::EnableBoot(const std::string& file_path)
{
	/*
	这里添加一个额外的 空格零 是为了区分程序开机启动运行 还是手动运行
	*/
    std::wstring path = ToWstring(file_path + " 0");
    HKEY hkey = NULL;
    LONG create_result = RegCreateKey(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", &hkey);
    LONG status = RegSetValueEx(hkey, L"AutoLogin", 0, REG_SZ, (BYTE*)path.c_str(), (path.size() + 1) * sizeof(wchar_t));

    error_msg = "Windows错误代码: " + std::to_string(create_result) + " " + std::to_string(status);

    return create_result == ERROR_SUCCESS && status == ERROR_SUCCESS;
}

bool Utils::DisableBoot()
{
    HKEY registryKey = NULL;
    LONG result_open = RegOpenKeyEx(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_ALL_ACCESS, &registryKey);
    LONG result_delete = RegDeleteValue(registryKey, L"AutoLogin");

    error_msg = "Windows错误代码: " + std::to_string(result_open) + " " + std::to_string(result_delete);

    return result_open == ERROR_SUCCESS && result_delete == ERROR_SUCCESS;
}

std::wstring Utils::ToWstring(std::string const& src)
{
    setlocale(LC_CTYPE, "zh_CN");

    size_t const wcs_len = mbstowcs(NULL, src.c_str(), 0);
    std::vector<wchar_t> tmp(wcs_len + 1);
    mbstowcs(&tmp[0], src.c_str(), src.size());

    std::wstring result;

    result.assign(tmp.begin(), tmp.end() - 1);

    return result;
}

std::string Utils::ToString(std::wstring const& src)
{
    setlocale(LC_CTYPE, "");

    size_t const mbs_len = wcstombs(NULL, src.c_str(), 0);
    std::vector<char> tmp(mbs_len + 1);
    wcstombs(&tmp[0], src.c_str(), tmp.size());

    std::string result;

    result.assign(tmp.begin(), tmp.end() - 1);

    return result;
}