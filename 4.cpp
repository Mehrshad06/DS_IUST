// #include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <deque>
#include <string>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <limits>
#include <random>

using namespace std;

class ColorManager {
private:
    mt19937 rng;
    vector<string> textColors = {
        "\033[30m", "\033[31m", "\033[32m", "\033[33m",
        "\033[34m", "\033[35m", "\033[36m", "\033[37m",
        "\033[90m", "\033[91m", "\033[92m", "\033[93m",
        "\033[94m", "\033[95m", "\033[96m", "\033[97m"
    };
    
    vector<string> styles = {
        "\033[1m", "\033[3m", "\033[4m"
    };
    
public:
    ColorManager() : rng(random_device{}()) {}
    
    string getRandomColor() {
        uniform_int_distribution<int> dist(0, textColors.size() - 1);
        return textColors[dist(rng)];
    }
    
    string getRandomStyle() {
        uniform_int_distribution<int> dist(0, styles.size() - 1);
        return styles[dist(rng)];
    }
    
    string getRandomStyledText() {
        uniform_int_distribution<int> colorDist(0, textColors.size() - 1);
        uniform_int_distribution<int> styleDist(0, styles.size() - 1);
        return styles[styleDist(rng)] + textColors[colorDist(rng)];
    }
    
    string reset() {
        return "\033[0m";
    }
    
    string getRandomColoredText(const string& text) {
        return getRandomStyledText() + text + reset();
    }
    
    void printRandom(const string& text) {
        cout << getRandomStyledText() << text << reset();
    }
    
    void printLineRandom(const string& text) {
        uniform_int_distribution<int> dist(0, 3);
        int style = dist(rng);
        
        string colorCode;
        switch(style) {
            case 0: colorCode = getRandomColor(); break;
            case 1: colorCode = getRandomStyle() + getRandomColor(); break;
            case 2: colorCode = "\033[1m" + getRandomColor(); break;
            case 3: colorCode = getRandomStyle(); break;
        }
        cout << colorCode << text << reset() << endl;
    }
};

ColorManager colorMgr;

struct Product {
    int id;
    string name;
    double price;
    string category;
    double rating;
    int soldCount;
    int stock;
    string brand;
    string description;
    
    void display() const {
        colorMgr.printRandom("ID: ");
        cout << id;
        colorMgr.printRandom(" | Name: ");
        cout << name;
        colorMgr.printRandom(" | Price: $");
        cout << price;
        colorMgr.printRandom(" | Category: ");
        cout << category;
        colorMgr.printRandom(" | Rating: ");
        cout << rating;
        colorMgr.printRandom(" | Sold: ");
        cout << soldCount;
        colorMgr.printRandom(" | Stock: ");
        cout << stock;
        colorMgr.printRandom(" | Brand: ");
        cout << brand << endl;
    }
    
    void displayDetailed() const {
        colorMgr.printLineRandom("\n=== PRODUCT DETAILS ===");
        colorMgr.printRandom("ID: ");
        cout << id << endl;
        colorMgr.printRandom("Name: ");
        cout << name << endl;
        colorMgr.printRandom("Price: $");
        cout << price << endl;
        colorMgr.printRandom("Category: ");
        cout << category << endl;
        colorMgr.printRandom("Rating: ");
        cout << rating << "/5" << endl;
        colorMgr.printRandom("Sold Count: ");
        cout << soldCount << endl;
        colorMgr.printRandom("Stock: ");
        cout << stock << endl;
        colorMgr.printRandom("Brand: ");
        cout << brand << endl;
        colorMgr.printRandom("Description: ");
        cout << description << endl;
        colorMgr.printLineRandom("=========================");
    }
};

class Node {
public:
    Product data;
    Node* next;
    Node(const Product& p) : data(p), next(nullptr) {}
};

class LinkedList {
private:
    Node* head;
    int size;
    
public:
    LinkedList() : head(nullptr), size(0) {}
    
