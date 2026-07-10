#include <iostream>
#include <string>

// ========================================================
// 知識點: 什麼是類別 (Class) 與物件 (Object)？
// ========================================================
// - 類別 (Class) 是藍圖：定義了資料 (變數) 與行為 (函式)。
// - 物件 (Object) 是實體：用藍圖造出來的實際東西。
//
// 封裝 (Encapsulation)：
// - `private` (私有)：只有類別內部可以存取，外部摸不到。用於保護資料。
// - `public` (公開)：外部可以自由存取的介面。
//
// 建構子 (Constructor) 與 解構子 (Destructor)：
// - 建構子：物件出生時自動執行的函式，用來初始化資料。名字與 Class 相同。
// - 解構子：物件死亡（被銷毀/釋放）時自動執行的清掃函式。名字是 `~Class`。

class Student {
private:
    std::string name; // 姓名 (私有，外部不能直接修改)
    int score;        // 分數 (私有，外部不能直接修改)

public:
    // TODO 1: 實作建構子 (Constructor)
    // 提示：
    // - 函數名稱必須是 `Student`，沒有回傳值型態。
    // - 接收兩個參數：`std::string n` 和 `int s`。
    // - 在裡面將私有變數 `name` 設為 `n`，`score` 設為 `s`。
    // [在此寫下建構子代碼]
    Student(std::string n, int s) {
        
    }

    // TODO 2: 實作解構子 (Destructor)
    // 提示：
    // - 函數名稱必須是 `~Student()`，沒有參數，沒有回傳值。
    // - 內部印出一行訊息："學生物件 " << name << " 已被銷毀。" << std::endl;
    // [在此寫下解構子代碼]
    ~Student() {
        
    }

    // TODO 3: 實作 Getter (取得私有資料的公開函式)
    // 提示：
    // - `getName()` 回傳字串 name。
    // - `getScore()` 回傳整數 score。
    // [在此寫下兩個 Getter 函式]
    std::string getName() {
        return ""; // 請修改它
    }
    
    int getScore() {
        return 0; // 請修改它
    }

    // TODO 4: 實作 Setter (修改私有資料的公開函式，加入安全檢查！)
    // 提示：
    // - 函數名稱：`setScore(int newScore)`。
    // - 在內部做安全檢查：如果 `newScore` 介於 0 到 100 之間，才將 `score` 修改為 `newScore`；
    //   否則印出警告訊息："錯誤：無效的分數值！"
    // [在此寫下 Setter 函式]
    void setScore(int newScore) {
        
    }
};

int main() {
    std::cout << "=== 1. 測試 Stack 物件的生命週期 ===" << std::endl;
    {
        // 用大括號 `{}` 限制生命範圍
        // TODO 5: 在 Stack 宣告一個名為 s1 的 Student 物件，名字叫 "Jasper"，分數 90 分。
        // [在此寫下宣告代碼]


        // 測試修改分數
        std::cout << "嘗試修改 " << s1.getName() << " 的分數為 98 分..." << std::endl;
        s1.setScore(98);
        std::cout << s1.getName() << " 目前的分數是: " << s1.getScore() << std::endl;

        // 測試輸入錯誤的分數 (安全機制應該會擋下來)
        std::cout << "嘗試修改分數為 150 分 (無效分數)..." << std::endl;
        s1.setScore(150);
        std::cout << s1.getName() << " 的分數依然是: " << s1.getScore() << std::endl;
        
        std::cout << "--- 離開大括號範圍，Stack 物件準備死亡 ---" << std::endl;
    } // 離開大括號後，s1 應該會自動被釋放，並觸發解構子！

    std::cout << "\n=== 2. 測試 Heap 物件的生命週期 ===" << std::endl;
    
    // TODO 6: 在 Heap 動態配置一個 Student 物件，名字叫 "Bob"，分數 80 分。
    // 提示：使用 `new Student("Bob", 80)`，並用指標 `Student* s2` 來接收地址。
    // [在此寫下代碼]



    std::cout << "印出 s2 的資訊：" << std::endl;
    // 解除下方註解來測試：
    // std::cout << s2->getName() << " 的分數是: " << s2->getScore() << std::endl;

    std::cout << "--- 準備手動釋放 Heap 物件 ---" << std::endl;
    // TODO 7: 用 delete 釋放 s2 指向的物件，觀察解構子是否會在此刻觸發！
    // [在此寫下代碼]



    std::cout << "程式結束。" << std::endl;
    return 0;
}
