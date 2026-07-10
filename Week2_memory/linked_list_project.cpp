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

}

// TODO 2: 在鏈結串列中尋找特定的數值
// 提示：
// - 從 head 開始遍歷鏈結串列，比對每個節點的 data。
// - 如果找到，回傳 true。
// - 如果遍歷完整個串列都沒找到，回傳 false。
// [在此寫下你的 search 函式]
bool search(Node* head, int target) {

    return false; // 暫時回傳 false，請修改它
}

// TODO 3: 釋放鏈結串列中所有節點的記憶體
// 提示：
// - 使用你在 linked_list_basics.cpp 中學到的安全釋放迴圈。
// - 釋放完所有節點後，記得將 `head` 設為 `nullptr`，防止它變成懸空指標！
// [在此寫下你的 clear 函式]
void clear(Node*& head) {

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