    ~LinkedList() {
        Node* current = head;
        while (current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }
    
    Node* getHead() const { return head; }
    int getSize() const { return size; }
    
    void add(const Product& p) {
        Node* newNode = new Node(p);
        if (!head) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
        size++;
    }
    
    bool removeById(int id) {
        if (!head) return false;
        
        if (head->data.id == id) {
            Node* temp = head;
            head = head->next;
            delete temp;
            size--;
            return true;
        }
        
        Node* current = head;
        while (current->next && current->next->data.id != id) {
            current = current->next;
        }
        
        if (current->next) {
            Node* temp = current->next;
            current->next = current->next->next;
            delete temp;
            size--;
            return true;
        }
        
        return false;
    }
    
    Product* findById(int id) {
        Node* current = head;
        while (current) {
            if (current->data.id == id) {
                return &(current->data);
            }
            current = current->next;
        }
        return nullptr;
    }
    
    void displayAll() const {
        if (size == 0) {
            colorMgr.printLineRandom("No products available!");
            return;
        }
        
        colorMgr.printLineRandom("\n=== All Products (" + to_string(size) + " products) ===");
        Node* current = head;
        while (current) {
            current->data.display();
            current = current->next;
        }
    }
    
    vector<Product> toVector() const {
        vector<Product> result;
        Node* current = head;
        while (current) {
            result.push_back(current->data);
            current = current->next;
        }
        return result;
    }
};

class CSVManager {
private:
    string filename;
    
public:
    CSVManager(const string& fname) : filename(fname) {}
    
    void loadProducts(LinkedList& list) {
        ifstream file(filename);
        if (!file.is_open()) {
            colorMgr.printLineRandom("Creating new CSV file...");
            return;
        }
        
        string line;
        getline(file, line); 
        
        while (getline(file, line)) {
            stringstream ss(line);
            vector<string> fields;
            string field;
            
            while (getline(ss, field, ',')) {
                fields.push_back(field);
            }
            
            if (fields.size() >= 9) {
                Product p;
                p.id = stoi(fields[0]);
                p.name = fields[1];
                p.price = stod(fields[2]);
                p.category = fields[3];
                p.rating = stod(fields[4]);
                p.soldCount = stoi(fields[5]);
                p.stock = stoi(fields[6]);
                p.brand = fields[7];
                p.description = fields[8];
                
                list.add(p);
            }
        }
        file.close();
    }
    
    void saveProducts(LinkedList& list) {
        ofstream file(filename);
        file << "id,name,price,category,rating,soldCount,stock,brand,description\n";
        
        Node* current = list.getHead();
        while (current) {
            Product& p = current->data;
            file << p.id << ","
                 << p.name << ","
                 << p.price << ","
                 << p.category << ","
                 << p.rating << ","
                 << p.soldCount << ","
                 << p.stock << ","
                 << p.brand << ","
                 << p.description;
            
            if (current->next) file << "\n";
            current = current->next;
        }
        file.close();
    }
};

class Logger {
private:
    vector<string> logs;
    
public:
    void addLog(const string& action) {
        time_t now = time(0);
        char* dt = ctime(&now);
        string timestamp = dt;
        timestamp.pop_back(); 
        
        string logEntry = timestamp + " - " + action;
        logs.push_back(logEntry);
    }
    
    void displayLogs() const {
        colorMgr.printLineRandom("\n=== SYSTEM LOGS ===");
        if (logs.empty()) {
            colorMgr.printLineRandom("No logs available.");
            return;
        }
        
        for (const string& log : logs) {
            colorMgr.printLineRandom(log);
        }
    }
    
    void saveToFile() const {
        ofstream file("system_logs.txt");
        for (const string& log : logs) {
            file << log << endl;
        }
        file.close();
        colorMgr.printLineRandom("Logs saved to 'system_logs.txt'");
    }
};

class BSTNode {
public:
    Product data;
    BSTNode* left;
    BSTNode* right;
    
    BSTNode(const Product& p) : data(p), left(nullptr), right(nullptr) {}
};

class NameBST {
private:
    BSTNode* root;
    
    void deleteTree(BSTNode* node) {
        if (!node) return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
    
    BSTNode* insert(BSTNode* node, const Product& p) {
        if (!node) return new BSTNode(p);
        if (p.name < node->data.name) {
            node->left = insert(node->left, p);
        } else {
            node->right = insert(node->right, p);
        }
        return node;
    }
    
    void searchByName(BSTNode* node, const string& name, vector<Product>& results) {
        if (!node) return;
        string productName = node->data.name;
        bool found = false;
        if (productName.length() >= name.length()) {
            for (size_t i = 0; i <= productName.length() - name.length(); i++) {
                bool match = true;
                for (size_t j = 0; j < name.length(); j++) {
                    if (tolower(productName[i + j]) != tolower(name[j])) {
                        match = false;
                        break;
                    }
                }
                if (match) {
                    found = true;
                    break;
                }
            }
        }
        
        if (found) {
            results.push_back(node->data);
        }
        if (name < node->data.name) {
            searchByName(node->left, name, results);
        } else {
            searchByName(node->right, name, results);
        }
    }
    
public:
    NameBST() : root(nullptr) {}
    
    ~NameBST() {
        deleteTree(root);
    }
    
    void buildFromList(LinkedList& list) {
        Node* current = list.getHead();
        while (current) {
            root = insert(root, current->data);
            current = current->next;
        }
    }
    
    vector<Product> search(const string& name) {
        vector<Product> results;
        searchByName(root, name, results);
        return results;
    }
};

class CategoryHashTable {
private:
    static const int TABLE_SIZE = 50;
    vector<Product> table[TABLE_SIZE];
    
