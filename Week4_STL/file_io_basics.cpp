#include <iostream>
#include <string>
#include <vector>
#include <fstream> // 核心：進行檔案讀寫必須引入此標頭檔 (File Stream)

// 定義一個簡單的學生結構體，用來裝讀取出來的資料
struct Student {
    std::string name;
    int score;
};

// ========================================================
// 🎯 Week 4: Day 26 - 檔案讀寫 (File I/O) 基礎
// ========================================================
// 到目前為止，我們寫的所有資料（學生成績、購物清單、排隊號碼）只要程式一關閉，
// 就會從記憶體中完全消失。
// 為了讓資料可以「永久保存」，我們必須學會如何讀寫檔案！
//
// 核心工具：
// 1. `std::ofstream` (Output File Stream) ➡️ 用於「寫入」檔案（寫入硬碟）。
// 2. `std::ifstream` (Input File Stream) ➡️ 用於「讀取」檔案（從硬碟讀進記憶體）。

int main() {
    std::string filename = "students_data.txt";

    // ========================================================
    // 💾 1. 寫入檔案 (Writing to File)
    // ========================================================
    std::cout << "=== 1. 正在寫入資料到檔案: " << filename << " ===" << std::endl;

    // TODO 1: 建立輸出檔案流物件，開啟名為 filename 的檔案。
    // 提示：`std::ofstream outFile(filename);`
    // [在此寫下代碼]
    std::ofstream outFile(filename);


    // TODO 2: 檢查檔案是否成功開啟。如果成功，寫入三筆學生姓名與分數。
    if(outFile.is_open()){
        // 解答你的疑問：
        // 1. outFile 是「管線」，指向學生的檔案。我們可以用 `<<` 將資料丟進管線，資料就會被寫入學生的檔案。
        // 2. 寫入三筆資料，我們可以用空格分隔名字與分數，並且每一筆換一行 (endl)。
        //    這樣以後讀取時，電腦才能輕易用空白辨認出名字和分數！
        outFile << "Jasper" << " " << 98 << std::endl;
        outFile << "Bob" << " " << 80 << std::endl;
        outFile << "Alice" << " " << 92 << std::endl;
        
        outFile.close(); // 寫完一定要關閉檔案管線！
    }


    // ========================================================
    // 📖 2. 讀取檔案 (Reading from File)
    // ========================================================
    std::cout << "\n=== 2. 正在從檔案讀取資料 ===" << std::endl;

    // 宣告一個 vector，用來儲存從檔案讀進來的學生資料
    std::vector<Student> loadedStudents;

    // TODO 3: 建立輸入檔案流物件。
    std::ifstream inFile(filename);


    // TODO 4: 檢查檔案是否成功開啟。如果成功，用 while 迴圈一行行讀取資料。
    std::string tempName;
    int tempScore;
    if(inFile.is_open()){
        // 迴圈每次讀取一對名字與分數
        while(inFile >> tempName >> tempScore ){
            // 解答你的疑問：
            // 我們的 loadedStudents 是一個裝「Student 結構體」的 vector (卡車)。
            // 可是從檔案讀出來的 tempName 是 string，tempScore 是 int。
            // 我們不能直接把 string 或 int 丟進裝 Student 的卡車！
            // 所以我們必須：
            // 1. 先摺好一個空的紙箱 `Student s;`
            // 2. 把名字和分數放進紙箱：`s.name = tempName; s.score = tempScore;`
            // 3. 把打包好的紙箱裝上卡車：`loadedStudents.push_back(s);`
            Student s; 
            s.name = tempName; 
            s.score = tempScore;
            loadedStudents.push_back(s);
        }
        inFile.close();
    }
    


    // ========================================================
    // 📊 3. 驗證讀取結果
    // ========================================================
    std::cout << "\n=== 3. 驗證從檔案讀取的資料是否成功 ===" << std::endl;
    // TODO 5: 使用你剛剛學會的 Range-based for 迴圈，印出 loadedStudents 裡所有學生的姓名與分數！
    
    // 解答你的疑問與修正：
    // 1. `loadedStudents` 裡面裝的每個東西型態是 `Student`（也就是紙箱）。
    // 2. 語法是 `for (元素型態 變數名 : 容器名)`。
    // 3. 所以要宣告為 `Student s`，這樣每一輪 `s` 就代表那一個學生！
    // 4. 透過 `s.name` 和 `s.score` 就可以讀取資料。
    for(Student s : loadedStudents) {
        std::cout << "姓名: " << s.name << ", 分數: " << s.score << std::endl;
    } 


    return 0;
}
