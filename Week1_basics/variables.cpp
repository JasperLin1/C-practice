#include <iostream>
#include <string>

int main() {
    // 1. 宣告各種型態的變數
    // 請在這裡宣告：
    // - 一個整數變數 age (代表年齡)
    //int age;
    // - 一個小數變數 height (代表身高，例如 175.5)
    double height;
    // - 一個字元變數 grade (代表成績等第，例如 'A')
    char grade;
    // - 一個布林值變數 isStudent (代表是否是學生，設為 true 或 false)
    bool isStudent;
    // - 一個字串變數 nickname (代表綽號)
    std :: string nickname;
    
    // 2. 賦值 (給予變數初始值)
    int age = 20;
    height = 175.5;
    grade = 'A';
    isStudent = true;
    nickname = "Jasper";

    // 3. 輸出這些變數的值到螢幕上
    std::cout << "--- 初始值 ---" << std::endl;
    std::cout << "年齡: " << age << std::endl;
    std::cout << "身高: " << height << std::endl;
    std::cout << "成績等第: " << grade << std::endl;
    std::cout << "是否為學生: " << (isStudent ? "是" : "否") << std::endl;
    std::cout << "綽號: " << nickname << std::endl;

    // 4. 【進階挑戰】
    // 使用 std::cin 讓使用者自己輸入他們的年齡、身高、綽號，並印出來！
    std::cout << "\n--- 請輸入新的資料 ---" << std::endl;
    std::cout << "請依序輸入 [年齡] [身高] [綽號] (中間用空白或 Enter 隔開): ";
    
    // 關鍵修正：在 C++ 中，多個輸入必須使用 >> 連接，不能使用逗號 ,
    std::cin >> age >> height >> nickname;

    std::cout << "\n--- 你輸入的資料 ---" << std::endl;
    std::cout << "更新後的年齡: " << age << std::endl;
    std::cout << "更新後の身高: " << height << std::endl;
    std::cout << "更新後的綽號: " << nickname << std::endl;

    return 0;
}