    int hashFunction(const string& category) {
        int hash = 0;
        for (char c : category) {
            hash = (hash * 31 + c) % TABLE_SIZE;
        }
        return hash % TABLE_SIZE;
    }
    
public:
    void buildFromList(LinkedList& list) {
        Node* current = list.getHead();
        while (current) {
            int index = hashFunction(current->data.category);
            table[index].push_back(current->data);
            current = current->next;
        }
    }
    
    vector<Product> searchByCategory(const string& category) {
        int index = hashFunction(category);
        vector<Product> results;
        
        for (const Product& p : table[index]) {
            if (p.category == category) {
                results.push_back(p);
            }
        }
        return results;
    }
};

vector<Product> searchByPriceRange(LinkedList& list, double minPrice, double maxPrice) {
    vector<Product> results;
    Node* current = list.getHead();
    
    while (current) {
        if (current->data.price >= minPrice && current->data.price <= maxPrice) {
            results.push_back(current->data);
        }
        current = current->next;
    }
    return results;
}

class QuickSorter {
private:
    static int partition(vector<Product>& arr, int low, int high, bool ascending) {
        double pivot = arr[high].price;
        int i = low - 1;
        
        for (int j = low; j < high; j++) {
            bool condition = ascending ? (arr[j].price <= pivot) : (arr[j].price >= pivot);
            if (condition) {
                i++;
                Product temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        Product temp = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = temp;
        return i + 1;
    }
    
    static void quickSort(vector<Product>& arr, int low, int high, bool ascending) {
        if (low < high) {
            int pi = partition(arr, low, high, ascending);
            quickSort(arr, low, pi - 1, ascending);
            quickSort(arr, pi + 1, high, ascending);
        }
    }
    
public:
    static void sortByPrice(vector<Product>& products, bool ascending = true) {
        if (products.empty()) return;
        quickSort(products, 0, products.size() - 1, ascending);
    }
};

class MergeSorter {
private:
    static void merge(vector<Product>& arr, int left, int mid, int right, bool ascending) {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        Product* L = new Product[n1];
        Product* R = new Product[n2];
        
        for (int i = 0; i < n1; i++)
            L[i] = arr[left + i];
        for (int j = 0; j < n2; j++)
            R[j] = arr[mid + 1 + j];
        
        int i = 0, j = 0, k = left;
        
        while (i < n1 && j < n2) {
            bool condition = ascending ? (L[i].rating <= R[j].rating) : (L[i].rating >= R[j].rating);
            if (condition) {
                arr[k] = L[i];
                i++;
            } else {
                arr[k] = R[j];
                j++;
            }
            k++;
        }
        
        while (i < n1) {
            arr[k] = L[i];
            i++;
            k++;
        }
        
        while (j < n2) {
            arr[k] = R[j];
            j++;
            k++;
        }
        
        delete[] L;
        delete[] R;
    }
    
    static void mergeSort(vector<Product>& arr, int left, int right, bool ascending) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            mergeSort(arr, left, mid, ascending);
            mergeSort(arr, mid + 1, right, ascending);
            merge(arr, left, mid, right, ascending);
        }
    }
    
public:
    static void sortByRating(vector<Product>& products, bool ascending = true) {
        if (products.empty()) return;
        mergeSort(products, 0, products.size() - 1, ascending);
    }
};

class SelectionSorter {
public:
    static void sortBySoldCount(vector<Product>& products, bool ascending = true) {
        int n = products.size();
        for (int i = 0; i < n - 1; i++) {
            int extremeIdx = i;
            for (int j = i + 1; j < n; j++) {
                bool condition = ascending ? 
                    (products[j].soldCount < products[extremeIdx].soldCount) :
                    (products[j].soldCount > products[extremeIdx].soldCount);
                if (condition) {
                    extremeIdx = j;
                }
            }
            if (extremeIdx != i) {
                Product temp = products[i];
                products[i] = products[extremeIdx];
                products[extremeIdx] = temp;
            }
        }
    }
};

class Recommender {
private:
    static double calculateSimilarity(const Product& p1, const Product& p2) {
        double score = 0.0;

        if (p1.category == p2.category) {
            score += 40.0;
        }
        
        double priceDiff = abs(p1.price - p2.price);
        if (priceDiff < 50) score += 30.0;
        else if (priceDiff < 100) score += 20.0;
        else if (priceDiff < 200) score += 10.0;

        score += p2.rating * 4;
        
        score += min(10.0, p2.soldCount / 100.0);
        
        return score;
    }
    
