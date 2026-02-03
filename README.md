# 🛒 CLI Online Store System
### Data Structures & Algorithms – Final Project

## 📌 Project Overview
This project is a **Command Line Interface (CLI) Online Store System** developed as the final project for the **Data Structures and Algorithms** course.

The system manages a single type of product and focuses on the **correct design and implementation of data structures and algorithms**, rather than graphical user interfaces.  
All user interactions are performed through the terminal.

The project is implemented in **C++**, and all searching and sorting algorithms are **manually implemented**, without using built-in STL algorithms, in accordance with course requirements.

---

## 🎯 Project Goals
- Practice and apply core **data structures**
- Implement classic **searching and sorting algorithms manually**
- Design a modular, readable, and maintainable system
- Create a project suitable for academic presentation and defense

---

## ⚙️ Features

### 1️⃣ Product Management
The system supports the following operations:
- Add a new product
- Remove an existing product
- Edit product information
- Display all products

**Data Structure Used:**  
- Linked List  

**Reason:**  
Linked lists allow dynamic insertion and deletion without shifting elements.

---

### 2️⃣ Product Search
Products can be searched using different criteria:

| Search Criterion | Data Structure | Description |
|------------------|---------------|-------------|
Product Name | Binary Search Tree (BST) | Efficient name-based searching |
Category | Hash Table | Fast category-based lookup |
Price Range | Linked List Traversal | Manual range filtering |

🚫 No STL search functions are used.

---

### 3️⃣ Product Sorting
Products can be sorted using classic algorithms:

| Sort Criterion | Algorithm |
|---------------|----------|
Price | Quick Sort |
Rating | Merge Sort |
Sales Count | Heap Sort |

Sorting can be performed in:
- Ascending order
- Descending order

🚫 STL `sort()` is not used.

---

### 4️⃣ Product Recommendation System
When a product is viewed, the system recommends similar products based on:
- Same category
- Similar price range
- Product rating

Each product receives a **similarity score**, and the top recommendations are displayed.

---

### 5️⃣ Logging System
All user interactions are logged, including:
- Adding, editing, and deleting products
- Searching products
- Viewing product details
- Shopping cart operations

Logs are displayed when the program exits.

**Data Structure Used:**  
- Vector

---

## ⭐ Bonus Features

### 🛒 Shopping Cart
The shopping cart allows:
- Adding products to the cart
- Removing products from the cart
- Viewing cart contents
- Calculating total price

**Data Structure Used:**  
- Vector

---

### 👀 Recently Viewed Products
- Stores the last **5 viewed products**
- Displays recently viewed product history

**Data Structure Used:**  
- Deque

---

## 💾 Data Storage
- Product data is stored in a **CSV file**
- Data is loaded at program startup
- All changes are saved automatically

---

## 🧠 Data Structures Summary

| System Component | Data Structure | Reason |
|------------------|---------------|--------|
Product storage | Linked List | Dynamic size |
Search by name | Binary Search Tree | Faster average search |
Search by category | Hash Table | Constant-time access |
Sorting | Custom Algorithms | Manual implementation |
Shopping cart | Vector | Simple and efficient |
Recent views | Deque | Fast front/back operations |
Logging | Vector | Sequential logging |

---

## 🛠 Technologies Used
- **Programming Language:** C++
- **Paradigm:** Object-Oriented Programming (OOP)
- **Interface:** Command Line (CLI)
- **Data Storage:** CSV file

---

## ▶️ How to Compile and Run

```bash
g++ main.cpp -o online_store
./online_store
