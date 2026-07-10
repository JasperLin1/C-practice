#include <iostream>

int main() {
    // ----------------------------------------------------
    // 1. 條件判斷 (If-Else)
    // ----------------------------------------------------
    std::cout << "=== 1. 奇偶數判斷 ===" << std::endl;
    std::cout << "請輸入一個整數: ";
    int number;
    std::cin >> number;

    // TODO: 請使用 if-else 判斷 number 是奇數還是偶數並印出結果。
    // 提示：用除以 2 的餘數判斷 (number % 2 == 0) 代表偶數。
    // [在此處寫下你的 if-else 程式碼]
    //int number;
    if(number % 2 ==0){
        std :: cout << "is even number";
    }else{
        std :: cout << "odd number";
    }

    // ----------------------------------------------------
    // 2. For 迴圈 (重複執行固定次數)
    // ----------------------------------------------------
    std::cout << "\n=== 2. For 迴圈印出 1 到 N ===" << std::endl;
    std::cout << "請輸入要印到多少 (N): ";
    int n;
    std::cin >> n;

    // TODO: 請寫一個 for 迴圈，從 1 印到 n。
    // 提示：for (int i = 1; i <= n; i++) { ... }
    // [在此處寫下你的 for 迴圈程式碼]
    for (int i =1; i <= n; i++){
        std :: cout << i << " ";
    }

    // ----------------------------------------------------
    // 3. While 迴圈與累加 (累加 1 到 N)
    // ----------------------------------------------------
    std::cout << "\n=== 3. While 迴圈計算 1 到 N 的總和 ===" << std::endl;
    
    int sum = 0;
    int counter = 1;

    // TODO: 請使用 while 迴圈，當 counter <= n 時，把 counter 加進 sum，並將 counter 加 1。
    // 提示：
    // while (counter <= n) {
    //     sum = sum + counter; // 或寫成 sum += counter;
    //     counter++;
    // }
    // [在此處寫下你的 while 迴圈程式碼]

    while(counter <= n){
        sum += counter;
        counter++;
    }

    std::cout << "1 到 " << n << " 的總合是: " << sum << std::endl;

    return 0;
}
