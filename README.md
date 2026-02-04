# 🛒 CLI Online Store System
### Data Structures & Algorithms – Final Project

---

## 📌 Project Overview

This project is a **Command Line Interface (CLI) Online Store Management System** developed as the final project for the **Data Structures and Algorithms** course.

The system manages a single type of product and focuses on the **correct design and manual implementation of data structures and algorithms**, rather than graphical user interfaces.  
All user interactions are performed entirely through the terminal.

The project is implemented in **C++**, and all searching and sorting operations are **implemented manually**, without using built-in STL algorithms, in full compliance with the course requirements.

---

## 🎯 Project Goals

- Practice and apply fundamental **data structures**
- Implement classic **searching and sorting algorithms manually**
- Design a modular, readable, and maintainable system
- Build a project suitable for **academic evaluation and oral defense**

---

## ⚙️ System Features

### 1️⃣ Product Management

The system provides full product management functionality:

- Add a new product
- Remove an existing product
- Edit product information
- Display all products

Each product contains the following attributes:
- ID
- Name
- Price
- Category
- Rating
- Sold Count
- Stock
- Brand
- Description

**Data Structure Used:**  
- Singly Linked List  

**Reason:**  
Linked lists allow efficient dynamic insertion and deletion of products without shifting elements in memory.

---

### 2️⃣ Product Search

The system supports searching products using multiple criteria, each implemented with an appropriate data structure:

| Search Criterion | Data Structure | Description |
|------------------|---------------|-------------|
| Product Name | Binary Search Tree (BST) | Efficient name-based searching |
| Category | Hash Table | Fast category-based lookup |
| Price Range | Linked List Traversal | Manual range filtering |

🚫 No STL search functions are used.

---

### 3️⃣ Product Sorting

Products can be sorted based on different attributes using classic sorting algorithms:

| Sort Criterion | Algorithm Used |
|---------------|---------------|
| Price | Quick Sort |
| Rating | Merge Sort |
| Sales Count | Selection Sort |

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
- Sales performance

Each product is assigned a **similarity score**, and the top-scoring products are displayed as recommendations.

---

### 5️⃣ Logging System

All major user interactions are recorded in a logging system, including:
- Adding products
- Editing products
- Deleting products
- Searching products
- Viewing product details
- Shopping cart operations

Logs are displayed when the program exits and are also saved to a file.

**Log File:**




**Data Structure Used:**  
- Vector

---

## ⭐ Bonus Features (Extra Credit)

### 🛒 Shopping Cart

The shopping cart supports the following operations:
- Add a product to the cart
- Remove a product from the cart
- View cart contents
- Calculate total price of items

**Data Structure Used:**  
- Vector  

---

### 👀 Recently Viewed Products

- Stores the last **5 products** viewed by the user
- Automatically removes duplicates
- Displays recent viewing history

**Data Structure Used:**  
- Deque  

---

## 💾 Data Storage

- Product data is stored persistently in a **CSV file**
- Data is loaded automatically at program startup
- All modifications are saved during program execution

**File Used:**





---

## 🧠 Data Structures Summary

| System Component | Data Structure | Reason |
|------------------|---------------|--------|
| Product storage | Linked List | Dynamic size and flexibility |
| Search by name | Binary Search Tree (BST) | Faster average search |
| Search by category | Hash Table | Near constant-time access |
| Sorting | Custom algorithms | Manual implementation requirement |
| Shopping cart | Vector | Simple and efficient |
| Recent views | Deque | Fast front/back operations |
| Logging | Vector | Sequential logging |

---

## 🛠 Technologies Used

- **Programming Language:** C++
- **Paradigm:** Object-Oriented Programming (OOP)
- **Interface:** Command Line Interface (CLI)
- **Data Storage Format:** CSV

---

## ▶️ How to Compile and Run

### Compilation
```bash
g++ -std=gnu++17 main.cpp -o online_store
./online_store

