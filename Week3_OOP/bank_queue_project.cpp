#include <iostream>
#include <string>

// ========================================================
// 這是我們剛剛寫好的 Queue 類別 (直接拿來當工具使用！)
// ========================================================
class Queue {
private:
    int* arr;
    int capacity;
    int front;
    int rear;
    int count;

public:
    Queue(int cap) {
        capacity = cap;
        front = 0;
        rear = 0;
        count = 0;
        arr = new int[capacity];
    }
    ~Queue() {
        delete[] arr;
        arr = nullptr;
    }
    void enqueue(int val) {
        if (!isFull()) {
            arr[rear] = val;
            rear = (rear + 1) % capacity;
            count++;
        }
    }
    int dequeue() {
        if (isEmpty()) return -1;
        int val = arr[front];
        front = (front + 1) % capacity;
        count--;
        return val;
    }
    int peek() {
        if (isEmpty()) return -1;
        return arr[front];
    }
    bool isEmpty() {
        return count == 0;
    }
    bool isFull() {
        return count == capacity;
    }
    int getSize() {
        return count;
    }
};

// ========================================================
// 🎯 Week 3 整合小專案：銀行排隊叫號系統
// ========================================================
// 這是你第三週的總結專案！它將會結合：
// 1. 物件導向封裝 (使用你手寫的 Queue 類別作為核心排隊引擎)
// 2. 流程控制 (使用 while 迴圈與 switch 做出互動選單)
//
// 系統規格：
// - 銀行一天最多服務 100 個號碼 (Queue 容量設為 100)。
// - 取號機自動發號：從號碼 1001 開始遞增（1001, 1002, 1003...）。
// - 櫃檯叫號：依序叫出下一個號碼，並從隊伍中移出。
// - 狀態查詢：印出目前隊伍中有幾個人在排隊，以及下一個準備接受服務的號碼。


int main() {
    // 1. 宣告一個容量為 100 的排隊佇列
    Queue bankQueue(100);

    int nextTicketNumber = 1001; // 下一個要發放的號碼牌
    int choice = 0;

    std::cout << "========================================" << std::endl;
    std::cout << "🏦 歡迎使用 模擬銀行排隊叫號系統" << std::endl;
    std::cout << "========================================" << std::endl;

    // TODO: 實作互動式叫號選單
    // 提示步驟：
    // 1. 使用 while (choice != 4) 寫一個選單迴圈。
    // 2. 在迴圈內部：
    //    a. 印出選單項目：
    //       1. 民眾取號 (排隊)
    //       2. 櫃檯叫號 (出隊)
    //       3. 查看排隊狀況
    //       4. 系統結束
    //    b. 用 std::cin 讀入 choice。
    //    c. 使用 switch (choice) 處理不同選項：
    //       - 情況 1 (民眾取號)：
    //         - 先檢查 myQueue 是否滿了 (bankQueue.isFull())。若滿了，顯示「目前排隊人數已滿，請稍後再試。」
    //         - 若沒滿，將 `nextTicketNumber` 加入隊伍：`bankQueue.enqueue(nextTicketNumber);`
    //         - 印出「您的號碼牌是：X，前面有 Y 個人在等候。」(提示：前面等候人數為 `bankQueue.getSize() - 1`)
    //         - 將 `nextTicketNumber` 加 1。
    //       - 情況 2 (櫃檯叫號)：
    //         - 先檢查隊伍是否為空 (bankQueue.isEmpty())。若空，顯示「目前無人排隊。」
    //         - 若不為空，呼叫 dequeue() 叫出號碼：`int servedNum = bankQueue.dequeue();`
    //         - 印出「請號碼牌 X 號民眾至 1 號櫃檯辦理業務！」
    //       - 情況 3 (查看排隊狀況)：
    //         - 印出「目前排隊人數：X 人」 (bankQueue.getSize())
    //         - 印出「下一位服務對象：Y 號」 (bankQueue.peek())，若為空則顯示無人排隊。
    //       - 情況 4 (離開)：
    //         - 印出「系統結束，祝您美好的一天！」
    // [在此寫下你的選單迴圈與 switch 邏輯程式碼]
    while(choice != 4){
        std::cout << "\n----------------------------------------" << std::endl;
        std::cout << "1. 民眾取號 (Enqueue)" << std::endl;
        std::cout << "2. 櫃檯叫號 (Dequeue)" << std::endl;
        std::cout << "3. 查看排隊狀況 (Peek/Size)" << std::endl;
        std::cout << "4. 離開系統 (Exit)" << std::endl;
        std::cout << "請輸入選項 (1-4): ";
        std ::cin >> choice;
        std::cout << "----------------------------------------" << std::endl;
        
        switch(choice){
            case 1: // 關鍵修正 1：因為 choice 是 int，這裡必須寫數字 1，不能寫字元 '1'！
                if(bankQueue.isFull()){
                    std::cout << "目前排隊人數已滿，請稍後再試。" << std::endl;
                }else{
                    // 關鍵修正 2：入隊只要呼叫 `bankQueue.enqueue(值);` 即可，不能在後面寫 `= 值`。
                    bankQueue.enqueue(nextTicketNumber);
                    
                    // 關鍵修正 3：民眾的號碼牌是 `nextTicketNumber`，不是 `bankQueue.getSize()`。
                    std::cout << "您的號碼牌是: " << nextTicketNumber 
                              << "，前面有 " << bankQueue.getSize() - 1 << " 個人在等候。" << std::endl;
                    
                    nextTicketNumber++; // 號碼牌遞增
                }
                break; // 關鍵修正 4：break 應該放在整個 case 的最外圍，確保無論走 if 還是 else 都會安全中斷，防止滑落到下一個 case。

            case 2:
                if(bankQueue.isEmpty()){
                    std::cout << "目前無人排隊。" << std::endl; 
                }else{
                    int servedNum = bankQueue.dequeue();
                    std::cout << "請號碼牌 " << servedNum << " 號民眾至 1 號櫃檯辦理業務！" << std::endl;
                }
                break;

            case 3:
                std::cout << "目前排隊人數: " << bankQueue.getSize() << " 人" << std::endl;
                if (bankQueue.isEmpty()) {
                    std::cout << "下一位服務對象: 目前無人排隊" << std::endl;
                } else {
                    std::cout << "下一位服務對象: " << bankQueue.peek() << " 號" << std::endl;
                }
                break;

            case 4:
                std::cout << "系統結束，祝您美好的一天！" << std::endl;
                break;

            default:
                std::cout << "無效的選項，請輸入 1-4 之間的數字。" << std::endl;
                break;
        }
    }


    return 0;
}
