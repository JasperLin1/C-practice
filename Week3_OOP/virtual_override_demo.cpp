#include <iostream>
#include <string>

// ========================================================
// 1. 父類別 (Base Class)：銀行帳戶
// ========================================================
class BankAccount {
protected: // protected 代表：只有自己和子類別可以存取，外部摸不到
    std::string ownerName;
    double balance;

public:
    BankAccount(std::string name, double initialBalance) {
        ownerName = name;
        balance = initialBalance;
    }

    // 關鍵點 1: 使用 `virtual` 宣告虛擬函式
    // 意思是：我允許子類別覆寫這個計算利息的行為。
    virtual void calculateInterest() {
        double interest = balance * 0.01; // 一般帳戶：利息 1%
        std::cout << "【一般帳戶】" << ownerName << " 的利息是: $" << interest << std::endl;
    }

    // 解構子必須宣告為 virtual！這是一個非常重要的 C++ 安全規則 (稍後會解釋)。
    virtual ~BankAccount() {}
};

// ========================================================
// 2. 子類別 1：VIP 帳戶 (繼承 BankAccount)
// ========================================================
class VIPAccount : public BankAccount {
public:
    // 呼叫父類別的建構子來初始化資料
    VIPAccount(std::string name, double balance) : BankAccount(name, balance) {}

    // 關鍵點 2: 使用 `override` 覆寫父類別的虛擬函式
    // 意思是：VIP 帳戶的利息計算方式與一般人不同！
    void calculateInterest() override {
        double interest = balance * 0.05; // VIP 帳戶：利息 5%
        std::cout << "★【VIP 帳戶】" << ownerName << " 的利息是: $" << interest 
                  << " (享有 VIP 專屬 5% 高利息！)" << std::endl;
    }
};

// ========================================================
// 3. 子類別 2：青年優存帳戶 (繼承 BankAccount)
// ========================================================
class YouthAccount : public BankAccount {
public:
    YouthAccount(std::string name, double balance) : BankAccount(name, balance) {}

    // 覆寫計算利息行為
    void calculateInterest() override {
        double interest = balance * 0.03; // 青年帳戶：利息 3%
        std::cout << "☘【青年優存】" << ownerName << " 的利息是: $" << interest << std::endl;
    }
};

// ========================================================
// 測試主程式
// ========================================================
int main() {
    std::cout << "=== 傳統做法：沒有多型時，必須分開宣告 ===" << std::endl;
    BankAccount normal("Jasper", 10000);
    VIPAccount vip("Bob", 10000);
    normal.calculateInterest();
    vip.calculateInterest();

    std::cout << "\n=== 強大做法：使用多型 (Polymorphism) ===" << std::endl;
    // 銀行經理的清單：用一個「父類別指標陣列」來裝所有不同類型的帳戶！
    BankAccount* accounts[3];

    accounts[0] = new BankAccount("一般顧客-陳先生", 10000);
    accounts[1] = new VIPAccount("VIP顧客-郭董", 10000); // 註：我們用 VIPAccount，這裡我寫 VIPAccount
    // 修正上面寫法：
    accounts[1] = new VIPAccount("VIP顧客-郭董", 10000);
    accounts[2] = new YouthAccount("青年顧客-林同學", 10000);

    // 經理只需要寫一個 simple loop 就能計算所有人的利息，完全不用管他是什麼帳戶！
    for (int i = 0; i < 3; i++) {
        // 核心魔法：因為 `calculateInterest` 是 virtual，
        // 雖然 accounts[i] 的型態都是 BankAccount*，
        // 但 C++ 會在執行時去尋找該物件真正的身分，並呼叫對應的 override 函式！
        accounts[i]->calculateInterest();
    }

    std::cout << "\n=== 釋放 Heap 記憶體 ===" << std::endl;
    for (int i = 0; i < 3; i++) {
        delete accounts[i]; // 這會觸發各個物件的解構子
    }

    return 0;
}
