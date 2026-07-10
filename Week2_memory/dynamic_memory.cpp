#include <iostream>

int main() {
    std::cout << "=== 1. 單一變數的動態配置 ===" << std::endl;
    
    // TODO 1: 在 Heap (堆) 中動態配置一個整數空間，並用指標 p 儲存它的地址
    // 提示：使用 `new int`
    // [在此寫下宣告代碼]
    int* ptr = new int ; //申請一個格子，並把地址存進指標變數 ptr 中

    // TODO 2: 將該空間的值設為 999，並印出值與地址
    *ptr = 999;
    std::cout << "value is: " << *ptr << ", address is: " << ptr << std::endl;

    // TODO 3: 釋放該動態配置的記憶體，並將指標設為 nullptr 確保安全
    // 提示：使用 `delete p;` 和 `p = nullptr;`
    // [在此寫下代碼]
    
    delete ptr;
    ptr = nullptr;


    std::cout << "\n=== 2. 動態陣列的配置 (根據使用者輸入決定大小) ===" << std::endl;
    std::cout << "請輸入班級的學生人數: ";
    int size;
    std::cin >> size;

    // TODO 4: 在 Heap 中動態配置一個大小為 size 的整數陣列，並用指標 scores 儲存首地址
    int* scores = new int[size];
    

    // 輸入學生成績
    for (int i = 0; i < size; i++) {
        std::cout << "請輸入第 " << (i + 1) << " 位學生的成績: ";
        // TODO 5: 將輸入的值存入動態陣列對應的格子中
        std::cin >> scores[i];

    }

    // 計算平均分
    double sum = 0;
    for (int i = 0; i < size; i++) {
        sum += scores[i];
    }
    std::cout << "\n學生平均成績為: " << (sum / size) << " 分。" << std::endl;

    // TODO 6: 釋放動態陣列的記憶體，防止記憶體洩漏！
    delete[] scores;
    scores = nullptr;



    return 0;
}
