#pragma once
class Utils
{
public:

    /*
    ͨ���޸�ע��� ���ÿ�������
    */
    static bool EnableBoot(const std::string& file_path);

    /*
    ɾ��ע����� �رտ�������
    */
    static bool DisableBoot();

    static std::wstring ToWstring(std::string const& src);
    static std::string ToString(std::wstring const& src);
};

