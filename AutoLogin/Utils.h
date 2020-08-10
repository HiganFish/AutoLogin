#pragma once
class Utils
{
public:

    /*
    通过修改注册表 设置开机启动
    */
    static bool EnableBoot(const std::string& file_path);

    /*
    删除注册表项 关闭开机启动
    */
    static bool DisableBoot();

    static std::wstring ToWstring(std::string const& src);
    static std::string ToString(std::wstring const& src);
};

