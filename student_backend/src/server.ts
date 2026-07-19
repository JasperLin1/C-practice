// ========================================================
// 📄 src/server.ts
// ========================================================
// 這是我們伺服器的「總入口 (Entry Point)」。
// 在大型專案中，這裡的職責非常單純：
// 1. 初始化 Express 伺服器與設定連接埠 (Port)。
// 2. 載入全域中間件 (Cors, JSON 解析等)。
// 3. 掛載路由 (Routers) ── 就像是把不同部門的電話分機接進總機。

import express, { Request, Response } from 'express';
import cors from 'cors';
import studentRouter from './routes/studentRoutes'; // 載入我們即將編寫的學生部門路由

const app = express();
const PORT = 5000;

// 1. 全域中間件
app.use(cors());
app.use(express.json());

// 2. 掛載 API 路由
// 依照業界標準，我們會給 API 加上 "/api" 的前綴，方便跟前端靜態網頁做區隔
app.use('/api/students', studentRouter);

// 3. 根路徑測試 API
app.get('/', (req: Request, res: Response) => {
    res.send('學生成績管理系統 API 服務已成功啟動！');
});

// 4. 監聽啟動
app.listen(PORT, () => {
    console.log(`後端伺服器運行於: http://localhost:${PORT}`);
});
