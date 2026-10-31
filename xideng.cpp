#include <iostream>
#include <bitset>
#include <cstring> // 用于 memset 和 memcpy
using namespace std;

void fei(int& y) {
    y ^= 1; // 等同于 if(y==1) y=0; else y=1; 更简洁
}
int main() {
    // 开大一点防止越界，全局/局部变量默认初始化为0
    int init_arr[7][8] = {0}; // 保存最原始的输入
    int arr[7][8];            // 用于每次枚举时操作
    int b[7][8];              // 记录操作状态
    for (int i = 1; i <= 5; i++) {
        for (int j = 1; j <= 6; j++) {
            cin >> init_arr[i][j];
        }
    }

    // 2. 枚举第一行的所有情况 (2^6 = 64 种)
    for (int i = 0; i < 64; i++) {
        // 【关键修复】每次枚举前，必须恢复初始状态，清空操作记录！
        memcpy(arr, init_arr, sizeof(arr)); // 把 init_arr 复制给 arr
        memset(b, 0, sizeof(b));            // 把 b 数组清零

        // 处理第一行（根据枚举的状态 i）
        // 使用 bitset 方便转为 6 位二进制字符串
        string str = bitset<6>(i).to_string(); 
        for (int j = 0; j < 6; j++) {
            if (str[j] == '1') {
                b[1][j + 1] = 1; // 记录第一行变了
                
                // 改变灯的状态（自身、上下左右）
                fei(arr[1][j + 1]); // 自身
                fei(arr[1][j]);     // 左
                fei(arr[1][j + 2]); // 右
                fei(arr[2][j + 1]); // 下
            }
        }

        // 处理第 2 到 5 行
        for (int k = 1; k <= 4; k++) {
            for (int l = 1; l <= 6; l++) {
                // 【关键修复】判断当前行灯的状态，如果亮着，必须在下一行按开关
                if (arr[k][l] == 1) {
                    b[k + 1][l] = 1; // 【关键修复】记录下一行的变化

                    // 改变灯的状态（自身、上下左右）
                    fei(arr[k + 1][l]);     // 下（当前按的开关）
                    fei(arr[k][l]);         // 上（自己这一行被影响）
                    fei(arr[k + 1][l - 1]); // 左
                    fei(arr[k + 1][l + 1]); // 右
                    fei(arr[k + 2][l]);     // 下下
                }
            }
        }

        // 3. 检查最后一行是否全部熄灭 (全为0)
        bool is_success = true;
        for (int l = 1; l <= 6; l++) {
            if (arr[5][l] == 1) {
                is_success = false;
                break;
            }
        }

        // 4. 如果成功，输出操作矩阵 b 并结束程序
        if (is_success) {
            for (int r = 1; r <= 5; r++) {
                for (int c = 1; c <= 6; c++) {
                    cout << b[r][c] << " ";
                }
                cout << endl;
            }
            break; // 题目通常只需要一个解，找到就退出
        }
    }

    return 0;
}