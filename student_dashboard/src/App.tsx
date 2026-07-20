import React, { useState, useEffect } from 'react';
import './App.css';

//定義傳入參數（Props）的型別介面 (國際大廠嚴格要求)
interface Student {
  id: string;
  name: string;
  score: number;
}

function App() {
  // TODO 1: 宣告 students 狀態，預設為空陣列
  // 提示：const [students, setStudents] = useState<Student[]>([]);
  const [students,setStudent] = useState<Student[]>([]);
  const [inputId,setInputId] = useState('');
  const [inputName,setInputName] = useState('');
  const [inputScore,setInputScore] = useState('');




  // TODO 2: 用 useEffect 在網頁加載時，向後端 API (http://localhost:5001/api/students) 拿資料 (fetch)
  // 提示步驟：
  // useEffect(() => {
  //   fetch('http://localhost:5001/api/students')
  //     .then(res => res.json()) // 翻譯成 JSON 物件
  //     .then(data => setStudents(data)); // 存入 students 狀態
  // }, []); // 空陣列 [] 代表只在網頁初次加載時執行一次
  // 定義一個可以重複呼叫的抓取函式
  const fetchStudents = () => {
    fetch('http://localhost:5001/api/students')
      .then(res => res.json())
      .then(data => setStudent(data));
  };

  // TODO 2: 網頁加載時自動抓取一次資料
  useEffect(() => {
    fetchStudents();
  }, []);

  // 關鍵修正 1：函式定義必須放在 App() 內部、return(...) 的「外面」！
  const handleAdd = (e: React.FormEvent) => { // 關鍵修正 2：FormEvent 拼字修正
    e.preventDefault(); // 阻止網頁刷新
    
    fetch('http://localhost:5001/api/students', {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify({ id: inputId, name: inputName, score: Number(inputScore) })
    })
    .then(res => res.json())
    .then(data => {
      alert(data.message); // 顯示後端回傳的訊息
      
      // 清空輸入框
      setInputId('');
      setInputName('');
      setInputScore('');
      
      // 重新向後端抓取最新資料！
      fetchStudents();
    });
  };

  return (
    <div className="dashboard-container">
      <header>
        <span style={{ fontSize: '24px', fontWeight: 'bold' }}>
          學生成績管理系統 (全端版)
        </span>
      </header>

      <main style={{ marginTop: '24px' }}>
        <h2>學生人數: {students.length} 人</h2>

        {/* TODO 5: 實作「刪除學生」功能 (DELETE API) */}
        {/* 提示步驟：
            1. 寫一個 handleDelete 函式接收要刪除的 id：
               const handleDelete = (id: string) => {
                 fetch(`http://localhost:5001/api/students/${id}`, {
                   method: 'DELETE'
                 })
                 .then(res => res.json())
                 .then(data => {
                   alert(data.message);
                   fetchStudents(); // 重新向後端抓取最新資料！
                 });
               };
            
            2. 在下面學生的右邊加上一個 <button onClick={() => handleDelete(s.id)}>刪除</button> 按鈕！
        */}
        {students.map(s => (
          <div key={s.id} style={{ padding:'8px', borderBottom: '1px solid #333', display: 'flex', justifyContent: 'space-between', alignItems: 'center' }}>
            <span>學號: {s.id} | 姓名: {s.name} | 分數: {s.score}</span>
            {/* [請在此處加入刪除按鈕] */}
          </div>
        ))}

        {/* TODO 4: 實作「新增學生」的表單 */}
        <section style={{ marginTop: '32px', padding: '16px', background: 'rgba(255,255,255,0.05)', borderRadius: '8px' }}>
          <h3>➕ 新增學生資料</h3>
          
          {/* 解答你的疑問：表單要怎麼寫？ */}
          {/* 使用 <form onSubmit={handleAdd}> 監聽送出事件 */}
          <form onSubmit={handleAdd} style={{ display: 'flex', gap: '30px', marginTop: '16px' }}>
            <input 
              type="text" 
              placeholder="學號 (如: S001)" 
              value={inputId}
              onChange={(e) => setInputId(e.target.value)} // 隨時更新 state
              required
            />
            <input 
              type="text" 
              placeholder="姓名" 
              value={inputName}
              onChange={(e) => setInputName(e.target.value)}
              required
            />
            <input 
              type="number" 
              placeholder="分數 (0-100)" 
              value={inputScore}
              onChange={(e) => setInputScore(e.target.value)}
              required
            />
            <button type="submit" style={{ padding: '8px 16px', cursor: 'pointer' }}>
              新增學生
            </button>
          </form>
        </section>
      </main>
    </div>
  );
}

export default App;
