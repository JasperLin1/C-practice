// ========================================================
// 📄 src/services/dbService.ts
// ========================================================
// 這是我們的「資料存取層 (Data Access Layer)」。
// 大公司非常看重「職責分離」：
// 如果以後公司決定把資料從 JSON 檔案改存到 MySQL 或 MongoDB 資料庫，
// 我們「只需要修改這個檔案」裡面的讀寫邏輯，其他路由 (Routes) 和前端代碼完全不需要改動！
// 這就是高延展性系統的精髓。

import fs from 'fs';
import { Student } from '../types/student'; // 匯入剛剛獨立出去的型態

const DB_FILE = 'students.json';

export function readData(): Student[] {
    // 1. 如果檔案不存在，代表目前完全沒有學生資料，直接回傳空陣列
    if (!fs.existsSync(DB_FILE)) {
        return [];
    }
    
    // 2. 讀取硬碟中的文字檔案
    const dataText = fs.readFileSync(DB_FILE, 'utf-8');
    
    // 3. 關鍵概念：
    //    硬碟裡的檔案存的是「純文字字串」，但程式碼裡我們需要「可操作的陣列物件」。
    //    `JSON.parse(dataText)` 就是這個翻譯官：把純文字轉回 C++ 陣列 (TS 中的 Object Array)。
    return JSON.parse(dataText) as Student[];
}

// TODO 5: 實作「寫入檔案」函式
export function writeData(data: Student[]): void {
    // 1. 翻譯官：把我們的 Student 陣列物件轉成 JSON 純文字字串。
    //    - data: 要轉換的資料。
    //    - null: 不過濾任何欄位。
    //    - 2: 縮排 2 格空白（這樣我們打開 JSON 檔時，排版會非常漂亮好讀，不會縮成一行）。
    const jsonString = JSON.stringify(data, null, 2);
    
    // 2. 寫入硬碟覆蓋舊檔案
    fs.writeFileSync(DB_FILE, jsonString);
}
