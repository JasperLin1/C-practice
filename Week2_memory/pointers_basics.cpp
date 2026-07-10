#include <iostream>

// ========================================================
// 知識點 1: 傳值呼叫 (Call by Value)
// ========================================================
// 這是我們以前學的普通函式。它會複製一份新的資料進去，
// 即使在函式內部修改了參數的值，也不會影響到 main 裡面的原始變數。
void addTenValue(int num) {
    num = num + 10;
}

// ========================================================
// 知識點 2: 傳指標呼叫 (Call by Pointer)
// ========================================================
// 我們傳入變數的「記憶體位址 (指標)」。
// 在函式內部，透過 `*ptr` 就可以直接修改外部原始變數的值！
void addTenPointer(int* ptr) {
    if (ptr != nullptr) {
        *ptr = *ptr + 10; // 打開指標指向的地址，把值加 10
    }
}

// ========================================================
// 知識點 3: 傳參考呼叫 (Call by Reference)
// ========================================================
// 參考 `int& ref` 就是變數的「別名 (綽號)」。
// 它是 C++ 獨有的超方便功能，不用像指標一樣寫 `*` 和 `&`，
// 寫起來像傳值，但實際上可以直接修改外部原始變數的值！
void addTenReference(int& ref) {
    ref = ref + 10; // 直接對別名做修改，原始變數也會跟著改
}

int main() {
    std::cout << "=== Part 1: 記憶體位址與指標變數 ===" << std::endl;
    int a = 42; // 在記憶體中宣告一個整數變數 a，裡面裝 42
    
    // TODO 1: 印出變數 a 的值，以及它在記憶體中的「位址」
    // 說明：a 代表格子裡裝的值 (42)，而 &a 代表這個格子的「門牌號碼 (地址)」
    std::cout << "a 的值是: " << a << std::endl;
    std::cout << "a 的記憶體地址 (&a) 是: " << &a << std::endl;

    // TODO 2: 宣告一個指標變數 ptr 指向 a 的位址，並印出指標與取值結果
    // 說明：
    // - `int* ptr` 代表宣告一個專門裝「整數地址」的指標變數，名字叫 ptr。
    // - `ptr = &a` 代表把 a 的門牌號碼存進 ptr 盒子裡。
    int* ptr = &a; 
    std::cout << "ptr 裡面存的地址是: " << ptr << " (這應該跟 &a 一模一樣)" << std::endl;
    std::cout << "使用 *ptr 取得該地址裡面的值是: " << *ptr << " (這應該跟 a 一模一樣，是 42)" << std::endl;


    // TODO 3: 透過指標 ptr 修改 a 的值為 100，並印出 a 來驗證
    // 說明：
    // - `*ptr = 100` 代表「打開 ptr 存的門牌號碼所在的格子，把裡面的東西換成 100」。
    // - 因為 ptr 存的是 a 的門牌，所以這行指令會直接修改變數 a 的值！
    *ptr = 100;
    std::cout << "經過 *ptr = 100 修改後，a 的值變成了: " << a << std::endl;


    std::cout << "\n=== Part 2: 傳值、傳指標與傳參考的差別 ===" << std::endl;
    int score = 80;
    std::cout << "最原始的 score: " << score << std::endl;

    // 1. 測試傳值呼叫 (Call by Value)
    // 說明：score 的值 (80) 被複製了一份傳給 addTenValue。函式裡面改的是複製品，原始 score 不變。
    addTenValue(score);
    std::cout << "1. 經過 addTenValue 後的 score: " << score << std::endl;

    // 2. 測試傳指標呼叫 (Call by Pointer)
    // 說明：我們把 score 的地址 (&score) 傳進去。
    // 函式 addTenPointer 收到地址後，用 *ptr 去修改那個地址的內容，所以 score 會被改變！
    addTenPointer(&score); 
    std::cout << "2. 經過 addTenPointer 後的 score: " << score << std::endl;

    // 3. 測試傳參考呼叫 (Call by Reference)
    // 說明：addTenReference(int& ref) 宣告了一個別名。
    // 當我們傳入 score，ref 就成了 score 的綽號，修改 ref 就等於修改 score，而且不需要寫 * 或 &。
    addTenReference(score);
    std::cout << "3. 經過 addTenReference 後的 score: " << score << std::endl;

    return 0;
}