    static void sortRecommendations(vector<pair<double, Product>>& items) {
        int n = items.size();
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (items[j].first < items[j + 1].first) {
                    pair<double, Product> temp = items[j];
                    items[j] = items[j + 1];
                    items[j + 1] = temp;
                }
            }
        }
    }
    
public:
    static vector<Product> getRecommendations(LinkedList& list, const Product& target, int count = 5) {
        vector<pair<double, Product>> scoredProducts;
        
        Node* current = list.getHead();
        while (current) {
            if (current->data.id != target.id) {
                double similarity = calculateSimilarity(target, current->data);
                scoredProducts.push_back({similarity, current->data});
            }
            current = current->next;
        }
        sortRecommendations(scoredProducts);

        vector<Product> recommendations;
        int limit = min(count, (int)scoredProducts.size());
        for (int i = 0; i < limit; i++) {
            recommendations.push_back(scoredProducts[i].second);
        }
        
        return recommendations;
    }
};

class ShoppingCart {
private:
    vector<Product> items;
    
public:
    void addItem(const Product& product) {
        items.push_back(product);
        colorMgr.printLineRandom("Added '" + product.name + "' to cart.");
    }
    
    bool removeItem(int productId) {
        for (auto it = items.begin(); it != items.end(); ++it) {
            if (it->id == productId) {
                colorMgr.printLineRandom("Removed '" + it->name + "' from cart.");
                items.erase(it);
                return true;
            }
        }
        return false;
    }
    
    void displayCart() const {
        if (items.empty()) {
            colorMgr.printLineRandom("Shopping cart is empty!");
            return;
        }
        
        colorMgr.printLineRandom("\n=== SHOPPING CART ===");
        double total = 0.0;
        
        for (const Product& item : items) {
            colorMgr.printRandom("ID: ");
            cout << item.id;
            colorMgr.printRandom(" | ");
            cout << item.name;
            colorMgr.printRandom(" | $");
            cout << item.price << endl;
            total += item.price;
        }
        
        colorMgr.printRandom("\nTotal: $");
        cout << total << endl;
        colorMgr.printRandom("Number of items: ");
        cout << items.size() << endl;
    }
    
    void clearCart() {
        items.clear();
        colorMgr.printLineRandom("Cart cleared!");
    }
    
    int getItemCount() const {
        return items.size();
    }
    
    double getTotalPrice() const {
        double total = 0.0;
        for (const Product& item : items) {
            total += item.price;
        }
        return total;
    }
};

class RecentView {
private:
    deque<Product> viewedItems;
    int maxSize;
    
public:
    RecentView(int size = 5) : maxSize(size) {}
    
    void addProduct(const Product& product) {
        for (auto it = viewedItems.begin(); it != viewedItems.end(); ++it) {
            if (it->id == product.id) {
                viewedItems.erase(it);
                break;
            }
        }
        
        viewedItems.push_front(product);
        
        if (viewedItems.size() > maxSize) {
            viewedItems.pop_back();
        }
    }
    
    void displayRecent() const {
        if (viewedItems.empty()) {
            colorMgr.printLineRandom("No recently viewed products!");
            return;
        }
        
        colorMgr.printLineRandom("\n=== RECENTLY VIEWED (" + to_string(viewedItems.size()) + " products) ===");
        int count = 1;
        for (const Product& product : viewedItems) {
            colorMgr.printRandom(to_string(count++) + ". ");
            product.display();
        }
    }
    
    vector<Product> getRecentProducts() const {
        return vector<Product>(viewedItems.begin(), viewedItems.end());
    }
};

class ProductManager {
private:
    LinkedList productList;
    CSVManager csvManager;
    Logger& logger;
    
public:
    ProductManager(Logger& log) : csvManager("products.csv"), logger(log) {
        csvManager.loadProducts(productList);
    }
    
    ~ProductManager() {
        csvManager.saveProducts(productList);
    }
    
    LinkedList& getProductList() { return productList; }
    
