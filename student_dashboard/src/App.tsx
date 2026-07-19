import React, { useState, useEffect } from 'react';
import './App.css';

interface Student {
  id: string;
  name: string;
  score: number;
}

function App() {
  // 1. 初始化資料狀態 (優先從 LocalStorage 讀取)
  const [students, setStudents] = useState<Student[]>(() => {
    const saved = localStorage.getItem('students_db');
    return saved ? JSON.parse(saved) : [
      { id: 'S001', name: 'Jasper', score: 95 },
      { id: 'S002', name: 'Bob', score: 80 },
      { id: 'S003', name: 'Alice', score: 92 }
    ];
  });

  // 當資料改變時，自動備份至 LocalStorage (持久化資料庫)
  useEffect(() => {
    localStorage.setItem('students_db', JSON.stringify(students));
  }, [students]);

  // 2. 表單輸入狀態
  const [inputId, setInputId] = useState('');
  const [inputName, setInputName] = useState('');
  const [inputScore, setInputScore] = useState('');
  const [idError, setIdError] = useState('');

  // 3. 搜尋與排序狀態
  const [searchQuery, setSearchQuery] = useState('');
  const [sortBy, setSortBy] = useState<'default' | 'score-desc' | 'score-asc'>('default');

  // 4. 行內修改狀態 (Inline Edit)
  const [editingId, setEditingId] = useState<string | null>(null);
  const [editingScore, setEditingScore] = useState('');

  // 🔎 學號即時重複性檢查 (這就是 Senior 級的防呆細節！)
  useEffect(() => {
    if (inputId.trim() === '') {
      setIdError('');
      return;
    }
    const exists = students.some(s => s.id.toLowerCase() === inputId.trim().toLowerCase());
    if (exists) {
      setIdError('⚠️ 此學號已存在，新增會失敗！');
    } else {
      setIdError('');
    }
  }, [inputId, students]);

  // 5. 事件處理：新增學生
  const handleAdd = (e: React.FormEvent) => {
    e.preventDefault();

    // 基礎驗證
    if (!inputId.trim() || !inputName.trim() || inputScore.trim() === '') {
      alert('請填寫所有欄位！');
      return;
    }

    // 檢查學號是否已存在
    const exists = students.some(s => s.id.toLowerCase() === inputId.trim().toLowerCase());
    if (exists) {
      alert('學號重複，新增失敗！');
      return;
    }

    const scoreNum = parseInt(inputScore);
    if (isNaN(scoreNum) || scoreNum < 0 || scoreNum > 100) {
      alert('分數必須是介於 0 到 100 之間的整數！');
      return;
    }

    const newStudent: Student = {
      id: inputId.trim(),
      name: inputName.trim(),
      score: scoreNum
    };

    setStudents([...students, newStudent]);

    // 清空輸入欄位
    setInputId('');
    setInputName('');
    setInputScore('');
  };

  // 6. 事件處理：更新成績
  const handleSaveEdit = (id: string) => {
    const scoreNum = parseInt(editingScore);
    if (isNaN(scoreNum) || scoreNum < 0 || scoreNum > 100) {
      alert('分數必須是介於 0 到 100 之間的整數！');
      return;
    }

    setStudents(students.map(s => s.id === id ? { ...s, score: scoreNum } : s));
    setEditingId(null);
  };

  // 7. 事件處理：刪除學生
  const handleDelete = (id: string) => {
    if (window.confirm(`確定要刪除學號為 ${id} 的學生嗎？`)) {
      setStudents(students.filter(s => s.id !== id));
    }
  };

  // 8. 🎯 動態運算屬性 (Reactive Derived State)
  // 搜尋過濾
  const filteredStudents = students.filter(s => 
    s.name.toLowerCase().includes(searchQuery.toLowerCase()) ||
    s.id.toLowerCase().includes(searchQuery.toLowerCase())
  );

  // 成績排序
  const sortedStudents = [...filteredStudents].sort((a, b) => {
    if (sortBy === 'score-desc') return b.score - a.score;
    if (sortBy === 'score-asc') return a.score - b.score;
    return 0; // 預設順序
  });

  // 數據統計計算
  const totalCount = students.length;
  
  const avgScore = totalCount > 0 
    ? Math.round((students.reduce((sum, s) => sum + s.score, 0) / totalCount) * 10) / 10
    : 0;

  const passCount = students.filter(s => s.score >= 60).length;
  const passRate = totalCount > 0 ? Math.round((passCount / totalCount) * 100) : 0;

  const highestStudent = totalCount > 0 
    ? [...students].sort((a, b) => b.score - a.score)[0]
    : null;

  const lowestStudent = totalCount > 0 
    ? [...students].sort((a, b) => a.score - b.score)[0]
    : null;

  return (
    <div className="dashboard-container">
      {/* 頂部標題 */}
      <header>
        <div style={{ display: 'flex', alignItems: 'center', gap: '12px' }}>
          <svg width="32" height="32" viewBox="0 0 24 24" fill="none" stroke="currentColor" strokeWidth="2.5" strokeLinecap="round" strokeLinejoin="round" style={{ color: 'var(--primary)' }}>
            <path d="M22 10v6M2 10l10-5 10 5-10 5z"/>
            <path d="M6 12v5c0 2 2 3 6 3s6-1 6-3v-5"/>
          </svg>
          <span style={{ fontSize: '24px', fontWeight: 'bold' }} className="text-gradient">
            Senior GradeManager™
          </span>
        </div>
        <div style={{ fontSize: '13px', color: 'var(--text-muted)' }}>
          系統狀態: <span style={{ color: 'var(--success)', fontWeight: 'bold' }}>● 已連線</span> (LocalStorage)
        </div>
      </header>

      {/* 📊 頂部數據統計面板 */}
      <section className="stats-grid animate-fade-in" style={{ marginTop: '24px' }}>
        {/* 平均分數 */}
        <div className="glass-card stat-card">
          <span className="stat-label">全班平均成績</span>
          <span className="stat-value">{avgScore} <span style={{ fontSize: '16px', fontWeight: 500, color: 'var(--text-muted)' }}>分</span></span>
          <span className="stat-sub">總參與統計學生人數: {totalCount} 人</span>
        </div>

        {/* 及格率 */}
        <div className="glass-card stat-card purple">
          <span className="stat-label">及格率 ( &gt;= 60分 )</span>
          <span className="stat-value">{passRate} <span style={{ fontSize: '16px', fontWeight: 500, color: 'var(--text-muted)' }}>%</span></span>
          <div className="progress-bar-container">
            <div className="progress-bar" style={{ width: `${passRate}%` }}></div>
          </div>
          <span className="stat-sub">及格人數: {passCount} 人 / 不及格: {totalCount - passCount} 人</span>
        </div>

        {/* 最高分 */}
        <div className="glass-card stat-card blue">
          <div style={{ display: 'flex', justifyContent: 'space-between', alignItems: 'center' }}>
            <span className="stat-label">全班第一名 🏆</span>
          </div>
          <span className="stat-value">
            {highestStudent ? highestStudent.score : '--'} 
            <span style={{ fontSize: '16px', fontWeight: 500, color: 'var(--text-muted)' }}> 分</span>
          </span>
          <span className="stat-sub" style={{ color: 'var(--accent-blue)', fontWeight: 600 }}>
            {highestStudent ? `[${highestStudent.id}] ${highestStudent.name}` : '目前無資料'}
          </span>
        </div>

        {/* 最低分 */}
        <div className="glass-card stat-card">
          <span className="stat-label">需要加強 (最低分) ⚠️</span>
          <span className="stat-value">
            {lowestStudent ? lowestStudent.score : '--'} 
            <span style={{ fontSize: '16px', fontWeight: 500, color: 'var(--text-muted)' }}> 分</span>
          </span>
          <span className="stat-sub" style={{ color: 'var(--danger)' }}>
            {lowestStudent ? `[${lowestStudent.id}] ${lowestStudent.name}` : '目前無資料'}
          </span>
        </div>
      </section>

      {/* 核心內容二欄排版 */}
      <main className="main-grid animate-fade-in">
        {/* 左側：新增學生面版 */}
        <section className="glass-card form-panel">
          <h2 className="section-title">
            <svg width="20" height="20" viewBox="0 0 24 24" fill="none" stroke="currentColor" strokeWidth="2" strokeLinecap="round" strokeLinejoin="round">
              <path d="M16 21v-2a4 4 0 0 0-4-4H5a4 4 0 0 0-4 4v2"/>
              <circle cx="8.5" cy="7" r="4"/>
              <line x1="20" y1="8" x2="20" y2="14"/>
              <line x1="23" y1="11" x2="17" y2="11"/>
            </svg>
            新增學生資料
          </h2>

          <form onSubmit={handleAdd}>
            <div className="form-group">
              <label className="form-label">學生學號 (ID)</label>
              <input 
                type="text" 
                placeholder="例如: S004" 
                value={inputId}
                onChange={(e) => setInputId(e.target.value)}
                required
              />
              {idError && <span className="error-msg">{idError}</span>}
            </div>

            <div className="form-group">
              <label className="form-label">學生姓名 (Name)</label>
              <input 
                type="text" 
                placeholder="例如: Jasper" 
                value={inputName}
                onChange={(e) => setInputName(e.target.value)}
                required
              />
            </div>

            <div className="form-group">
              <label className="form-label">學生成績 (Score)</label>
              <input 
                type="number" 
                placeholder="0 - 100" 
                min="0"
                max="100"
                value={inputScore}
                onChange={(e) => setInputScore(e.target.value)}
                required
              />
            </div>

            <button type="submit" className="btn-primary" disabled={!!idError}>
              <svg width="18" height="18" viewBox="0 0 24 24" fill="none" stroke="currentColor" strokeWidth="2" strokeLinecap="round" strokeLinejoin="round">
                <line x1="12" y1="5" x2="12" y2="19"/>
                <line x1="5" y1="12" x2="19" y2="12"/>
              </svg>
              新增至資料庫
            </button>
          </form>
        </section>

        {/* 右側：學員列表 */}
        <section className="glass-card list-panel">
          <div className="list-header">
            {/* 搜尋欄 */}
            <div className="search-input-wrapper">
              <svg className="search-icon" width="18" height="18" viewBox="0 0 24 24" fill="none" stroke="currentColor" strokeWidth="2" strokeLinecap="round" strokeLinejoin="round">
                <circle cx="11" cy="11" r="8"/>
                <line x1="21" y1="21" x2="16.65" y2="16.65"/>
              </svg>
              <input 
                type="text" 
                className="search-input" 
                placeholder="搜尋學號或姓名..." 
                value={searchQuery}
                onChange={(e) => setSearchQuery(e.target.value)}
              />
            </div>

            {/* 排序控制 */}
            <div className="sort-actions">
              <button 
                className={`btn-outline ${sortBy === 'default' ? 'active' : ''}`}
                onClick={() => setSortBy('default')}
              >
                預設
              </button>
              <button 
                className={`btn-outline ${sortBy === 'score-desc' ? 'active' : ''}`}
                onClick={() => setSortBy('score-desc')}
              >
                成績由高到低 ↓
              </button>
              <button 
                className={`btn-outline ${sortBy === 'score-asc' ? 'active' : ''}`}
                onClick={() => setSortBy('score-asc')}
              >
                成績由低到高 ↑
              </button>
            </div>
          </div>

          {/* 表格區 */}
          <div className="table-wrapper">
            {sortedStudents.length === 0 ? (
              <div className="empty-state">
                <svg width="48" height="48" viewBox="0 0 24 24" fill="none" stroke="currentColor" strokeWidth="1.5" strokeLinecap="round" strokeLinejoin="round">
                  <circle cx="12" cy="12" r="10"/>
                  <line x1="8" y1="12" x2="16" y2="12"/>
                </svg>
                <p>找不到符合篩選條件的學生資料！</p>
              </div>
            ) : (
              <table>
                <thead>
                  <tr>
                    <th>學號 (ID)</th>
                    <th>姓名 (Name)</th>
                    <th>成績 (Score)</th>
                    <th>狀態 (Status)</th>
                    <th style={{ textAlign: 'right' }}>操作 (Actions)</th>
                  </tr>
                </thead>
                <tbody>
                  {sortedStudents.map((s) => (
                    <tr key={s.id}>
                      <td style={{ fontWeight: 'bold' }}>{s.id}</td>
                      <td>{s.name}</td>
                      <td>
                        {editingId === s.id ? (
                          <input
                            type="number"
                            style={{ width: '70px', padding: '6px 8px', fontSize: '13px' }}
                            value={editingScore}
                            min="0"
                            max="100"
                            onChange={(e) => setEditingScore(e.target.value)}
                            autoFocus
                          />
                        ) : (
                          <span style={{ fontSize: '15px', fontWeight: 600 }}>{s.score} 分</span>
                        )}
                      </td>
                      <td>
                        {s.score >= 60 ? (
                          <span className="score-badge pass">及格</span>
                        ) : (
                          <span className="score-badge fail">不及格</span>
                        )}
                      </td>
                      <td style={{ textAlign: 'right' }}>
                        <div className="action-buttons" style={{ justifyContent: 'flex-end' }}>
                          {editingId === s.id ? (
                            <>
                              {/* 儲存按鈕 */}
                              <button 
                                className="btn-icon edit" 
                                title="儲存修改"
                                onClick={() => handleSaveEdit(s.id)}
                              >
                                <svg width="18" height="18" viewBox="0 0 24 24" fill="none" stroke="currentColor" strokeWidth="2" strokeLinecap="round" strokeLinejoin="round">
                                  <polyline points="20 6 9 17 4 12"/>
                                </svg>
                              </button>
                              {/* 取消按鈕 */}
                              <button 
                                className="btn-icon delete" 
                                title="取消修改"
                                onClick={() => setEditingId(null)}
                              >
                                <svg width="18" height="18" viewBox="0 0 24 24" fill="none" stroke="currentColor" strokeWidth="2" strokeLinecap="round" strokeLinejoin="round">
                                  <line x1="18" y1="6" x2="6" y2="18"/>
                                  <line x1="6" y1="6" x2="18" y2="18"/>
                                </svg>
                              </button>
                            </>
                          ) : (
                            <>
                              {/* 編輯按鈕 */}
                              <button 
                                className="btn-icon edit" 
                                title="編輯成績"
                                onClick={() => {
                                  setEditingId(s.id);
                                  setEditingScore(String(s.score));
                                }}
                              >
                                <svg width="18" height="18" viewBox="0 0 24 24" fill="none" stroke="currentColor" strokeWidth="2" strokeLinecap="round" strokeLinejoin="round">
                                  <path d="M11 4H4a2 2 0 0 0-2 2v14a2 2 0 0 0 2 2h14a2 2 0 0 0 2-2v-7"/>
                                  <path d="M18.5 2.5a2.121 2.121 0 1 1 3 3L12 15l-4 1 1-4Z"/>
                                </svg>
                              </button>
                              {/* 刪除按鈕 */}
                              <button 
                                className="btn-icon delete" 
                                title="刪除學生"
                                onClick={() => handleDelete(s.id)}
                              >
                                <svg width="18" height="18" viewBox="0 0 24 24" fill="none" stroke="currentColor" strokeWidth="2" strokeLinecap="round" strokeLinejoin="round">
                                  <polyline points="3 6 5 6 21 6"/>
                                  <path d="M19 6v14a2 2 0 0 1-2 2H7a2 2 0 0 1-2-2V6m3 0V4a2 2 0 0 1 2-2h4a2 2 0 0 1 2 2v2"/>
                                  <line x1="10" y1="11" x2="10" y2="17"/>
                                  <line x1="14" y1="11" x2="14" y2="17"/>
                                </svg>
                              </button>
                            </>
                          )}
                        </div>
                      </td>
                    </tr>
                  ))}
                </tbody>
              </table>
            )}
          </div>
        </section>
      </main>
    </div>
  );
}

export default App;
