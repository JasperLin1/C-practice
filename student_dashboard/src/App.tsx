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
      alert(data.message); // 顯示「刪除成功！」
      fetchStudents();     // 重新向後端抓取最新資料，畫面上的該學生就會 disappear！
    });
  };

  // App 組件的渲染 HTML 區塊
  return (
    <div className="dashboard-container">
      {/* 頁首標題 */}
      <header>
        <span style={{ fontSize: '24px', fontWeight: 'bold' }}>
          學生成績管理系統 (全端版)
        </span>
      </header>

      {/* 主要內容區 */}
      <main style={{ marginTop: '24px' }}>
        {/* 動態顯示目前陣列的長度 (人數) */}
        <h2>學生人數: {students.length} 人</h2>

        {/* 使用 .map() 陣列迴圈，將 `students` 中的每位學生轉化成一個 <div> 畫在網頁上 */}
        {students.map(s => (
          // key={s.id} 是 React 規定：迴圈畫出來的元素必須給予唯一的 key，效能才會好
          <div key={s.id} style={{ padding:'8px', borderBottom: '1px solid #333', display: 'flex', justifyContent: 'space-between', alignItems: 'center' }}>
            {/* 顯示學號、姓名與分數 */}
            <span>學號: {s.id} | 姓名: {s.name} | 分數: {s.score}</span>
            
            {/* 關鍵修正：刪除按鈕必須放在迴圈內部！才能知道目前這行是要刪除哪一位學生 s.id */}
            {/* 使用 () => handleDelete(s.id) 綁定點擊事件，只有在「按下」時才會觸發！ */}
            <button onClick={() => handleDelete(s.id)} style={{ color: 'red', cursor: 'pointer', padding: '4px 8px' }}>
              刪除
            </button>
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