    void addNewProduct() {
        Product newProduct;
        
        colorMgr.printLineRandom("\n=== ADD NEW PRODUCT ===");

        while (true) {
            colorMgr.printRandom("Product ID: ");
            string input;
            cin >> input;

            bool valid = true;
            for (char c : input) {
                if (!isdigit(c)) {
                    valid = false;
                    break;
                }
            }
            
            if (!valid) {
                colorMgr.printLineRandom("Invalid ID! Please enter numbers only.");
                continue;
            }
            
            newProduct.id = stoi(input);
            if (productList.findById(newProduct.id)) {
                colorMgr.printLineRandom("Error: Product ID already exists! Please enter a different ID.");
            } else {
                break;
            }
        }
        
        colorMgr.printRandom("Product Name: ");
        cin.ignore();
        getline(cin, newProduct.name);

        while (true) {
            colorMgr.printRandom("Price: $");
            string input;
            cin >> input;
            
            bool valid = true;
            bool dotFound = false;
            for (char c : input) {
                if (!isdigit(c)) {
                    if (c == '.' && !dotFound) {
                        dotFound = true;
                    } else {
                        valid = false;
                        break;
                    }
                }
            }
            
            if (valid) {
                newProduct.price = stod(input);
                if (newProduct.price > 0) break;
            }
            colorMgr.printLineRandom("Invalid price! Please enter a positive number.");
        }
        
        colorMgr.printRandom("Category: ");
        cin.ignore();
        getline(cin, newProduct.category);

        while (true) {
            colorMgr.printRandom("Rating (0-5): ");
            string input;
            cin >> input;
            
            bool valid = true;
            bool dotFound = false;
            for (char c : input) {
                if (!isdigit(c)) {
                    if (c == '.' && !dotFound) {
                        dotFound = true;
                    } else {
                        valid = false;
                        break;
                    }
                }
            }
            
            if (valid) {
                newProduct.rating = stod(input);
                if (newProduct.rating >= 0 && newProduct.rating <= 5) break;
            }
            colorMgr.printLineRandom("Invalid rating! Please enter a number between 0 and 5.");
        }
        
        while (true) {
            colorMgr.printRandom("Sold Count: ");
            string input;
            cin >> input;
            
            bool valid = true;
            for (char c : input) {
                if (!isdigit(c)) {
                    valid = false;
                    break;
                }
            }
            
            if (valid) {
                newProduct.soldCount = stoi(input);
                if (newProduct.soldCount >= 0) break;
            }
            colorMgr.printLineRandom("Invalid count! Please enter a positive integer.");
        }
        
        while (true) {
            colorMgr.printRandom("Stock: ");
            string input;
            cin >> input;
            
            bool valid = true;
            for (char c : input) {
                if (!isdigit(c)) {
                    valid = false;
                    break;
                }
            }
            
            if (valid) {
                newProduct.stock = stoi(input);
                if (newProduct.stock >= 0) break;
            }
            colorMgr.printLineRandom("Invalid stock! Please enter a positive integer.");
        }
        
        colorMgr.printRandom("Brand: ");
        cin.ignore();
        getline(cin, newProduct.brand);
        
        colorMgr.printRandom("Description: ");
        getline(cin, newProduct.description);
        
        productList.add(newProduct);
        csvManager.saveProducts(productList);
        logger.addLog("Added product: " + newProduct.name + " (ID: " + to_string(newProduct.id) + ")");
        
        colorMgr.printLineRandom("\n✓ Product added successfully!");
        newProduct.display();
    }
    
    void removeProduct() {
        colorMgr.printLineRandom("\n=== REMOVE PRODUCT ===");
        
        int id;
        colorMgr.printRandom("Enter product ID to remove: ");
        cin >> id;
        
        Product* product = productList.findById(id);
        if (!product) {
            colorMgr.printLineRandom("Error: Product not found!");
            return;
        }
        
        colorMgr.printLineRandom("You are about to remove:");
        product->display();
        colorMgr.printRandom("Are you sure? (y/n): ");
        
        char confirm;
        cin >> confirm;
        
        if (confirm == 'y' || confirm == 'Y') {
            string productName = product->name;
            if (productList.removeById(id)) {
                csvManager.saveProducts(productList);
                logger.addLog("Removed product: " + productName + " (ID: " + to_string(id) + ")");
                colorMgr.printLineRandom("✓ Product removed successfully!");
            }
        } else {
            colorMgr.printLineRandom("Operation cancelled.");
        }
    }
    
