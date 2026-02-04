# StoreX – Command-Line Online Store Management System

## 📌 Project Overview

**StoreX** is a command-line based online store management system developed in **C++** as the final project for the **Data Structures and Algorithms** course.  
The primary objective of this project is to design and implement a fully functional store system while **manually applying fundamental data structures and algorithms**, without relying on built-in STL search or sorting utilities.

All user interactions are performed through a **CLI (Command Line Interface)**, with the main focus on correctness, efficiency, and clarity of data structure usage rather than graphical appearance.

---

## 🎯 Project Objectives

- Apply core **data structures** in a real-world scenario
- Implement **manual searching and sorting algorithms**
- Design a modular and maintainable system architecture
- Practice file handling and persistent data storage
- Simulate features of an online shopping system

---

## 🧩 Core Features

### 1. Product Management
- Add new products
- Remove existing products
- Edit product information
- Display all products

Each product includes the following attributes:
- ID
- Name
- Price
- Category
- Rating
- Sold Count
- Stock
- Brand
- Description

Products are primarily stored using a **Singly Linked List**.

---

### 2. Search System
The system supports multiple search methods, each implemented using an appropriate data structure:

| Search Type | Data Structure Used |
|------------|--------------------|
| Search by name | Binary Search Tree (BST) |
| Search by category | Hash Table |
| Search by price range | Linear search |

All search algorithms are implemented manually without STL shortcuts.

---

### 3. Product Sorting
Products can be sorted in **ascending or descending order** using different criteria:

| Sorting Criterion | Algorithm Used |
|------------------|---------------|
| Price | Quick Sort |
| Rating | Merge Sort |
| Sold Count | Selection Sort |

Sorting is performed on temporary vectors derived from the linked list to preserve data integrity.

---

### 4. Product Recommendation System
A recommendation engine suggests similar products based on:
- Category similarity
- Price range proximity
- Product rating
- Sales performance

Each product receives a **similarity score**, and recommendations are sorted manually using Bubble Sort.

---

### 5. System Logging
All major system interactions are logged, including:
- Adding products
- Editing products
- Deleting products
- Searching
- Viewing product details
- Shopping cart actions

Logs are displayed at program termination and saved to:

---

## ⭐ Bonus Features (Extra Points)

### 🛒 Shopping Cart
- Add products to cart
- Remove products from cart
- View cart contents
- Calculate total price

Implemented using a dynamic `vector` structure.

---

### 🕒 Recently Viewed Products
- Tracks the last 5 viewed products
- Prevents duplicate entries
- Automatically removes the oldest viewed product

Implemented using a `deque` data structure.

---

## 🗃️ Data Persistence

- Product data is stored in a **CSV file**
- File is automatically loaded at program startup
- All changes are saved on exit

**Supported format:**



---

## 🧠 Data Structures Used

- Singly Linked List
- Binary Search Tree (BST)
- Hash Table (with chaining)
- Vector
- Deque
- Pair (for scoring and recommendations)

---

## ⚙️ Algorithms Implemented

- Linear Search
- Hash-based Search
- Binary Search Tree traversal
- Quick Sort
- Merge Sort
- Selection Sort
- Bubble Sort

> ⚠️ No STL search or sort algorithms were used in compliance with course rules.

---

## 🧪 Input Validation

- Numeric validation for IDs, prices, ratings, stock, and sold count
- Unique product ID enforcement
- Range checks for price and rating
- Safe input handling to prevent invalid entries

---

## ▶️ How to Compile and Run

### Compilation
```bash
g++ -std=gnu++17 main.cpp -o StoreX
