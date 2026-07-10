#include <iostream>

// ========================================================
// 知識點 1: 什麼是函式 (Function)？
// ========================================================
// 函式就像是一台機器，丟入原料（參數），產出成品（回傳值）。
// 語法：
// 回傳值型態 函式名稱(參數1, 參數2, ...) {
//     程式碼...
//     return 結果;
// }

// 範例：寫一個計算兩數相加的函式
int add(int a, int b) {
    return a + b;
}

// ========================================================
// 練習 1: 實作一個「計算圓形面積」的函式
// ========================================================
// TODO: 請實作 circleArea 函式
// - 參數：浮點數 radius (半徑)
// - 回傳值：雙精度浮點數 (double)
// - 圓周率 π 請用 3.14159 計算
// [在此寫下你的 circleArea 函式]
double circleArea(double radius) {
    // 圓面積 = 半徑 * 半徑 * PI
    return radius * radius * 3.14159;
}



// ========================================================
// 練習 2: 實作「線性搜尋演算法 (Linear Search)」
// ========================================================
// 陣列 (Array) 是記憶體中連續的空間，用來存放相同型態的多個資料。
// 線性搜尋：從陣列的第一個元素開始，一個一個往後比對，直到找到目標，或者找完為止。
//
// TODO: 請實作 linearSearch 函式
// - 參數：
//     1. int arr[] (要搜尋的陣列)
//     2. int size (陣列的長度)
//     3. int target (我們要尋找的目標數字)
// - 回傳值：
//     - 如果找到目標，回傳該數字在陣列中的「索引 (index)」(0, 1, 2...)
//     - 如果找完所有元素都沒找到，回傳 -1
//
// 提示：使用 for 迴圈遍歷整個陣列，並用 if 判斷 arr[i] 是否等於 target。
// [在此寫下你的 linearSearch 函式]
int linearSearch(int arr[], int size, int target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            return i; // 找到了！立刻回傳索引並結束函式。
        }
        // 警告：不要在這裡寫 else { return -1; }
        // 因為如果第一個數字不對，它就會直接回傳 -1 結束程式，後面就找不到了！
    }
    // 當整個 for 迴圈都跑完（代表所有數字都比對過且都不符合）
    // 才能確定沒找到，此時才回傳 -1。
    return -1;
}
    


int main() {
    // 測試練習 1：計算圓面積
    std::cout << "=== 測試 1: 函式與圓面積 ===" << std::endl;
    double r = 5.0;
    // 解除下方註解來測試你的 circleArea 函式：
    std::cout << "半徑為 " << r << " 的圓面積是: " << circleArea(r) << std::endl;

    std::cout << std::endl;

    // 測試練習 2：線性搜尋演算法
    std::cout << "=== 測試 2: 陣列與線性搜尋演算法 ===" << std::endl;
    
    // 宣告一個包含 6 個數字的陣列
    int myNumbers[] = {12, 45, 7, 23, 56, 89};
    int size = 6; // 陣列的長度

    std::cout << "當前陣列中的數字為: ";
    for (int i = 0; i < size; i++) {
        std::cout << myNumbers[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "請輸入你想搜尋的數字: ";
    int target;
    std::cin >> target;

    // 呼叫你的搜尋函式
    // 解除下方註解來測試你的 linearSearch 函式：
    int resultIndex = linearSearch(myNumbers, size, target);

    if (resultIndex != -1) {
        std::cout << "找到了！數字 " << target << " 位在陣列的索引 " << resultIndex << "。" << std::endl;
        std::cout << "驗證：myNumbers[" << resultIndex << "] 的確是 " << myNumbers[resultIndex] << std::endl;
    } else {
        std::cout << "很遺憾，陣列中沒有數字 " << target << "。" << std::endl;
    }

    return 0;
}
