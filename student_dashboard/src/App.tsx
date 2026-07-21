//  'react' 庫匯入 React 本身，以及兩個最核心的 Hook 工具：useState (狀態管理) 與 useEffect (副作用處理)
import React, { useState, useEffect } from 'react';
// 匯入同目錄下的樣式檔案 App.css，用來給網頁套用外觀顏色與排版
import './App.css';

// ：定義「學生 (Student)」資料結構的介面 (Interface)。
// 這是 TypeScript 的強大功能：明確規定每一個學生資料必須包含 id(字串)、name(字串) 與 score(數字)。
interface Student {
  id: string;   // 學號
  name: string; // 姓名
  score: number; // 分數
}

// 定義主網頁組件 (Component) 函式，名稱為 App
function App() {
  // 宣告一個名為 `students` 的 State (狀態)。
  // `students` 裝著學生清單陣列，`setStudent` 是專門用來更新這個陣列的唯一函式。預設值為空陣列 `[]`。
  const [students, setStudent] = useState<Student[]>([]);

  // 宣告三個 State，分別用來即時儲存使用者在輸入框打的「學號」、「姓名」與「分數」
  const [inputId, setInputId] = useState('');
  const [inputName, setInputName] = useState('');
  const [inputScore, setInputScore] = useState('');
  // 宣告兩位新成員，用來紀錄「目前正在編輯哪一位學生的學號」以及「編輯中的新分數」
  const [editingId, setEditingId] = useState<string | null>(null);
  const [editingScore, setEditingScore] = useState('');

  // 定義一個專門向後端拿資料的函式 `fetchStudents`
  const fetchStudents = () => {
    // 使用瀏覽器內建的 fetch 向後端 API 發送 HTTP GET 請求
    fetch('http://localhost:5001/api/students')
      // 把後端回傳的原始 Response 翻譯解析成 JSON 物件
      .then(res => res.json())
      // 拿到解析後的學生陣列資料 (data)，呼叫 setStudent 更新 State。網頁畫面會自動重畫！
      .then(data => setStudent(data));
  };

  // 使用 useEffect 生命週期 Hook
  // 傳入空陣列 `[]` 作為第二個參數，代表「只在網頁第一次開啟載入時，自動執行內部的 fetchStudents() 一次」
  useEffect(() => {
    fetchStudents();
  }, []);

  // 定義按下「新增學生」按鈕時會發生的處理函式 `handleAdd`
  const handleAdd = (e: React.FormEvent) => {
    // 阻止表單的預設行為（預設點擊 submit 會刷新的網頁，我們要阻止它刷新）
    e.preventDefault();
    
    // 向後端 API 發送 HTTP POST 請求，準備寫入新資料
    fetch('http://localhost:5001/api/students', {
      method: 'POST', // 指定傳輸方法為 POST (新增)
      headers: { 'Content-Type': 'application/json' }, // 告訴後端我們送過去的是 JSON 格式的包裹
      // 把我們在輸入框存好的 state 變數，打包成 JSON 文字字串送給後端
      body: JSON.stringify({ id: inputId, name: inputName, score: Number(inputScore) })
    })
    // 等待後端處理完畢並回傳 Response，將其轉為 JSON
    .then(res => res.json())
    // 拿到後端回傳的結果 (data)
    .then(data => {
      // 跳出提示視窗，顯示後端傳來的訊息（如：「新增成功！」）
      alert(data.message); 
      
      // 清空網頁上的三個輸入框，讓使用者方便輸入下一個人
      setInputId('');
      setInputName('');
      setInputScore('');
      
      // 再次向後端抓取最新名單，畫面就會立刻多出剛剛新增的那個人！
      fetchStudents();
    });
  };

  // 定義按下「刪除」按鈕時會發生的處理函式 `handleDelete`
  const handleDelete = (id: string) => {
    // 關鍵修正：必須使用「反單引號 `...`」，變數 `${id}` 才會被正確替換成真實學號 (如 S001)！
    fetch(`http://localhost:5001/api/students/${id}`, {
      method: 'DELETE' // 指定傳輸方法為 DELETE (刪除)
    })
    .then(res => res.json())
    .then(data => {
      alert(data.message);
      fetchStudents();
    });
  };

  // 第 75-84 行：定義按下「儲存成績」時會發生的處理函式 `handleUpdateScore`
  const handleUpdateScore = (id: string) => {
    fetch(`http://localhost:5001/api/students/${id}`, {
      method: 'PUT',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify({ score: Number(editingScore) })
    })
    .then(res => res.json())
    .then(data => {
      alert(data.message);
      setEditingId(null);
      fetchStudents();
    });
  };

  // 📊 【Senior 進階功能】：動態數據統計計算 (Derived State)
  const totalCount = students.length;
  // 1. 計算全班平均分數
  const avgScore = totalCount > 0 
    ? Math.round((students.reduce((sum, s) => sum + s.score, 0) / totalCount) * 10) / 10 
    : 0;
  // 2. 計算及格率 (分數 >= 60)
  const passCount = students.filter(s => s.score >= 60).length;
  const passRate = totalCount > 0 ? Math.round((passCount / totalCount) * 100) : 0;
  // 3. 找出全班最高分與最低分學生
  const highestStudent = totalCount > 0 ? [...students].sort((a, b) => b.score - a.score)[0] : null;
  const lowestStudent = totalCount > 0 ? [...students].sort((a, b) => a.score - b.score)[0] : null;

  // 💡 【解答你的發問】：這個邏輯要寫在哪裡？
  // 答案：寫在 App() 內部、return(...) 的「外面」！
  // 因為條件判斷 (if-else) 是純 JavaScript 的邏輯運算，不能直接放在 JSX return 裡面。
  let lowestCardTitle = "需要加強 (最低分) ⚠️";
  let lowestCardSubText = "";
  let lowestCardColor = "var(--danger)"; // 預設紅色警告

  if (!lowestStudent) {
    lowestCardTitle = "需要加強 (最低分)";
    lowestCardSubText = "目前無資料";
    lowestCardColor = "var(--text-muted)";
  } else if (lowestStudent.score >= 80) {
    // 情境 B：所有人都在 80 分以上
    lowestCardTitle = "表現優異 🎉";
    lowestCardSubText = "全員皆達 80 分以上，目前無需加強！";
    lowestCardColor = "var(--success)"; // 綠色
  } else if (lowestStudent.score >= 60) {
    // 情境 C：無人不及格，但有人介於 60~79 分
    lowestCardTitle = "觀察對象 (60-79分) 💡";
    lowestCardSubText = `[${lowestStudent.id}] ${lowestStudent.name}`;
    lowestCardColor = "var(--warning)"; // 黃色警告
  } else {
    // 情境 D：有人不及格 (< 60 分)
    lowestCardTitle = "需要加強 (不及格) ⚠️";
    lowestCardSubText = `[${lowestStudent.id}] ${lowestStudent.name}`;
    lowestCardColor = "var(--danger)"; // 紅色警告
  }

  return (
    <div className="dashboard-container">
      {/* 頁首標題 */}
      <header>
        <div style={{ display: 'flex', alignItems: 'center', gap: '12px' }}>
          <span style={{ fontSize: '24px', fontWeight: 'bold' }} className="text-gradient">
            Senior GradeManager™ (全端整合版)
          </span>
        </div>
        <div style={{ fontSize: '13px', color: 'var(--text-muted)' }}>
          後端連线: <span style={{ color: 'var(--success)', fontWeight: 'bold' }}>● 已連線 Port 5001</span> (students.json)
        </div>
      </header>

      {/* 📊 頂部數據統計面板 (Glassmorphism 玻璃卡片區塊) */}
      <section className="stats-grid animate-fade-in" style={{ marginTop: '24px' }}>
        {/* 平均分數卡片 */}
        <div className="glass-card stat-card">
          <span className="stat-label">全班平均成績</span>
          <span className="stat-value">{avgScore} <span style={{ fontSize: '16px', fontWeight: 500, color: 'var(--text-muted)' }}>分</span></span>
          <span className="stat-sub">總參與人數: {totalCount} 人</span>
        </div>

        {/* 及格率卡片 (帶動態進度條) */}
        <div className="glass-card stat-card purple">
          <span className="stat-label">及格率 (&ge; 60分)</span>
          <span className="stat-value">{passRate} <span style={{ fontSize: '16px', fontWeight: 500, color: 'var(--text-muted)' }}>%</span></span>
          <div className="progress-bar-container">
            <div className="progress-bar" style={{ width: `${passRate}%` }}></div>
          </div>
          <span className="stat-sub">及格: {passCount} 人 / 不及格: {totalCount - passCount} 人</span>
        </div>

        {/* 最高分卡片 */}
        <div className="glass-card stat-card blue">
          <span className="stat-label">全班最高分 🏆</span>
          <span className="stat-value">
            {highestStudent ? highestStudent.score : '--'} <span style={{ fontSize: '16px', fontWeight: 500, color: 'var(--text-muted)' }}>分</span>
          </span>
          <span className="stat-sub" style={{ color: 'var(--accent-blue)', fontWeight: 600 }}>
            {highestStudent ? `[${highestStudent.id}] ${highestStudent.name}` : '目前無資料'}
          </span>
        </div>

        {/* 第 4 張卡片：動態顯示最低分 / 觀察對象 / 全員優異 */}
        <div className="glass-card stat-card">
          <span className="stat-label">{lowestCardTitle}</span>
          <span className="stat-value">
            {lowestStudent ? lowestStudent.score : '--'} <span style={{ fontSize: '16px', fontWeight: 500, color: 'var(--text-muted)' }}>分</span>
          </span>
          <span className="stat-sub" style={{ color: lowestCardColor, fontWeight: 600 }}>
            {lowestCardSubText}
          </span>
        </div>
      </section>

      {/* 主要內容區 */}
      <main style={{ marginTop: '24px' }}>
        {/* 顯示學生清單與編輯/刪除按鈕 */}
        {students.map(s => (
          <div key={s.id} style={{ padding:'8px', borderBottom: '1px solid #333', display: 'flex', justifyContent: 'space-between', alignItems: 'center' }}>
            <span>
              學號: {s.id} | 姓名: {s.name} | 分數: 
              {/* 如果目前的 s.id 等於正在編輯的 editingId，就渲染輸入框，否則顯示原本的分數數字 */}
              {editingId === s.id ? (
                <input 
                  type="number" 
                  value={editingScore} 
                  onChange={(e) => setEditingScore(e.target.value)} 
                  style={{ width: '60px', marginLeft: '8px' }}
                />
              ) : (
                ` ${s.score}`
              )}
            </span>
            
            <div>
              {/* 如果正在編輯這一行，顯示「儲存」按鈕；否則顯示「修改分數」與「刪除」按鈕 */}
              {editingId === s.id ? (
                <button onClick={() => handleUpdateScore(s.id)} style={{ color: 'green', cursor: 'pointer', marginRight: '8px' }}>
                  儲存
                </button>
              ) : (
                <button 
                  onClick={() => {
                    setEditingId(s.id);
                    setEditingScore(String(s.score));
                  }} 
                  style={{ marginRight: '8px', cursor: 'pointer' }}
                >
                  修改分數
                </button>
              )}

              {/* 關鍵修正：刪除按鈕必須放在迴圈內部！才能知道目前這行是要刪除哪一位學生 s.id */}
              {/* 使用 () => handleDelete(s.id) 綁定點擊事件，只有在「按下」時才會觸發！ */}
              <button onClick={() => handleDelete(s.id)} style={{ color: 'red', cursor: 'pointer', padding: '4px 8px' }}>
                刪除
              </button>
            </div>
          </div>
        ))}

        {/* 新增學生的表單卡片區塊 */}
        <section style={{ marginTop: '32px', padding: '16px', background: 'rgba(255,255,255,0.05)', borderRadius: '8px' }}>
          <h3>➕ 新增學生資料</h3>
          
          {/* <form onSubmit={handleAdd}> 綁定表單送出事件 */}
          <form onSubmit={handleAdd} style={{ display: 'flex', gap: '10px', marginTop: '16px' }}>
            {/* 學號輸入框：value 綁定 inputId，onChange 隨時把打的字存回 inputId */}
            <input 
              type="text" 
              placeholder="學號 (如: S001)" 
              value={inputId}
              onChange={(e) => setInputId(e.target.value)}
              required
            />
            {/* 姓名輸入框 */}
            <input 
              type="text" 
              placeholder="姓名" 
              value={inputName}
              onChange={(e) => setInputName(e.target.value)}
              required
            />
            {/* 分數輸入框 */}
            <input 
              type="number" 
              placeholder="分數 (0-100)" 
              value={inputScore}
              onChange={(e) => setInputScore(e.target.value)}
              required
            />
            {/* 送出按鈕：點擊時會觸發 <form> 的 onSubmit 執行 handleAdd */}
            <button type="submit" style={{ padding: '8px 16px', cursor: 'pointer' }}>
              新增學生
            </button>
          </form>
        </section>
      </main>
    </div>
  );
}

// 匯出 App 組件，讓 main.tsx 可以 import 它並渲染到網頁上
export default App;
