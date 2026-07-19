// ========================================================
// 📄 src/routes/studentRoutes.ts
// ========================================================
// 這是我們學生的「分機路由 (Router)」。
// 它負責接收前端發送過來的各種 HTTP 請求，並對應到適當的業務邏輯。
// 
// 💡 RESTful API 設計標準：
// - GET    /api/students      ➡️ 取得所有學生資料
// - POST   /api/students      ➡️ 新增一位學生資料
// - PUT    /api/students/:id  ➡️ 修改指定學號的學生成績
// - DELETE /api/students/:id  ➡️ 刪除指定學號的學生

import { Router, Request, Response } from 'express';
import { readData, writeData } from '../services/dbService';
import { Student } from '../types/student';

const router = Router();

// TODO 6: 取得所有學生 (GET /api/students)
router.get('/', (req: Request, res: Response) => {
    // 解答你的疑問：為什麼要用 students 變數存 readData()？
    // 答：因為這樣我們才能拿到讀出來的資料，並在下一行把它丟給 res.json(students)。
    // （當然也可以直接寫 res.json(readData())，但存成變數更清楚易讀！）
    const students = readData(); 
    res.json(students); 
});

// TODO 7: 新增學生 (POST /api/students)
router.post('/', (req: Request, res: Response) => {
    // 關鍵修正 1：req.body 是一個「物件屬性」，不是函式！不能加括號 ()，否則會當機。
    const { id, name, score } = req.body;
    
    // 解答你的疑問：變數不用標註型態嗎？
    // 答：不用！因為 TypeScript 有「型態推導 (Type Inference)」。
    // 由於 readData() 已經宣告回傳 Student[]，TS 就知道 students 必定是陣列，可以直接使用陣列的所有方法。
    const students = readData(); 
    
    // 檢查學號是否重複
    if (students.some(s => s.id === id)) {
        return res.status(400).json({ message: '學號已存在！' });
    }
    
    // 解答你的疑問：students.push() 括號裡寫什麼？
    // 答：我們要塞入一個符合 Student 結構的「物件」，在 JS/TS 中物件是用大括號 `{}` 表示。
    // `{ id, name, score: Number(score) }` 就是把變數包裝成物件放進去！
    students.push({ 
        id, 
        name, 
        score: Number(score) // 確保轉為數字
    });
    
    writeData(students);
    res.status(201).json({ message: '新增成功！' });
});

// TODO 8: 修改學生成績 (PUT /api/students/:id)
router.put('/:id', (req: Request, res: Response) => {
    // 關鍵修正 2：學號 id 是放在網址參數中的 (:id)，所以要用 `req.params.id` 取得！
    // 分數 score 則是前端用 JSON 包裹在 body 裡送來的，用 `req.body` 取得。
    const { id } = req.params;
    const { score } = req.body;
    
    const students = readData();
    
    // 解答你的疑問：如何寫找到後，修改其 score？
    // 答：我們用陣列內建的 `.find()` 尋找符合學號的學生。
    const student = students.find(s => s.id === id);
    
    if (!student) {
        return res.status(404).json({ message: '找不到該學生！' });
    }
    
    // 找到學生了，直接修改他的分數
    student.score = Number(score);
    
    // 寫入檔案保存
    writeData(students);
    res.json({ message: '成績修改成功！' });
});

// TODO 9: 刪除學生 (DELETE /api/students/:id)
router.delete('/:id', (req: Request, res: Response) => {
    // 關鍵修正 3：從網址參數 `req.params` 取得 id
    const { id } = req.params;
    const students = readData();
    
    // 解答你的疑問 1：為什麼要用過濾 (.filter) 掉的方式？
    // 答：在 JS 陣列中，刪除最直覺的做法是「過濾」。
    // `s.id !== id` 代表「留下學號不等於我們要刪除的那些學生」。
    // 這樣，被刪除的學生就會被排除在新陣列之外！
    const updatedStudents = students.filter(s => s.id !== id); //意思是幫我篩選出學號『不等於』我要刪除學號的那些人，組成一個新陣列
    
    // 解答你的疑問 2：為什麼長度沒變代表找不到學生？怎麼寫？
    // 答：如果原本有 3 個人，你想刪除一個「不存在的學號」（如 S999）。
    // 過濾完後，那 3 個人還是會留下來（長度還是 3）。
    // 所以，如果 `updatedStudents.length === students.length`，就代表「根本沒有人被刪掉」➡️ 找不到人！
    if (updatedStudents.length === students.length) {
        return res.status(404).json({ message: '找不到該學生！' });
    }
    
    // 存入過濾後的新名單
    writeData(updatedStudents);
    res.json({ message: '刪除成功！' });
});

export default router;
