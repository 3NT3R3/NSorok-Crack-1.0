#pragma once
#include "head.h"

std::string menu = "NSorok-Crack 1.0 - easy cracking ;)\n\n";
std::string prompt = "NSorok-Crack >> ";
std::string help_syntax = "NSorok-Crack Syntax:\n| <IP_TARGET> -U <USERNAME>\' -P <FILE_WITH_PASSWORDS>\'\n|\n";
std::string help_explanation = "| Explanation:\n| <IP_TARGET> - IPv4 target\n| -U <USERNAME>\' - username (for exaple mysql\')\n";
std::string help_explanation2 = "| -P <FILE_WITH_PASSWORDS>\' - file with password (for exaple ~/passwords.txt\')\n";
std::string help_explanation3 = "|_____________________________________________________________________________________\n";

void help()
{
    std::cout << help_syntax << help_explanation << help_explanation2 << help_explanation3 << "\n";
}