// server-sorter.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <Shlwapi.h>
#include <Windows.h>
#include <fstream>
#include <string>
#include <ctime>

void prepare_and_listening() {
    std::wofstream clean_file("sysi.txt");
    clean_file.clear();
    clean_file.close();
    //ShellExecute(NULL, L"open", L"C:\\WINDOWS\\system32\\cmd.exe", L"/k calc.exe", 0, SW_RESTORE);
    ShellExecute(NULL, L"open", L"C:\\WINDOWS\\system32\\cmd.exe", L"/k (ncat -l -p 23 > sysi.txt)&(exit)", 0, SW_SHOWNORMAL);
    //system("cmd.exe ncat -l -p 23 > sysi.txt");
    // /k (ncat -l -p 23 > sysi.txt)&(exit)
}


int main()
{
    setlocale(LC_CTYPE, "");
    std::wstring ip_seek_string = L"192.168.0.";

    prepare_and_listening();

    while (true)
    {
        std::wifstream sysinf_file("sysi.txt");
        if (!sysinf_file)
        {
            // То выводим следующую ошибку и выполняем exit()
            std::cerr << "Uh oh, SomeText.txt could not be opened for reading!";
            exit(1);
        }


        std::wstring ts,cont = L"";
        while (!sysinf_file.eof())
        {
            std::getline(sysinf_file, ts);
            cont.append(ts);
        }
        sysinf_file.close();
        //sysinf_file.seekg(0, std::ios::beg); // перемещаемся в начало файла
        //sysinf_file.seekg(0, ios::end); // перемещаемся в конец файла

        //std::cout << cont;


        sysinf_file.open("sysi.txt");
        if (cont != L"")
        {

            std::cout << 785;
            std::wstring machine_ip_str, temp_str;

            while (!sysinf_file.eof())
            {
                std::getline(sysinf_file, temp_str);
                
                int ip_pos = temp_str.find(ip_seek_string);
                if (ip_pos != -1)
                {
                    if (temp_str[ip_pos + 1] != '1')
                    {
                        machine_ip_str = temp_str.substr(ip_pos, temp_str.length() - ip_pos + 1 - 1);
                    }
                }
            }

            std::wstring dest_file_name = L"C:\\Users\\kseno\\YandexDisk\\net_info\\";

            dest_file_name.append(machine_ip_str);

            //time_t now = time(0);
            //char* dt = new char[255];
            //ctime_s(dt,255, &now);

            //std::string timestr(dt);
            //delete[] dt;
            
            //dest_file_name.append(timestr);
            dest_file_name.append(L".txt");
            sysinf_file.close();
            //std::ofstream dst(dest_file_name, std::ios::binary);

            //dst << sysinf_file.rdbuf();
            //dst.close();

            std::wstring cmd_str = L"/k (COPY sysi.txt ";
            cmd_str.append(dest_file_name);
            cmd_str.append(L")&(exit)");
            ShellExecute(NULL, L"open", L"C:\\WINDOWS\\system32\\cmd.exe", cmd_str.c_str(), 0, SW_SHOWNORMAL);
            Sleep(1000);



            prepare_and_listening();

        }
        else
        {
            Sleep(1000);
        }
        sysinf_file.close();
    }

}

