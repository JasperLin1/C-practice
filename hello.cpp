#include <iostream> // 引入輸入輸出庫
#include <string>   // 引入字串庫

int main() {
    // 輸出問候語
    std::cout << "Hello! 歡迎來到 C++ 的世界！" << std::endl;
    
    // 詢問使用者姓名
    std::cout << "請輸入你的名字: ";
    std::string name;
    std::cin >> name; // 從鍵盤讀取輸入並存入變數 name 中
    
    // 再次打招呼
    std::cout << "嗨，" << name << "！讓我們在一個月內征服 C++ 吧！" << std::endl;
    
    return 0;
}
