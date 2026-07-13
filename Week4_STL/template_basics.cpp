#include <iostream>
#include <string>

// ========================================================
// 1. 知識點：函式模板 (Function Template)
// ========================================================
// 想像你要寫一個比較兩個數並回傳較大值的函式。
// 如果沒有模板，你得寫：
//   int getMax(int a, int b);
//   double getMax(double a, double b);
//   char getMax(char a, char b);
// 使用模板，我們可以用一個「型態占位符 (T)」來代表任意型態！

template <typename T>
T getMax(T a, T b) {
    return (a > b) ? a : b;
}

// ========================================================
// 2. 知識點：類別模板 (Class Template)
// ========================================================
// 類別也可以用模板來宣告。最常見的就是「容器」（如 Stack、Queue、或裝任何東西的盒子）。
// 這裡我們寫一個簡單的 `Box` 類別，它能裝任何型態的禮物！

template <typename T>
class Box {
private:
    T content; // 這裡的 T 會在我們宣告物件時被替換成具體的型態 (如 int 或 string)

public:
    Box(T val) {
        content = val;
    }

    T getContent() {
        return content;
    }

    void setContent(T val) {
        content = val;
    }
};

// ========================================================
// 🎯 今日挑戰：寫一個模板化的 Stack (Template Stack)
// ========================================================
// 我們要把之前寫的 Stack 改造一下，讓它不僅能裝 int，還能裝 char、double 甚至 string！
// 提示：
// - 在 class 定義上方加上 `template <typename T>`。
// - 把內部原本寫死的 `int* arr` 或 `char* arr` 改為 `T* arr`。
// - 函式裡面的資料型態也改為 `T` (例如 `void push(T val)`，`T pop()`)。

template <typename T>
class TemplateStack {
private:
    T* arr; // 動態陣列，存型態為 T 的資料
    int capacity;
    int topIndex;

public:
    // TODO 1: 實作模板建構子
    // 提示：
    // - 接收一個容量參數 `cap`。
    // - 使用 `new T[capacity]` 在 Heap 配置大小為 capacity 的 T 型態陣列！
    TemplateStack(int cap) {
        capacity = cap;
        topIndex = -1;
        // [在此寫下動態配置代碼]
        arr = new T[capacity];
        
    }

    // TODO 2: 實作模板解構子
    ~TemplateStack() {
        // [在此寫下釋放記憶體代碼]
        delete [] arr;
        arr = nullptr;
    }

    // TODO 3: 實作模板 Push 函式
    // 提示：接收參數型態為 T 的 `val` ,你不是已經寫好了 TODO 3和4 了 我還要寫甚麼?
    void push(T val) {
        if (topIndex >= capacity - 1) {
            std::cout << "Stack Overflow!" << std::endl;
        } else {
            topIndex++;
            arr[topIndex] = val;
        }
        
    }

    // TODO 4: 實作模板 Pop 函式
    // 提示：回傳型態為 T
    T pop() {
        if (isEmpty()) {
            std::cout << "Stack Underflow!" << std::endl;
            // 由於 T 可能是任何型態，若發生錯誤，我們可以直接回傳 T 的預設值：`return T();`
            return T(); 
        } else {
            T val = arr[topIndex];
            topIndex--;
            return val;
        }
    }

    bool isEmpty() {
        return topIndex == -1;
    }
};

int main() {
    std::cout << "=== 1. 測試函式模板 ===" << std::endl;
    // C++ 會自動推導出 T 的型態！
    std::cout << "比較 10 和 20 的最大值: " << getMax(10, 20) << " (T 被自動推導為 int)" << std::endl;
    std::cout << "比較 3.14 和 2.71 的最大值: " << getMax(3.14, 2.71) << " (T 被自動推導為 double)" << std::endl;
    std::cout << "比較 'a' 和 'z' 的最大值: " << getMax('a', 'z') << " (T 被自動推導為 char)" << std::endl;

    std::cout << "\n=== 2. 測試類別模板 Box ===" << std::endl;
    // 宣告類別模板物件時，必須用 `<型態>` 告訴編譯器我們要裝什麼
    Box<std::string> stringBox("一隻可愛的黃金獵犬");
    std::cout << "字串盒子裡裝著: " << stringBox.getContent() << std::endl;

    Box<double> doubleBox(99.9);
    std::cout << "浮點數盒子裡裝著: " << doubleBox.getContent() << std::endl;

    std::cout << "\n=== 3. 測試模板化的 TemplateStack ===" << std::endl;
    
    // TODO 5: 宣告一個可以裝「字串 std::string」的 TemplateStack，容量設為 3。
    // 提示：語法為 `TemplateStack<型態> 變數名(容量);`
    // [在此寫下宣告代碼]
    TemplateStack<std::string> strStack(3);

   
    std::cout << "--- 正在推入字串資料到堆疊 ---" << std::endl;
    strStack.push("蘋果");
    strStack.push("香蕉");
    strStack.push("西瓜");

    std::cout << "--- 開始彈出字串資料 ---" << std::endl;
    while (!strStack.isEmpty()) {
        std::cout << "彈出: " << strStack.pop() << std::endl;
    }
    

    return 0;
}