    void editProduct() {
        colorMgr.printLineRandom("\n=== EDIT PRODUCT ===");
        
        int id;
        colorMgr.printRandom("Enter product ID to edit: ");
        cin >> id;
        
        Product* product = productList.findById(id);
        if (!product) {
            colorMgr.printLineRandom("Error: Product not found!");
            return;
        }
        
        colorMgr.printLineRandom("\nCurrent product details:");
        product->displayDetailed();
        
        colorMgr.printLineRandom("\nEnter new values (press Enter to keep current):");
        
        cin.ignore();
        colorMgr.printRandom("New name [" + product->name + "]: ");
        string newName;
        getline(cin, newName);
        if (!newName.empty()) product->name = newName;
        
        colorMgr.printRandom("New price [$" + to_string(product->price) + "]: ");
        string priceStr;
        getline(cin, priceStr);
        if (!priceStr.empty()) product->price = stod(priceStr);
        
        colorMgr.printRandom("New category [" + product->category + "]: ");
        string newCategory;
        getline(cin, newCategory);
        if (!newCategory.empty()) product->category = newCategory;
        
        colorMgr.printRandom("New rating [" + to_string(product->rating) + "]: ");
        string ratingStr;
        getline(cin, ratingStr);
        if (!ratingStr.empty()) product->rating = stod(ratingStr);
        
        colorMgr.printRandom("New sold count [" + to_string(product->soldCount) + "]: ");
        string soldStr;
        getline(cin, soldStr);
        if (!soldStr.empty()) product->soldCount = stoi(soldStr);
        
        colorMgr.printRandom("New stock [" + to_string(product->stock) + "]: ");
        string stockStr;
        getline(cin, stockStr);
        if (!stockStr.empty()) product->stock = stoi(stockStr);
        
        colorMgr.printRandom("New brand [" + product->brand + "]: ");
        string newBrand;
        getline(cin, newBrand);
        if (!newBrand.empty()) product->brand = newBrand;
        
        colorMgr.printRandom("New description [" + product->description + "]: ");
        string newDescription;
        getline(cin, newDescription);
        if (!newDescription.empty()) product->description = newDescription;
        
        csvManager.saveProducts(productList);
        logger.addLog("Edited product ID: " + to_string(id));
        colorMgr.printLineRandom("\n✓ Product updated successfully!");
        product->display();
    }
    
    void searchProducts() {
        colorMgr.printLineRandom("\n=== SEARCH PRODUCTS ===");
        colorMgr.printLineRandom("1. Search by name");
        colorMgr.printLineRandom("2. Search by category");
        colorMgr.printLineRandom("3. Search by price range");
        colorMgr.printLineRandom("4. Back to main menu");
        colorMgr.printRandom("Enter choice: ");
        
        int choice;
        cin >> choice;
        
        vector<Product> results;
        
        switch (choice) {
            case 1: {
                colorMgr.printRandom("Enter product name (or part of name): ");
                string name;
                cin.ignore();
                getline(cin, name);
                
                NameBST bst;
                bst.buildFromList(productList);
                results = bst.search(name);
                
                logger.addLog("Searched by name: " + name);
                break;
            }
                
            case 2: {
                colorMgr.printRandom("Enter category: ");
                string category;
                cin.ignore();
                getline(cin, category);
                
                CategoryHashTable hashTable;
                hashTable.buildFromList(productList);
                results = hashTable.searchByCategory(category);
                
                logger.addLog("Searched by category: " + category);
                break;
            }
                
            case 3: {
                double minPrice, maxPrice;
                colorMgr.printRandom("Enter minimum price: $");
                cin >> minPrice;
                colorMgr.printRandom("Enter maximum price: $");
                cin >> maxPrice;
                
                results = searchByPriceRange(productList, minPrice, maxPrice);
                
                logger.addLog("Searched by price range: $" + to_string(minPrice) + " - $" + to_string(maxPrice));
                break;
            }
                
            case 4:
                return;
                
            default:
                colorMgr.printLineRandom("Invalid choice!");
                return;
        }
        
        if (results.empty()) {
            colorMgr.printLineRandom("No products found!");
        } else {
            colorMgr.printLineRandom("\n✓ Found " + to_string(results.size()) + " product(s):");
            for (const Product& p : results) {
                p.display();
            }
        }
    }
    
