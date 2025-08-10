# 📝 Simple Task Manager in C

A simple console-based Task Manager written in C.

## 🚀 Features

- ✅ Add new tasks (with title, priority, and due date)
- 📋 List all tasks
- ☑️ Mark tasks as completed
- 🗑️ Delete tasks
- 💾 Save tasks to a file
- 📂 *(Planned)* Load tasks from a file

---

## 📦 Structure

### 🔹 `Task` struct:

```c
typedef struct {
    int id;
    char title[50];
    int priority;         // 1 = High, 2 = Medium, 3 = Low
    char due_date[12];    // Format: YYYY-MM-DD
    int status;           // 0 = Pending, 1 = Completed
} Task;
