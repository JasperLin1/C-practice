#include <iostream>

// ========================================================
// 知識點: 什麼是佇列 (Queue)？
// ========================================================
// 佇列是一種「先進先出 (FIFO - First In First Out)」的資料結構。
// 想像在排隊買車票：
// - 新來的人只能排在隊伍的最後面 (Enqueue - 入隊)
// - 買好票的人從隊伍的最前面離開 (Dequeue - 出隊)
// - 排在最前面的人就是 Front (隊頭)
//
// 環形佇列 (Circular Queue) 觀念：
// - 如果只是單純把 front/rear 往後移，陣列前面出隊釋放的空間就再也用不到了。
// - 為了重複利用空間，我們把陣列的首尾相連，當指針走到陣列末端時，使用「模數運算子 (%)」讓它繞回開頭。
// - 我們在類別中多記錄一個 `count` 變數代表「目前隊伍中的人數」，這樣判斷空或滿就會變得超級簡單！

class Queue {
private:
    int* arr;         // 指向動態陣列的指標
    int capacity;     // 佇列的最大容量
    int front;        // 記錄隊頭 (最前面元素) 的索引位置
    int rear;         // 記錄隊尾 (下一個準備排隊位置) 的索引位置
    int count;        // 目前佇列中的元素個數 (人數)

public:
    // TODO 1: 實作建構子 (Constructor)
    // 提示：
    // - 初始化 `capacity = cap;`。
    // - 初始化 `front = 0;`, `rear = 0;`, `count = 0;`。
    // - 在 Heap 中動態配置一個大小為 capacity 的整數陣列，並讓 `arr` 指向它。
    // [在此寫下建構子代碼]
    Queue(int cap) {
        capacity = cap;
        front =0;
        rear = 0;
        count = 0;
        arr = new int[capacity];
    }

    // TODO 2: 實作解構子 (Destructor)
    // 提示：
    // - 用 `delete[] arr;` 釋放記憶體。
    // [在此寫下解構子代碼]
    ~Queue() {
        delete[] arr;
        arr = nullptr;
    }

    // TODO 3: 實作 Enqueue (入隊 / 排隊)
    // 提示：
    // - 函數名稱：`void enqueue(int val)`。
    // - 先檢查佇列是否滿了：如果 `count == capacity`，印出 "Queue Overflow!" 並直接結束。
    // - 如果沒滿：
    //   1. 把 `val` 放入隊尾位置：`arr[rear] = val;`。
    //   2. 將 `rear` 指標移到下一個位置。因為是環形佇列，使用相除求餘數來繞回開頭：`rear = (rear + 1) % capacity;`。
    //   3. 將元素個數 `count` 加 1。
    // [在此寫下 enqueue 函式]
    void enqueue(int val) {
        // 關鍵修正：必須使用雙等號 `==` 進行比較！
        // 如果寫成單等號 `count = capacity`，會變成「賦值」動作，將 capacity 的值寫入 count，且條件判斷永遠為真！
        // 這裡我們直接使用寫好的 `isFull()` 來判斷，最安全也最漂亮！
        if (isFull()) {
            std::cout << "Queue Overflow!" << std::endl;
        } else {
            arr[rear] = val;
            rear = (rear + 1) % capacity;
            count++;
        }
    }

    // TODO 4: 實作 Dequeue (出隊 / 離開隊伍)
    // 提示：
    // - 函數名稱：`int dequeue()`。
    // - 先檢查佇列是否為空：如果 `isEmpty()` 為真，印出 "Queue Underflow!" 並回傳 -1。
    // - 如果不為空：
    //   1. 用變數記錄隊頭的值：`int val = arr[front];`。
    //   2. 將 `front` 指標移到下一個位置 (環形繞回)：`front = (front + 1) % capacity;`。
    //   3. 將元素個數 `count` 減 1。
    //   4. 回傳記錄的 `val`。
    // [在此寫下 dequeue 函式]
    int dequeue() {
        if(isEmpty()){
            std::cout << "Queue underflow" << std::endl;
            return -1;
        }else{
            int val = arr[front];
            front = (front+1) % capacity;
            count--;
            return val; // 請修改它
        }

        
    }

    // TODO 5: 實作 Peek (看隊伍最前面是誰，但不移出)
    // 提示：
    // - 函數名稱：`int peek()`。
    // - 如果為空，回傳 -1，否則回傳 `arr[front]`。
    // [在此寫下 peek 函式]
    int peek() {
        if(isEmpty()){
            return -1; // 請修改它
        }else{
            return arr[front];
        }
        
    }

    // TODO 6: 實作判斷是否為空、是否為滿以及取得人數的公開函式
    // 提示：
    // - `isEmpty()`: 當 `count == 0` 時為真。
    // - `isFull()`: 當 `count == capacity` 時為真。
    // - `getSize()`: 回傳 `count`。
    // [在此寫下這三個輔助函式]
    bool isEmpty() {
        return count == 0; // 請修改它
    }
    
    bool isFull() {
        return count == capacity; // 請修改它
    }
    
    int getSize() {
        return count; // 請修改它
    }
};

int main() {
    std::cout << "=== 創建一個容量為 3 的佇列 ===" << std::endl;
    Queue myQueue(3);

    std::cout << "--- 測試 Enqueue (排隊) ---" << std::endl;
    myQueue.enqueue(10);
    myQueue.enqueue(20);
    myQueue.enqueue(30);
    
    // 嘗試排第 4 個人 (應該會爆掉，顯示 Queue Overflow!)
    std::cout << "嘗試推入第 4 個資料 (40)..." << std::endl;
    myQueue.enqueue(40);

    std::cout << "\n目前隊伍人數: " << myQueue.getSize() << " 人" << std::endl;
    std::cout << "排在最前面的是: " << myQueue.peek() << std::endl;

    std::cout << "\n--- 測試 Dequeue (先進先出離開隊伍) ---" << std::endl;
    std::cout << "出隊: " << myQueue.dequeue() << std::endl; // 應該是 10
    std::cout << "出隊: " << myQueue.dequeue() << std::endl; // 應該是 20

    std::cout << "\n--- 測試環形重複利用空間 (Enqueue 40 和 50) ---" << std::endl;
    // 因為前面走了兩個人，隊伍空出兩個位置，這時候可以繼續排隊！
    myQueue.enqueue(40);
    myQueue.enqueue(50);

    // 依序出隊，應該會看到 30 ➡️ 40 ➡️ 50 (先進先出)
    std::cout << "\n--- 依序出隊剩餘所有人 ---" << std::endl;
    // TODO 7: 寫一個 while 迴圈，只要 myQueue 不是空的，就一直呼叫 dequeue 並印出值。
    while (!myQueue.isEmpty()) {
        std::cout << "出隊: " << myQueue.dequeue() << std::endl;
    }

    return 0;
}