    void sortProducts() {
        colorMgr.printLineRandom("\n=== SORT PRODUCTS ===");
        colorMgr.printLineRandom("1. Sort by price");
        colorMgr.printLineRandom("2. Sort by rating");
        colorMgr.printLineRandom("3. Sort by sold count");
        colorMgr.printLineRandom("4. Back to main menu");
        colorMgr.printRandom("Enter choice: ");
        
        int choice;
        cin >> choice;
        
        if (choice == 4) return;
        
        colorMgr.printLineRandom("\nSort order:");
        colorMgr.printLineRandom("1. Ascending (low to high)");
        colorMgr.printLineRandom("2. Descending (high to low)");
        colorMgr.printRandom("Enter order: ");
        
        int orderChoice;
        cin >> orderChoice;
        
        if (orderChoice != 1 && orderChoice != 2) {
            colorMgr.printLineRandom("Invalid choice!");
            return;
        }
        
        bool ascending = (orderChoice == 1);
        
        vector<Product> products = productList.toVector();
        
        if (products.empty()) {
            colorMgr.printLineRandom("No products to sort!");
            return;
        }
        
        switch (choice) {
            case 1:
                QuickSorter::sortByPrice(products, ascending);
                logger.addLog("Sorted products by price (" + string(ascending ? "ascending" : "descending") + ")");
                break;
                
            case 2:
                MergeSorter::sortByRating(products, ascending);
                logger.addLog("Sorted products by rating (" + string(ascending ? "ascending" : "descending") + ")");
                break;
                
            case 3:
                SelectionSorter::sortBySoldCount(products, ascending);
                logger.addLog("Sorted products by sold count (" + string(ascending ? "ascending" : "descending") + ")");
                break;
                
            default:
                colorMgr.printLineRandom("Invalid choice!");
                return;
        }
        
        colorMgr.printLineRandom("\n=== SORTED PRODUCTS ===");
        string sortBy;
        switch (choice) {
            case 1: sortBy = "Price"; break;
            case 2: sortBy = "Rating"; break;
            case 3: sortBy = "Sold Count"; break;
        }
        colorMgr.printLineRandom("Sorting by: " + sortBy + " (" + (ascending ? "Ascending" : "Descending") + ")");
        
        for (const Product& p : products) {
            p.display();
        }
    }
    
    void showProductDetails() {
        colorMgr.printLineRandom("\n=== VIEW PRODUCT DETAILS ===");
        
        int id;
        colorMgr.printRandom("Enter product ID: ");
        cin >> id;
        
        Product* product = productList.findById(id);
        if (!product) {
            colorMgr.printLineRandom("Product not found!");
            return;
        }
        
        product->displayDetailed();
        logger.addLog("Viewed details for product ID: " + to_string(id));
    }

    void showProductRecommendations() {
        colorMgr.printLineRandom("\n=== PRODUCT RECOMMENDATIONS ===");
        
        int id;
        colorMgr.printRandom("Enter product ID for recommendations: ");
        cin >> id;
        
        Product* product = productList.findById(id);
        if (!product) {
            colorMgr.printLineRandom("Product not found!");
            return;
        }
        
        colorMgr.printLineRandom("\nBase product:");
        product->displayDetailed();
        
        vector<Product> recommendations = Recommender::getRecommendations(productList, *product, 5);
        
        if (recommendations.empty()) {
            colorMgr.printLineRandom("No recommendations available!");
        } else {
            colorMgr.printLineRandom("\n✓ Recommended products (based on category, price, and rating):");
            for (size_t i = 0; i < recommendations.size(); i++) {
                colorMgr.printRandom("\n" + to_string(i + 1) + ". ");
                recommendations[i].display();
            }
        }
        
        logger.addLog("Viewed recommendations for product ID: " + to_string(id));
    }
};

class StoreXSystem {
private:
    Logger logger;
    ProductManager productManager;
    ShoppingCart cart;
    RecentView recentView;
    
public:
    StoreXSystem() : productManager(logger) {}
    
