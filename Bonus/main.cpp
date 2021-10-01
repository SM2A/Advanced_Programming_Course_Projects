#include <iostream>
#include <fstream>

#define ENCRYPT "encrypt"
#define DECRYPT "decrypt"
#define SIMPLE "simple"
#define COMPLICATED "complicated"
#define RAND_RANGE 11

using namespace std;

struct process_handler{
    string mode;
    string type;
    string key;
};

string read_input_file(string input_file_path);

void write_output_file(string output_file_path, string output_content);

string simple_encrypt(string input_content, string key);

string simple_decrypt(string input_content, string key);

string complicated_encrypt(string input_content, string key);

string complicated_decrypt(string input_content, string key);

string process(struct process_handler process_data,string input_content);

int main() {

    string input_content, output_content;
    string input_file_path, output_file_path;
    struct process_handler process_data;

    cin >> process_data.mode
        >> process_data.type
        >> process_data.key
        >> input_file_path
        >> output_file_path;

    input_content = read_input_file(input_file_path);

    output_content = process(process_data,input_content);

    write_output_file(output_file_path, output_content);

    return 0;
}

string read_input_file(string input_file_path) {

    string input_content;
    ifstream input_file(input_file_path, ios::in);
    char ch = 0;
    while (input_file.get(ch)) input_content += ch;
    input_file.close();
    return input_content;
}

void write_output_file(string output_file_path, string output_content) {

    ofstream output_file(output_file_path, ios::out);
    output_file << output_content;
    output_file.close();
}

string process(struct process_handler process_data,string input_content){

    string output_content;
    if (process_data.mode == ENCRYPT) {
        if (process_data.type == SIMPLE) output_content = simple_encrypt(input_content, process_data.key);
        else if (process_data.type == COMPLICATED) output_content = complicated_encrypt(input_content, process_data.key);
    } else if (process_data.mode == DECRYPT) {
        if (process_data.type == SIMPLE) output_content = simple_decrypt(input_content, process_data.key);
        else if (process_data.type == COMPLICATED) output_content = complicated_decrypt(input_content, process_data.key);
    }
    return output_content;
}

string simple_encrypt(string input_content, string key) {

    int index = 0;
    string output_content;

    for (int i = 0; i < input_content.size(); i++) {
        if (index == key.size()) index = 0;
        int encrypted = (int) input_content[i] + (int) key[index];
        index++;
        output_content += to_string(encrypted);
        output_content += '\n';
    }
    return output_content;
}

string simple_decrypt(string input_content, string key) {

    int index = 0;
    string output_content;

    for (int i = 0; i < input_content.size(); i++) {
        if (index == key.size()) index = 0;
        string string_to_int;
        while (input_content[i] != '\n') {
            string_to_int += input_content[i];
            i++;
        }
        char decrypted = (char) (stoi(string_to_int) - (int) key[index]);
        index++;
        output_content += decrypted;
    }
    return output_content;
}

string complicated_encrypt(string input_content,  string key) {

    string output_content;
    int srand_starting_point = 0;
    for (int i = 0; i < key.size(); i++) srand_starting_point += (int) key[i];
    srand(srand_starting_point);

    for (int i = 0; i < input_content.size(); i++) {
        int encrypted = (int) input_content[i] + (rand() % RAND_RANGE);
        output_content += to_string(encrypted);
        output_content += '\n';
    }
    return output_content;
}

string complicated_decrypt(string input_content, string key) {

    string output_content;
    int srand_strarting_pint = 0;
    for (int i = 0; i < key.size(); i++) srand_strarting_pint += (int) key[i];
    srand(srand_strarting_pint);

    for (int i = 0; i < input_content.size(); i++) {
        string string_to_number;
        while (input_content[i] != '\n') {
            string_to_number += input_content[i];
            i++;
        }
        char decrypted = (char) (stoi(string_to_number) - (rand() % RAND_RANGE));
        output_content += decrypted;
    }
    return output_content;
}