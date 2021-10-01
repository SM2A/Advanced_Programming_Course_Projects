#include <functional>
#include <iostream>
#include <string>

#define NOT_FOUND "NOT_FOUND"

unsigned long int generatePasswordHash(std::string password)
{
    return std::hash<std::string>()(password);
}

std::string findPassword(std::string validAlphabet, unsigned long int passwordHash, int remainingLength, std::string currentPassword = "")
{
    if (generatePasswordHash(currentPassword) == passwordHash)
    {
        return currentPassword;
    }

    if (!remainingLength)
    {
        return NOT_FOUND;
    }

    std::string foundPassword;
    for (size_t i = 0; i < validAlphabet.size(); i++)
    {
        currentPassword += validAlphabet[i];
        foundPassword = findPassword(validAlphabet, passwordHash, remainingLength - 1, currentPassword);
        if (foundPassword != NOT_FOUND)
        {
            return foundPassword;
        }

        currentPassword.pop_back();
    }

    return NOT_FOUND;
}

int main()
{
    std::string validAlphabet;
    unsigned long int passwordHash;
    int length;

    std::cin >> length >> validAlphabet >> passwordHash;

    std::cout << findPassword(validAlphabet, passwordHash, length) << std::endl;

    return 0;
}
