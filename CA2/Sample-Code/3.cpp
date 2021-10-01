#include <iostream>
#include <vector>

const std::pair<int, int> POSSIBLE_MOVES[] = {
    {-1, 0},
    {0, 1},
    {1, 0},
    {0, -1},
};

bool isValidIndices(const std::vector<std::vector<int>> &mine, int row, int column)
{
    int numberOfRows = mine.size();
    int numberOfColumns = mine[0].size();
    return row >= 0 && row < numberOfRows && column >= 0 && column < numberOfColumns && mine[row][column];
}

int findMaximumPathFrom(const std::vector<std::vector<int>> &mine, int row, int column, std::vector<std::vector<bool>> visited)
{
    if (!isValidIndices(mine, row, column) || visited[row][column])
    {
        return 0;
    }

    visited[row][column] = true;
    int result = 0;
    for (auto &&move : POSSIBLE_MOVES)
    {
        result = std::max(result, findMaximumPathFrom(mine, row + move.first, column + move.second, visited));
    }
    return mine[row][column] + result;
}

int findMaximumPathFrom(const std::vector<std::vector<int>> &mine, int row, int column)
{
    std::vector<std::vector<bool>> visited(mine.size(), std::vector<bool>(mine[0].size(), false));
    return findMaximumPathFrom(mine, row, column, visited);
}

int main()
{
    int numberOfRows, numberOfColumns;
    std::cin >> numberOfRows >> numberOfColumns;
    std::vector<std::vector<int>> mine(numberOfRows);
    int cellValue;
    for (int row = 0; row < numberOfRows; row++)
    {
        for (int column = 0; column < numberOfColumns; column++)
        {
            std::cin >> cellValue;
            mine[row].push_back(cellValue);
        }
    }

    int result = 0;
    for (int row = 0; row < numberOfRows; row++)
    {
        for (int column = 0; column < numberOfColumns; column++)
        {
            result = std::max(result, findMaximumPathFrom(mine, row, column));
        }
    }
    std::cout << result << std::endl;
    return 0;
}
