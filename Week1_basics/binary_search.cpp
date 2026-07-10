#include <iostream>

// ========================================================
// 知識點: 什麼是二分搜尋法 (Binary Search)？
// ========================================================
// 二分搜尋法適用於「已經排好序」的陣列。
// 每次比對中間的值：
// - 如果中間的值等於目標，恭喜找到！
// - 如果中間的值小於目標，代表目標在右半邊，將搜尋範圍的左界 (left) 往右移。
// - 如果中間的值大於目標，代表目標在左半邊，將搜尋範圍的右界 (right) 往左移。
// 每次比對都能將搜尋範圍「砍半」，效率非常高 ($O(\log N)$)。

// TODO: 請實作 binarySearch 函式
// - 參數：
//     1. int arr[] (已經排好序的陣列)
//     2. int size (陣列長度)
//     3. int target (要搜尋的目標數字)
// - 回傳值：
//     - 找到目標，回傳索引 (index)
//     - 沒找到目標，回傳 -1
//
// 提示步驟：
// 1. 宣告左界變數 `int left = 0;` 和右界變數 `int right = size - 1;`
// 2. 使用 while 迴圈，條件是當 `left <= right` 時就繼續找。
// 3. 在迴圈內部：
//    a. 計算中間索引 `int mid = left + (right - left) / 2;`
//    b. 如果 `arr[mid] == target`，代表找到了，直接回傳 `mid`。
//    c. 如果 `arr[mid] < target`，代表目標在右邊，請更新 `left = mid + 1;`
//    d. 如果 `arr[mid] > target`，代表目標在左邊，請更新 `right = mid - 1;`
// 4. 如果 while 迴圈結束了都沒回傳，代表找不到，最後回傳 -1。
// [在此寫下你的 binarySearch 函式]
int binarySearch(int arr[], int size, int target) {
    // 1. 在函式內部宣告左界與右界 (不應該放在參數列)
    int left = 0;
    int right = size - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2; //cabinet number indexing

        if (arr[mid] == target) {
            return mid; // 找到了，立刻回傳索引
        } else if (arr[mid] < target) {
            left = mid + 1; // 目標在右半邊，縮小左界
        } else {
            right = mid - 1; // 目標在左半邊，縮小右界
        }
        // 警告：不要在這裡寫 return -1; 
        // 否則迴圈跑完第一次如果沒中，就會直接結束並回傳 -1！
        //arr[mid] is the number in arr
    }

    // 2. 當 while 迴圈結束 (left > right)，代表找遍了整個範圍都沒有找到
    return -1; 
}
    


int main() {
    // 一個已經排好序的陣列 (二分搜尋的前提條件！)
    int sortedNumbers[] = {2, 5, 8, 12, 16, 23, 38, 56, 72, 91};
    int size = 10;

    std::cout << "=== 二分搜尋法測試 ===" << std::endl;
    std::cout << "已排序陣列中的數字為: ";
    for (int i = 0; i < size; i++) {
        std::cout << sortedNumbers[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "請輸入你想搜尋的數字: ";
    int target;
    std::cin >> target;

    // 呼叫二分搜尋法
    // TODO: 寫好 binarySearch 函式後，解除下方代碼的註解來進行測試：
    int resultIndex = binarySearch(sortedNumbers, size, target);

    if (resultIndex != -1) {
        std::cout << "找到了！數字 " << target << " 位在已排序陣列的索引 " << resultIndex << "。" << std::endl;
        std::cout << "驗證：sortedNumbers[" << resultIndex << "] 的確是 " << sortedNumbers[resultIndex] << std::endl;
    } else {
        std::cout << "很遺憾，已排序陣列中沒有數字 " << target << "。" << std::endl;
    }

    return 0;
}
