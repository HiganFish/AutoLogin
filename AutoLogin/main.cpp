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
std::string error_msg = "δ֪����";

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
    error_msg = "δ֪����";

    switch (operate)
    {
        case Operate::LOGIN:
        {
            result = g_network_manager.Login(g_userinfo.username, g_userinfo.password);
            if (result)
            {
                std::cout << "��¼�ɹ�\r\n";
            }
            else
            {
                std::cout << "��¼ʧ��: " << error_msg << "\r\n";
            }
            break;
        }
        case Operate::LOGOUT:
        {
            result = g_network_manager.Logout();
            if (result)
            {
                std::cout << "ע���ɹ�\r\n";
            }
            else
            {
                std::cout << "ע��ʧ��: " << error_msg << "\r\n";
            }
            break;
        }
        case Operate::CHANGE_USER_INFO:
        {
            result = g_usermanager.OperateChangeUserInfo(&g_userinfo);
            if (result)
            {
                std::cout << "����ɹ�\r\n";
            }
            else
            {
                std::cout << "����ʧ��: " << error_msg << "\r\n";
            }
            break;
        }
        case Operate::SET_BOOT:
        {
            std::cout << "�ɹ����ÿ���������, ����ʱ�Զ����е�¼. \r\n�����¼�ɹ�, �����Զ��˳�\r\n�����½ʧ��, ������ʾ������Ϣ, �������Զ��˳�\r\n\r\n";
            result = Utils::EnableBoot(g_file_name);
            if (result)
            {
                std::cout << "���ÿ��������ɹ�!!!\r\n";
            }
            else
            {
                std::cout << "���ÿ�������ʧ��: " << error_msg << "\r\n";
            }

            break;
        }
        case Operate::UNSET_BOOT:
        {
            result = Utils::DisableBoot();
            if (result)
            {
                std::cout << "�رտ��������ɹ�\r\n";
            }
            else
            {
                std::cout << "�رտ�������ʧ��: " << error_msg << "\r\n";
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
            std::cout << "�Ƿ�����\r\n";
        }
    }

    return result;
}

int main(int argc, char* argv[])
{
    g_file_name.append(argv[0]);

    std::cout << "��һ���������� http://atcumt.com ��ӭ����~~~\r\n";

    while (!g_usermanager.ReadUserInfo(&g_userinfo))
    {
        std::cout << "δ�ҵ��û���Ϣ �����û���Ϣ ����ɹ��������ٴ�����\r\n";
        Process(Operate::CHANGE_USER_INFO);
    }

    int input;
    /*
    ��������������Զ����������� �жϲ���������֪�Ƿ��ǿ�������
    */
    bool boot_run = argc == 2;

    while (g_running)
    {
        if (!boot_run)
        {
            std::cout <<
                "\r\n-----------------------------------------------\r\n" <<
                "����0: ��¼\r\n"
                "����1: ע��\r\n"
                "����2: �޸��û���Ϣ\r\n"
                "����3: ���ÿ����Զ���¼\r\n"
                "����4: ȡ�������Զ���¼\r\n"
                "����5: �˳�����\r\n" <<
                "-----------------------------------------------\r\n";

            std::cin >> input;
            Process(static_cast<Operate>(input));
        }
        else
        {
            /*
            �����������½�ɹ����˳����� ����תΪ��������
            */
            boot_run = false;
            if (Process(Operate::LOGIN))
            {
                g_running = false;
            }
            else 
            {
                std::cout << "�����������Ե�½ʧ�� �봦�������ٴε�¼\r\n";
            }
        }
    }

    return 0;
}
