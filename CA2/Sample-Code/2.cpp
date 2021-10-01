#include <iostream>
#include <vector>
#include <string>

int calculateMultiplyOfPrevious(const std::vector<int>& numbers, int index, int start = 0)
{
    if (start >= index)
    {
        return 1;
    }

    return numbers[start] * calculateMultiplyOfPrevious(numbers, index, start + 1);
}

int calculateMultiplyOfAfter(const std::vector<int>& numbers, int index)
{
    if (index >= numbers.size() - 1)
    {
        return 1;
    }

    index += 1;
    return numbers[index] * calculateMultiplyOfAfter(numbers, index);
}

int calculateMultiplyOfOthers(const std::vector<int>& numbers, int index)
{
    return calculateMultiplyOfPrevious(numbers, index) * calculateMultiplyOfAfter(numbers, index);
}

std::vector<int> manipulate(std::vector<int> numbers, int currentIndex = 0)
{
    if (currentIndex == numbers.size())
    {
        return numbers;
    }

    int result = calculateMultiplyOfOthers(numbers, currentIndex);
    numbers = manipulate(numbers, currentIndex + 1);
    numbers[currentIndex] = result;
    return numbers;
}

void printVector(const std::vector<int>& numbers, std::vector<int>::const_iterator currentItem)
{
    if (currentItem == numbers.end())
    {
        std::cout << std::endl;
        return;
    }

    std::cout << *currentItem++ << ' ';
    printVector(numbers, currentItem);
}

int main()
{
    std::vector<int> numbers;
    int number;
    while (std::cin >> number)
    {
        numbers.push_back(number);
    }

    numbers = manipulate(numbers);

    printVector(numbers, numbers.begin());
    return 0;
}
