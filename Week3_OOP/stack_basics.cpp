#include <iostream>

// ========================================================
// 知識點: 什麼是堆疊 (Stack)？
// ========================================================
// 堆疊是一種「後進先出 (LIFO - Last In First Out)」的資料結構。
// 想像一疊盤子：
// - 你只能把新盤子放到最上面 (Push)
// - 你拿盤子也只能從最上面拿 (Pop)
// - 你看盤子也只能看到最上面那一個 (Top/Peek)
//
// 本次練習：我們將使用物件導向 (Class) 的封裝特性，
// 在內部使用「動態陣列 (new[])」來手動實作一個 Stack 類別！

class Stack {
private:
    int* arr;         // 指向動態陣列的指標 (用來存堆疊裡的資料)
    int capacity;     // 堆疊的最大容量
    int topIndex;     // 記錄目前最上方元素的位置 (索引)。如果堆疊是空的，設為 -1。

public:
    // TODO 1: 實作建構子 (Constructor)
    Stack(int cap) {
        capacity = cap;
        topIndex = -1;
        // 關鍵修正：直接使用成員變數 arr，不要在前面加上 int*！
        // 如果寫了 int* arr，會宣告出一個「全新的局部指標」，這會導致原本的成員變數 arr 依然是空指針，並且造成記憶體洩漏。
        arr = new int[capacity]; 
    }

    // TODO 2: 實作解構子 (Destructor)
    ~Stack() {
        delete[] arr;
        arr = nullptr;
    }

    // TODO 3: 實作 Push (將資料壓入堆疊)
    void push(int val) {
        if(topIndex >= capacity - 1){
            std::cout << "Stack Overflow!" << std::endl;
        }else{
            topIndex++;
            arr[topIndex] = val;
        }
    }

    // TODO 4: 實作 Pop (將最上方資料彈出並回傳)
    int pop() {
        // 關鍵修正：在類別內部的成員函式，直接呼叫 `isEmpty()` 即可，不需要寫 `arr.` 或 `Stack.`
        if (isEmpty()) {
            std::cout << "Stack Underflow!" << std::endl;
            return -1; // 發生錯誤時回傳 -1
        } else {
            int topVal = arr[topIndex];
            // 關鍵修正：用 `topIndex--` 或是 `topIndex = topIndex - 1;` 才能修改變數的值。
            // 只寫 `topIndex - 1;` 電腦只是算了一下，並不會把值存回去！
            topIndex--; 
            return topVal; 
        }
    }

    // TODO 5: 實作 Peek/Top (只看最上方資料，但不彈出)
    int peek() {
        // 關鍵修正：直接呼叫同一個類別內部的 `isEmpty()` 即可！
        if (isEmpty()) { 
            return -1;
        } else {
            return arr[topIndex]; 
        }
    }

    // TODO 6: 實作判斷是否為空的公開函式
    bool isEmpty() {
        // 說明：這是一個「判斷」，使用 if 或者直接 return 關係式即可，不需要使用 while 迴圈。
        return topIndex == -1; // 當 topIndex 是 -1 時回傳 true，否則回傳 false
    }
};

int main() {
    std::cout << "=== 創建一個容量為 3 的堆疊 ===" << std::endl;
    // 宣告一個容量為 3 的 Stack 物件 (在 Stack 記憶體中宣告，但內部陣列在 Heap 中)
    Stack myStack(3);

    std::cout << "--- 測試 Push 資料 ---" << std::endl;
    myStack.push(10);
    myStack.push(20);
    myStack.push(30);

    // 嘗試推入第 4 個資料 (應該會爆掉，顯示 Stack Overflow!)
    std::cout << "嘗試推入第 4 個資料 (40)..." << std::endl;
    myStack.push(40);

    std::cout << "\n--- 測試 Peek (看最上方資料) ---" << std::endl;
    std::cout << "目前最上方的資料是 (應該是 30): " << myStack.peek() << std::endl;

    std::cout << "\n--- 測試 Pop (後進先出彈出資料) ---" << std::endl;
    // 解除下方註解進行測試：
    while (!myStack.isEmpty()) {
        std::cout << "彈出資料: " << myStack.pop() << std::endl;
    }

    // 再次嘗試彈出 (應該會顯示 Stack Underflow!)
    std::cout << "再次嘗試彈出: " << myStack.pop() << std::endl;

    return 0;
}
