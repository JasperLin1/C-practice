#include <iostream>
#include <string>
#include <vector> // 核心：使用 vector 必須引入此標頭檔
#include <list>   // 核心：使用 list 必須引入此標頭檔

// ========================================================
// 🎯 Week 4: Day 24 - STL (標準樣板庫) 基礎練習
// ========================================================
// STL (Standard Template Library) 是 C++ 官方提供的強大武器庫。
// 它已經用我們剛剛學過的「模板 (Template)」幫我們寫好了各種資料結構！
// 今天我們要學習最常用的兩個容器：
// 1. `std::vector` (動態陣列) ➡️ 自動增長容量的陣列，支援索引存取。
// 2. `std::list` (雙向鏈結串列) ➡️ 底層是 Linked List，新增刪除極快。


int main() {
    // ========================================================
    // 💡 1. std::vector (動態陣列)
    // ========================================================
    std::cout << "=== 1. 測試 std::vector ===" << std::endl;

    // 宣告一個儲存整數的 vector
    std::vector<int> numbers;

    // TODO 1: 使用 `push_back` 把三個數字 (10, 20, 30) 推入 vector 尾端。
    // [在此寫下代碼]
    numbers.push_back(10);
    numbers.push_back(20);
    numbers.push_back(30);


    std::cout << "目前 vector 的大小 (size): " << numbers.size() << std::endl;

    // TODO 2: 用兩種方式遍歷並印出 vector 的內容：
    // 方式 A：傳統索引迴圈 (例如用 numbers[i] 讀取值)
    std::cout << "方式 A (索引迴圈): " << std::endl;
    // 關鍵修正：迴圈條件必須是 `i < numbers.size()`。
    // 如果寫 `i <= numbers.size()`，當 i 變成 3 時，numbers[3] 就越界了，會讀到垃圾記憶體甚至當機！
    for(int i = 0; i < numbers.size(); i++){
        std::cout << numbers[i] << std::endl;
    }

    std::cout << std::endl;

    // 方式 B：現代 C++ 的 Range-based for 迴圈 (簡潔優雅，推薦！)
    std::cout << "方式 B (Range-based for): " << std::endl;
    // 解答你的疑問：這裡的 `num` 不是上面的索引 `i`，而是「直接代表陣列裡面的數值本身」！
    // 第一輪：num 是 numbers[0] (也就是 10)
    // 第二輪：num 是 numbers[1] (也就是 20)
    // 第三輪：num 是 numbers[2] (也就是 30)
    for(int num : numbers){
        std::cout << num << std::endl; 
    }


    std::cout << std::endl;


    // ========================================================
    // 💡 2. std::list (雙向鏈結串列)
    // ========================================================
    std::cout << "\n=== 2. 測試 std::list ===" << std::endl;

    // 宣告一個儲存字串的 list (購物清單)
    std::list<std::string> shoppingList;

    // TODO 3: 使用 `push_back` 和 `push_front` 新增項目。
    shoppingList.push_back("milk");
    shoppingList.push_back("bread");
    shoppingList.push_front("eggs");



    // 思考題：我們可以使用 `shoppingList[0]` 來讀取第一個項目嗎？
    // 答案：絕對不行！因為 list 底層是 Linked List (鏈結串列)，記憶體是不連續的，
    // 電腦無法直接透過索引計算出地址。必須從頭節點一個個走過去！

    // TODO 4: 使用 Range-based for 迴圈，遍歷並印出 shoppingList 的所有項目。
    for(std::string item : shoppingList){
        std::cout << item << std::endl;
    }



    // TODO 5: 測試刪除功能：
    // 解答你的疑問：C++ STL 的 `pop_front()` 與 `pop_back()` 回傳值是 void (空)，
    // 所以它們「不會」告訴你剛剛刪了誰。
    // 如果你想在刪除前確認是誰，必須先用 `.front()` 或 `.back()` 偷看一下：
    std::cout << "即將從最前面刪除: " << shoppingList.front() << std::endl; // 偷看最前面 (eggs)
    shoppingList.pop_front(); // 正式刪除
    
    std::cout << "即將從最後面刪除: " << shoppingList.back() << std::endl;  // 偷看最後面 (bread)
    shoppingList.pop_back(); // 正式刪除


    std::cout << "--- 刪除後的購物清單 ---" << std::endl;
    // TODO 6: 再次用 Range-based for 迴圈印出剩餘的項目 (應該只剩下牛奶)
    // [在此寫下 for 迴圈]
    for(std::string item : shoppingList){
        std :: cout << item << std :: endl;
    }

    return 0;
}
