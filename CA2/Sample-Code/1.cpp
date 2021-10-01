#include <iostream>
#include <string>

std::string reverse(std::string str)
{
    if (str.size() == 0)
    {
        return "";
    }

    return reverse(str.substr(1)) + str.front();
}

std::string encode(std::string password)
{
    int passwordLength = password.size();
    if (passwordLength == 1)
    {
        return password;
    }

    int middle = passwordLength / 2;
    return encode(reverse(password.substr(middle))) + encode(reverse(password.substr(0, middle)));
}

int main()
{
    std::string password;
    std::cin >> password;
    std::cout << encode(password) << std::endl;
    return 0;
}