    void run() {
        for(int i = 0; i < 50; i++) colorMgr.printRandom("=");
        cout << endl;
        colorMgr.printLineRandom("       WELCOME TO STOREX SYSTEM");
        colorMgr.printLineRandom("  Online Store Management System");
        for(int i = 0; i < 50; i++) colorMgr.printRandom("=");
        cout << endl;
        
        bool running = true;
        
        while (running) {
            displayMainMenu();
            int choice;
            cin >> choice;

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            
            switch (choice) {
                case 1:
                    productManager.addNewProduct();
                    break;
                    
                case 2:
                    productManager.removeProduct();
                    break;
                    
                case 3:
                    productManager.editProduct();
                    break;
                    
                case 4:
                    productManager.getProductList().displayAll();
                    logger.addLog("Viewed all products");
                    break;
                    
                case 5:
                    productManager.searchProducts();
                    break;
                    
                case 6:
                    productManager.sortProducts();
                    break;
                    
                case 7: {
                    colorMgr.printLineRandom("\n=== VIEW PRODUCT DETAILS ===");
                    int id;
                    colorMgr.printRandom("Enter product ID: ");
                    cin >> id;
                    
                    Product* product = productManager.getProductList().findById(id);
                    if (product) {
                        product->displayDetailed();
                        recentView.addProduct(*product);
                        logger.addLog("Viewed details for product ID: " + to_string(id));
                    } else {
                        colorMgr.printLineRandom("Product not found!");
                    }
                    break;
                }
                    
                case 8: {
                    colorMgr.printLineRandom("\n=== PRODUCT RECOMMENDATIONS ===");
                    int id;
                    colorMgr.printRandom("Enter product ID for recommendations: ");
                    cin >> id;
                    
                    Product* product = productManager.getProductList().findById(id);
                    if (product) {
                        colorMgr.printLineRandom("\nBase product:");
                        product->displayDetailed();
                        
                        vector<Product> recommendations = Recommender::getRecommendations(
                            productManager.getProductList(), *product, 5);
                        
                        if (recommendations.empty()) {
                            colorMgr.printLineRandom("No recommendations available!");
                        } else {
                            colorMgr.printLineRandom("\n✓ Recommended products:");
                            for (size_t i = 0; i < recommendations.size(); i++) {
                                colorMgr.printRandom("\n" + to_string(i + 1) + ". ");
                                recommendations[i].display();
                            }
                        }
                        
                        recentView.addProduct(*product);
                        logger.addLog("Viewed recommendations for product ID: " + to_string(id));
                    } else {
                        colorMgr.printLineRandom("Product not found!");
                    }
                    break;
                }
                    
                case 9:
                    manageCart();
                    break;
                    
                case 10:
                    recentView.displayRecent();
                    logger.addLog("Viewed recent products");
                    break;
                    
                case 0:
                    running = false;
                    colorMgr.printLineRandom("\nExiting StoreX System...");
                    break;
                    
                default:
                    colorMgr.printLineRandom("Invalid choice! Please enter a number between 0-10.");
            }
            
            if (choice != 0 && choice >= 1 && choice <= 10) {
                colorMgr.printRandom("\nPress Enter to continue...");
                cin.get();
            }
        }

        for(int i = 0; i < 50; i++) colorMgr.printRandom("=");
        cout << endl;
        logger.displayLogs();
        logger.saveToFile();
        colorMgr.printLineRandom("\nThank you for using StoreX System!");
        for(int i = 0; i < 50; i++) colorMgr.printRandom("=");
        cout << endl;
    }
    
private:
    void displayMainMenu() {
        colorMgr.printLineRandom("\n========== MAIN MENU ==========");
        colorMgr.printLineRandom("1. Add new product");
        colorMgr.printLineRandom("2. Remove product");
        colorMgr.printLineRandom("3. Edit product");
        colorMgr.printLineRandom("4. Display all products");
        colorMgr.printLineRandom("5. Search products");
        colorMgr.printLineRandom("6. Sort products");
        colorMgr.printLineRandom("7. View product details");
        colorMgr.printLineRandom("8. Get product recommendations");
        colorMgr.printLineRandom("9. Shopping cart");
        colorMgr.printLineRandom("10. Recently viewed products");
        colorMgr.printLineRandom("0. Exit system");
        colorMgr.printLineRandom("===============================");
        colorMgr.printRandom("Enter your choice: ");
    }
    
    void manageCart() {
        while (true) {
            colorMgr.printLineRandom("\n=== SHOPPING CART ===");
            colorMgr.printRandom("Current items: ");
            cout << cart.getItemCount() << endl;
            colorMgr.printRandom("Total: $");
            cout << cart.getTotalPrice() << endl;
            colorMgr.printLineRandom("\n1. Add item to cart");
            colorMgr.printLineRandom("2. Remove item from cart");
            colorMgr.printLineRandom("3. View cart contents");
            colorMgr.printLineRandom("4. Clear cart");
            colorMgr.printLineRandom("5. Back to main menu");
            colorMgr.printRandom("Enter choice: ");
            
            int choice;
            cin >> choice;
            
            switch (choice) {
                case 1: {
                    int id;
                    colorMgr.printRandom("Enter product ID to add to cart: ");
                    cin >> id;
                    
                    Product* product = productManager.getProductList().findById(id);
                    if (product) {
                        cart.addItem(*product);
                        logger.addLog("Added product ID " + to_string(id) + " to cart");
                    } else {
                        colorMgr.printLineRandom("Product not found!");
                    }
                    break;
                }
                    
                case 2: {
                    int id;
                    colorMgr.printRandom("Enter product ID to remove from cart: ");
                    cin >> id;
                    
                    if (cart.removeItem(id)) {
                        logger.addLog("Removed product ID " + to_string(id) + " from cart");
                    } else {
                        colorMgr.printLineRandom("Product not found in cart!");
                    }
                    break;
                }
                    
                case 3:
                    cart.displayCart();
                    logger.addLog("Viewed shopping cart");
                    break;
                    
                case 4:
                    cart.clearCart();
                    logger.addLog("Cleared shopping cart");
                    break;
                    
                case 5:
                    return;
                    
                default:
                    colorMgr.printLineRandom("Invalid choice!");
            }
            
            colorMgr.printRandom("\nPress Enter to continue...");
            cin.ignore();
            cin.get();
        }
    }
};

int main() {
    StoreXSystem system;
    system.run();
    return 0;
}