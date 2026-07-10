#include <iostream>

// ========================================================
// 知識點 1: 定義鏈結串列的節點 (Node)
// ========================================================
// 每個節點就像是一節火車車廂。
// 它必須裝載兩樣東西：
// 1. 資料本身 (data)
// 2. 指向下一節車廂位置的指標 (next)
struct Node {
    int data;     // 車廂裡的乘客/貨物 (資料)
    Node* next;   // 指向下一節車廂的地址指標 (下一個節點)
};

int main() {
    std::cout << "=== 1. 手動創建與串接節點 ===" << std::endl;

    // TODO 1: 在 Heap (堆) 中動態配置三個節點空間
    // 提示：使用 `new Node`，用 Node* 型態的指標變數來裝地址
    // [在此寫下代碼，分別宣告 Node* head, Node* second, Node* third]
    Node* head = new Node;
    Node* second = new Node;
    Node* third = new Node;

    // TODO 2: 給這三個節點賦予資料，並把它們串起來！
    // 說明：「賦予資料」是指把我們要存的數值 (例如 10, 20, 30) 存入節點的 data 變數中。
    head->data = 10;
    second->data = 20;
    third->data = 30;

    // 連結指標：把車廂一節一節串起來
    head->next = second; 
    second->next = third;
    third->next = nullptr; // 最後一節後面沒人了，設為空地址 nullptr




    // ========================================================
    // 知識點 2: 遍歷鏈結串列 (Traversal)
    // ========================================================
    std::cout << "=== 2. 遍歷並印出鏈結串列的內容 ===" << std::endl;

    // TODO 3: 寫一個 while 迴圈，從頭節點 (head) 開始，一個接一個往後印出所有節點的 data
    Node* current = head;
    while(current != nullptr){
        std::cout << current->data << " -> ";
        current = current->next;
    }



    std::cout << "nullptr" << std::endl;

    // ========================================================
    // 知識點 3: 記憶體釋放 (Memory Cleanup)
    // ========================================================
    std::cout << "\n=== 3. 釋放所有節點的記憶體 ===" << std::endl;

    // TODO 4: 因為這三個節點都是用 `new` 申請的，我們必須把它們都 `delete` 掉防止記憶體洩漏！
    
    // 解答你的疑問 1：前面 TODO 3 執行完後，current 已經變成 nullptr 了！
    // 所以我們必須重新把它指回火車頭 head：
    current = head; 

    while(current != nullptr){
        // 每一輪都要先記下「下一站的地址」，因為等一下 delete current 後，current->next 就會消失！
        Node* nextNode = current->next; 
        
        delete current;      // 釋放當前車廂
        current = nextNode;  // 走到下一站
    }


    std::cout << "所有節點記憶體釋放完畢！" << std::endl;

    return 0;
}
