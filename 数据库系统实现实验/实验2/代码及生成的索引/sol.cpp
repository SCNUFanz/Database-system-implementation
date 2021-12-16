#include <iostream>
#include <fstream>
#include <cstring>
#include <bitset>
#include <vector>
#include <map>
#include <unordered_map>
#include <ctime>

#include <cmath>

const int N = 23;
const int BLOCK_SIZE = 1000;
const int MOD = (1 << N);
const int P = 1e9 + 7;
std::string testdata = "data\\testdata.csv";
std::string testdata1 = "data\\testdata1.csv";
std::string testdata2 = "data\\testdata2.csv";
std::string testdata3 = "data\\testdata3.csv";
std::string testdata4 = "data\\testdata4.csv";
std::string relative_path = "testdata.csv";
std::string relative_path1 = "testdata1.csv";
std::string relative_path2 = "testdata2.csv";
std::string relative_path3 = "testdata3.csv";
std::string relative_path4 = "testdata4.csv";
std::string path = "dataout2\\indexfile";

struct Bucket {
    int i;
    int pointer[1 << N];

    Bucket(int _i = 1) : i(_i) {}
}buk;
struct Block {
    int j;
    int size;
    std::string indexfile;
    std::vector<std::string> position;

    Block(int _j = 1, int _sz = 0) : j(_j), size(_sz) {}
}block[1 << N];
int filenum, blknum;
std::string tmp[BLOCK_SIZE + 1];
std::string buk_filepath[1 << N];

inline int Hash(std::string str) {
    int res = 0;
    for (int i = 0; i < (int)str.size(); i++) {
        res = (1ll * res * P + str[i]) % MOD;
    }
    return res;
}
inline int get(int num, int x) {
    return (num & ((1 << x) - 1));
}
void Insert(std::string primary_key, std::string filepath, int linenum) {
    int hash_val = Hash(primary_key);
    int num = get(hash_val, buk.i);
    if (buk.pointer[num] != 0) {
        int x = buk.pointer[num];
        if (block[x].size < BLOCK_SIZE) {
            block[x].size++;
            block[x].position.push_back(primary_key + "," + filepath + "," + std::to_string(linenum)); 
        } else {
            if (block[x].j == buk.i) {
                buk.i++;
                for (int j = 0; j < (1 << buk.i); j++) {
                    buk.pointer[j] = buk.pointer[get(j, buk.i - 1)];
                }
            }
            block[x].j++;

            int idx = 0;
            for (int i = 0; i < block[x].size; i++) {
                tmp[idx++] = block[x].position[i];
            }
            tmp[idx++] = primary_key + "," + filepath + "," + std::to_string(linenum);

            blknum++;
            std::string newfile = path + std::to_string(++filenum);
            block[x].size = block[blknum].size = 0;
        	block[blknum].j = block[x].j;
            block[blknum].indexfile = newfile;
            block[x].position.clear();
            block[blknum].position.clear();

            int t = get(num, block[x].j - 1);
            for (int k = 0; k < (1 << (buk.i - block[x].j + 1)); k++) {
                int n = t + (k << (block[x].j - 1));
                if (buk.pointer[n] == x && ((n >> (block[x].j - 1)) & 1)) {
                    buk.pointer[n] = blknum;
                }
            }

            for (int i = 0; i < idx; i++) {
                std::string line = tmp[i];
                std::string pk = line.substr(0, line.find(','));
                int val = Hash(pk);
                if ((val >> (block[x].j - 1)) & 1) {
                    block[blknum].size++;
                    block[blknum].position.push_back(line);
                } else {
                    block[x].size++;
                    block[x].position.push_back(line);
                }
            }
        }
    } else {
        std::string newfile = path + std::to_string(++filenum);
        buk.pointer[num] = ++blknum;
        block[blknum].size = 1;
        block[blknum].indexfile = newfile;
        block[blknum].position.push_back(primary_key + "," + filepath + "," + std::to_string(linenum)); 
    }
}
void BuildIndex(std::string filepath, std::string relative_path) {
    std::ifstream fin;
    fin.open(filepath.c_str(), std::ios::binary | std::ios::in); 
    std::string line;
    int linenum = 0;
    while (getline(fin, line)) {
        linenum++;
        if (linenum == 1) {
            continue;
        }
        std::string primary_key = line.substr(0, line.find(','));
        Insert(primary_key, relative_path, linenum);
    }
    fin.close();
    std::cerr << relative_path << " finished!" << '\n';
}
void BuildIndexFile() {
	std::ofstream fout;
	fout.open("dataout2\\bucket_index", std::ios::binary | std::ios::out);
	for (int j = 0; j < (1 << buk.i); j++) {
		fout << block[buk.pointer[j]].indexfile << '\n';
	}
	fout.close();
    for (int i = 1; i <= blknum; i++) {
        fout.open(block[i].indexfile.c_str(), std::ios::binary | std::ios::out);
        for (int j = 0; j < block[i].size; j++) {
            fout << block[i].position[j] << '\n';
        }
        fout.close();
    }
}
void build() {
    BuildIndex(testdata1, relative_path1);
    BuildIndex(testdata2, relative_path2);
    BuildIndex(testdata3, relative_path3);
    BuildIndex(testdata4, relative_path4);
	BuildIndexFile();
}
void query() {
    std::ifstream fin;
    fin.open("dataout2\\bucket_index", std::ios::binary | std::ios::in);
    std::string filepath;
    int j = 0;
    while (getline(fin, filepath)) {
        buk_filepath[j++] = filepath;
    }
    int buk_i = std::log2(j);
    fin.close();
    while (1) {
        std::cout << "Please input operation: 1. Query 2. Exit " << '\n';
        int op;
        std::cin >> op;
        if (op == 1) {
            std::cout << "Please enter the primary key of the record to be queried: ";
            std::string primary_key;
            std::cin >> primary_key;
            int hash_val = Hash(primary_key);
            int num = get(hash_val, buk_i);
            std::ifstream fin;
            fin.open(buk_filepath[num].c_str(), std::ios::binary | std::ios::in);
            std::string line, position;
            while(getline(fin, line)) {
                std::string pk = line.substr(0, line.find(','));
                if (pk == primary_key) {
                    position = line.substr(line.find(',') + 1, (int)line.size() - (line.find(',') + 1)); 
                    break;
                }
            }
            if ((int)position.size() != 0) {
                std::string file = "data\\" + position.substr(0, position.find(','));
                std::string tmp = position.substr(position.find(',') + 1, (int)position.size() - (position.find(',') + 1));
                int linenum = atoi(tmp.c_str());
                std::ifstream fin;
                fin.open(file.c_str(), std::ios::binary | std::ios::in);
                int cnt = 0;
                std::string result;
                while (getline(fin, result)) {
                    cnt++;
                    if (cnt == linenum) {
                        break;
                    }
                } 
                std::cout << "The record is in " + file << "line " << linenum  << '\n';
                std::cout << result << '\n';
            } else {
                std::cout << "No record found!" << '\n';
            }
        } else {
            break;
        }
    }
}
int main() {
    clock_t start = clock();
    build();
    // query();
    clock_t end = clock();
    std::cerr << "cost time = " << (double)(end - start) / CLOCKS_PER_SEC << "s" << '\n';
    return 0;
}