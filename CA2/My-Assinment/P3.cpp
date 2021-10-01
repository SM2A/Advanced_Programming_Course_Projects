#include <iostream>
#include <vector>
#include <algorithm>

#define POSSIBLE_MOVE 4

using namespace std;

typedef vector<int> gold;
typedef vector<vector<int>> mine;
typedef struct raw_mine_data gold_mine;

struct raw_mine_data {
    int row;
    int column;
    mine mine_data;
    int row_move[POSSIBLE_MOVE];
    int column_move[POSSIBLE_MOVE];
};

bool collect_gold(gold_mine mine_data, gold &collected, int row, int column, int gold_collected = 0);
gold_mine get_mine_data();
int solve(gold_mine mine_data);

int main() {

    gold_mine data = get_mine_data();

    cout << solve(data) << endl;

    return 0;
}

gold_mine get_mine_data() {

    gold_mine mine_data;
    int row_move[POSSIBLE_MOVE] = {1, -1, 0, 0};
    int column_move[POSSIBLE_MOVE] = {0, 0, -1, 1};

    cin >> mine_data.row
        >> mine_data.column;

    for (int row = 0; row < mine_data.row; ++row) {
        mine_data.mine_data.push_back(vector<int>());
        for (int column = 0; column < mine_data.column; ++column) {
            int input_gold;
            cin >> input_gold;
            mine_data.mine_data[row].push_back(input_gold);
        }
    }

    for (int index = 0; index < POSSIBLE_MOVE; ++index) {
        mine_data.row_move[index] = row_move[index];
        mine_data.column_move[index] = column_move[index];
    }

    return mine_data;
}

bool collect_gold(gold_mine mine_data, gold &collected, int row, int column, int gold_collected) {

    if (mine_data.mine_data[row][column] == 0) return false;

    gold_collected += mine_data.mine_data[row][column];
    mine_data.mine_data[row][column] = 0;

    for (int move = 0; move < POSSIBLE_MOVE; ++move) {

        int new_row = row + mine_data.row_move[move];
        int new_column = column + mine_data.column_move[move];

        if ((new_row < 0) || (new_column < 0) || (new_row >= mine_data.row) || (new_column >= mine_data.column))
            continue;

        if (mine_data.mine_data[new_row][new_column] == 0) continue;

        if (collect_gold(mine_data, collected, new_row, new_column, gold_collected))
            return true;
    }
    collected.push_back(gold_collected);
    return false;
}

int solve(gold_mine mine_data) {

    gold collected_gold;

    for (int row = 0; row < mine_data.row; ++row) {
        for (int column = 0; column < mine_data.column; ++column) {
            collect_gold(mine_data, collected_gold, row, column);
        }
    }
    sort(collected_gold.begin(), collected_gold.end());
    return collected_gold[collected_gold.size() - 1];
}