#include <iostream>
#include "Utils.h"
#include "UserManager.h"
#include "NetworkManager.h"

const std::string USER_FILE = "C:\\Users\\Public\\Documents\\user.info";
std::string g_file_name;

UserInfo g_userinfo;
UserManager g_usermanager(USER_FILE);
NetworkManager g_network_manager;
bool g_running = true;
std::string error_msg = "未知错误";

enum class Operate
{
    LOGIN = 0,
    LOGOUT = 1,
    CHANGE_USER_INFO = 2,
    SET_BOOT = 3,
    UNSET_BOOT = 4,
    EXIT = 5
};

bool Process(Operate operate)
{
    bool result = true;
    error_msg = "未知错误";

    switch (operate)
    {
        case Operate::LOGIN:
        {
            result = g_network_manager.Login(g_userinfo.username, g_userinfo.password);
            if (result)
            {
                std::cout << "登录成功\r\n";
            }
            else
            {
                std::cout << "登录失败: " << error_msg << "\r\n";
            }
            break;
        }
        case Operate::LOGOUT:
        {
            result = g_network_manager.Logout();
            if (result)
            {
                std::cout << "注销成功\r\n";
            }
            else
            {
                std::cout << "注销失败: " << error_msg << "\r\n";
            }
            break;
        }
        case Operate::CHANGE_USER_INFO:
        {
            result = g_usermanager.OperateChangeUserInfo(&g_userinfo);
            if (result)
            {
                std::cout << "保存成功\r\n";
            }
            else
            {
                std::cout << "保存失败: " << error_msg << "\r\n";
            }
            break;
        }
        case Operate::SET_BOOT:
        {
            std::cout << "成功设置开机启动后, 开机时自动进行登录. \r\n如果登录成功, 程序将自动退出\r\n如果登陆失败, 程序显示错误信息, 不进行自动退出\r\n\r\n";
            result = Utils::EnableBoot(g_file_name);
            if (result)
            {
                std::cout << "设置开机启动成功!!!\r\n";
            }
            else
            {
                std::cout << "设置开机启动失败: " << error_msg << "\r\n";
            }

            break;
        }
        case Operate::UNSET_BOOT:
        {
            result = Utils::DisableBoot();
            if (result)
            {
                std::cout << "关闭开机启动成功\r\n";
            }
            else
            {
                std::cout << "关闭开机启动失败: " << error_msg << "\r\n";
            }
            break;
        }
        case Operate::EXIT:
        {
            g_running = false;
            break;
        }
        default:
        {
            std::cout << "非法输入\r\n";
        }
    }

    return result;
}

int main(int argc, char* argv[])
{
    g_file_name.append(argv[0]);

    std::cout << "放一个神秘链接 http://atcumt.com 欢迎加入~~~\r\n";

    while (!g_usermanager.ReadUserInfo(&g_userinfo))
    {
        std::cout << "未找到用户信息 创建用户信息 保存成功后无需再次输入\r\n";
        Process(Operate::CHANGE_USER_INFO);
    }

    int input;
    /*
    开机启动程序会自动带参数运行 判断参数数量得知是否是开机启动
    */
    bool boot_run = argc == 2;

    while (g_running)
    {
        if (!boot_run)
        {
            std::cout <<
                "\r\n-----------------------------------------------\r\n" <<
                "输入0: 登录\r\n"
                "输入1: 注销\r\n"
                "输入2: 修改用户信息\r\n"
                "输入3: 设置开机自动登录\r\n"
                "输入4: 取消开机自动登录\r\n"
                "输入5: 退出程序\r\n" <<
                "-----------------------------------------------\r\n";

            std::cin >> input;
            Process(static_cast<Operate>(input));
        }
        else
        {
            /*
            开机启动后登陆成功则退出程序 否则转为正常运行
            */
            boot_run = false;
            if (Process(Operate::LOGIN))
            {
                g_running = false;
            }
            else 
            {
                std::cout << "开机启动后尝试登陆失败 请处理错误后再次登录\r\n";
            }
        }
    }

    return 0;
}
