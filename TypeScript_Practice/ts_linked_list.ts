// ========================================================
// 🎯 TypeScript 實戰練習：自製單向鏈結串列 (Singly Linked List)
// ========================================================
//
// 💡 TS 版的指標觀念轉變：
// 1. C++ 中指向下個節點用指標 `ListNode* next;`
//    TS 中沒有指標，我們直接宣告 `next: ListNode | null;`
//    這代表 `next` 要麼是指向「另一個 ListNode 物件」，要麼是「空值 null」。
// 2. C++ 中存取內部變數用 `->` (如 `curr->val`)
//    TS 中一律統一用點 `.` 即可 (如 `curr.val`)。

class ListNode {
    public val: number;
    public next: ListNode | null;

    constructor(x: number) {
        this.val = x;
        this.next = null; // 預設指向 null
    }
}

class LinkedList {
    private head: ListNode | null = null; // 火車頭，一開始是空的 (null)

    // TODO 1: 在鏈結串列「尾端」新增一個節點 (Insert)
    // 提示步驟：
    // 1. 建立新節點：`const newNode = new ListNode(val);`。
    // 2. 判斷火車是不是空的：如果 `this.head === null`，代表新車廂就是火車頭，直接讓 `this.head = newNode;`。
    // 3. 如果不為空，宣告移動變數 `let temp = this.head;`，用 while 迴圈走到最末端節點 (當 `temp.next === null` 時停下)。
    // 4. 將最末端節點的 next 指向新節點：`temp.next = newNode;`。
    public insert(val: number): void {
        const newNode = new ListNode(val);
        
        // 關鍵修正 1：比較要用三等號 `===`，單等號 `=` 是賦值！
        if (this.head === null) {
            this.head = newNode;
        } else {
            let temp = this.head;
            // 關鍵修正 2：只要「下一站不是 null」，就代表後面還有車廂，我們就繼續前進！
            while (temp.next !== null) {
                temp = temp.next; // 走向下一站
            }
            // 走到最後一節車廂了，把它接上新車廂
            temp.next = newNode;
        }
    } // 關鍵修正 3：補上 insert 函式的結束大括號 `}`！

    // TODO 2: 在鏈結串列中尋找特定數值 (Search)
    public search(target: number): boolean {
        let curr = this.head;
        while(curr !== null){
            if(curr.val === target){
                return true; 
            }
            curr = curr.next; // 簡化：可以直接寫在 if-else 外面
        }
        return false;
    }

    // TODO 3: 印出整條鏈結串列 (Print)
    public print(): void {
        let curr = this.head;
        let result = "";
        while (curr !== null) {
            // 將數值與箭頭串接成字串
            result += curr.val + " -> ";
            
            // 解答你的疑問 1：移動到下一站的寫法跟搜尋一樣，就是指向它的 `next`！
            curr = curr.next; 
        }
        // 解答你的疑問 2：迴圈結束後，我們直接把最後的 "null" 串接在字串的最尾端即可！
        result += "null"; 
        console.log(result);
    }

    // 💡 思考題：在 C++ 中我們必須寫 delete 迴圈來釋放記憶體。在 TypeScript 中要怎麼清空鏈結串列？
    public clear(): void {
        this.head = null;
        console.log("鏈結串列已清空 (由垃圾回收器自動釋放記憶體)！");
    }
}

// ========================================================
// 測試主程式
// ========================================================
console.log("=== 測試 TypeScript 版 Linked List ===");
const list = new LinkedList();

list.insert(10);
list.insert(20);
list.insert(30);

// TODO 4: 呼叫 print() 印出串列 (預期印出: 10 -> 20 -> 30 -> null)
list.print();

// TODO 5: 測試搜尋功能
// 解答你的疑問 3：我們可以直接把搜尋的結果 (true/false) 當作參數傳給 console.log 列印出來！
console.log("搜尋 20 是否存在: ", list.search(20)); // 應該印出 true
console.log("搜尋 99 是否存在: ", list.search(99)); // 應該印出 false


console.log("\n=== 測試清空記憶體 ===");
list.clear();
list.print(); // 應該只會印出 null
