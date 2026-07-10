#include <iostream>

struct Node {
    int data;
    Node* next;
};

// ========================================================
// 🎯 Week 2 整合小專案：單向鏈結串列管理器
// ========================================================
// 這個專案將結合你第二週所學的全部精髓：
// 指標、動態記憶體 (new/delete)、鏈結串列遍歷、以及「傳參考指標 (Node*& head)」。
//
// 請完成以下三個鏈結串列的核心操作函數：

// TODO 1: 在鏈結串列的「尾端」新增一個節點
// 提示：
// - 參數中的 `Node*& head` 代表傳入指標的參考（這樣當 head 為空時，修改 head 才會影響到外部）。
// - 步驟：
//   1. 創建一個新節點：`Node* newNode = new Node;`，賦值 `newNode->data = val;`，並將 `newNode->next = nullptr;`。
//   2. 如果目前鏈結串列是空的（也就是 `head == nullptr`），那這個新節點就是頭節點，直接讓 `head = newNode;` 即可。
//   3. 如果不是空的，宣告一個移動指標 `Node* temp = head;`，用 while 迴圈走到最末端節點（當 `temp->next == nullptr` 時停下）。
//   4. 將最末端節點的 next 指向新節點：`temp->next = newNode;`。
// [在此寫下你的 insert 函式]
void insert(Node*& head, int val) {
    // 1. 創建要接上去的新車廂 (new Node)
    Node* newNode = new Node;
    newNode->data = val;
    newNode->next = nullptr;

    // 2. 判斷火車是不是空的
    if (head == nullptr) {
        head = newNode; // 空的話，新車廂就是火車頭
    } else {
        // 3. 不為空時，我們需要一個「臨時紙條」來幫忙走訪到最後一站。
        // 注意：千萬不要在這裡寫 `new Node`，因為我們只是要建立一條「指向已有車廂的臨時紙條」，不是要造新車廂。
        Node* temp = head; 
        
        // 4. 只要「下一站不是 nullptr」，就一直往前走
        while (temp->next != nullptr) {
            temp = temp->next; // 走向下一站
        }
        
        // 5. 走到最後一節車廂了，把它的 next 接上新車廂
        temp->next = newNode;
    }
}

// TODO 2: 在鏈結串列中尋找特定的數值
// 提示：
// - 從 head 開始遍歷鏈結串列，比對每個節點的 data。
// - 如果找到，回傳 true。
// - 如果遍歷完整個串列都沒找到，回傳 false。
// [在此寫下你的 search 函式]
bool search(Node* head, int target) {
    // 說明：搜尋是唯讀的，不要在這裡 new Node 造新車廂！
    // 我們只需要一張臨時紙條 current，指向頭部開始往後找
    Node* current = head; 

    while (current != nullptr) {
        if (current->data == target) {
            return true; // 找到了！
        }
        current = current->next; // 移到下一站
    }
    
    return false; // 找遍了所有車廂都沒找到
}


// TODO 3: 釋放鏈結串列中所有節點的記憶體
// 提示：
// - 使用你在 linked_list_basics.cpp 中學到的安全釋放迴圈。
// - 釋放完所有節點後，記得將 `head` 設為 `nullptr`，防止它變成懸空指標！
// [在此寫下你的 clear 函式]
void clear(Node*& head) {
    // 說明：這裡確確實實是要「delete current」！
    // 因為如果只寫 `delete head;`，我們只刪除了第一節車廂，後面的車廂全都會遺失並殘留在記憶體中。
    
    Node* current = head;
    while (current != nullptr) {
        Node* nextNode = current->next; // 先記住下一站的地址
        delete current;                // 釋放當前車廂 (delete current 是完全正確的！)
        current = nextNode;            // 走向下一站
    }
    
    // 所有車廂都刪完了，把火車頭指標清空
    head = nullptr; 
}

// 輔助函式：印出整條鏈結串列 (已幫你寫好)
void printList(Node* head) {
    Node* temp = head;
    std::cout << "串列內容: ";
    while (temp != nullptr) {
        std::cout << temp->data << " -> ";
        temp = temp->next;
    }
    std::cout << "nullptr" << std::endl;
}

int main() {
    Node* myHead = nullptr; // 一開始鏈結串列是空的

    std::cout << "=== 1. 測試尾端新增節點 ===" << std::endl;
    insert(myHead, 10);
    insert(myHead, 20);
    insert(myHead, 30);
    insert(myHead, 40);
    printList(myHead); // 應該要印出: 10 -> 20 -> 30 -> 40 -> nullptr

    std::cout << "\n=== 2. 測試尋找數值 ===" << std::endl;
    int target = 30;
    if (search(myHead, target)) {
        std::cout << "找到了！數值 " << target << " 存在於串列中。" << std::endl;
    } else {
        std::cout << "找不到！數值 " << target << " 不存在於串列中。" << std::endl;
    }

    target = 99;
    if (search(myHead, target)) {
        std::cout << "找到了！數值 " << target << " 存在於串列中。" << std::endl;
    } else {
        std::cout << "找不到！數值 " << target << " 不存在於串列中。" << std::endl;
    }

    std::cout << "\n=== 3. 測試清空記憶體 ===" << std::endl;
    clear(myHead);
    printList(myHead); // 應該要印出: 串列內容: nullptr

    return 0;
}
