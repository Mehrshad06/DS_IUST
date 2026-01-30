#include <bits/stdc++.h>
using namespace std;


class Product {
public:
    int id;
    string name;
    double price;
    string category;
    double rating;
    int soldCount;
    int stock;
    string brand;
    string description;
};

class Node {
public:
    Product data;
    Node* next;
    Node(Product p) {
        data = p;
        next = nullptr;
    }
};


class LinkedList {
private:
    Node* head;
public:
    LinkedList() { head = nullptr; }
    Node* getHead() { return head; }
    void add(Product p) {
        Node* n = new Node(p);
        if (!head) { head = n; return; }
        Node* t = head;
        while (t->next) t = t->next;
        t->next = n;
    }
    void removeById(int id) {
        if (!head) return;
        if (head->data.id == id) {
            Node* d = head;
            head = head->next;
            delete d;
            return;
        }
        Node* t = head;
        while (t->next && t->next->data.id != id)
            t = t->next;
        if (t->next) {
            Node* d = t->next;
            t->next = t->next->next;
            delete d;
        }
    }
    Product* findById(int id) {
        Node* t = head;
        while (t) {
            if (t->data.id == id) return &t->data;
            t = t->next;
        }
        return nullptr;
    }
    void display() {
        Node* t = head;
        while (t) {
            Product p = t->data;
            cout << p.id << " | " << p.name << " | " << p.price << " | " 
                 << p.category << " | " << p.rating << " | " 
                 << p.soldCount << " | " << p.stock << endl;
            t = t->next;
        }
    }
};

class CSVManager {
private:
    string filename;
public:
    CSVManager(string f) { filename = f; }
    void load(LinkedList &list) {
        ifstream file(filename);
        if (!file.is_open()) return;
        string line;
        getline(file, line);
        while (getline(file, line)) {
            stringstream ss(line);
            vector<string> t;
            string x;
            while (getline(ss, x, ',')) t.push_back(x);
            if (t.size() < 9) continue;
            Product p;
            p.id = stoi(t[0]);
            p.name = t[1];
            p.price = stod(t[2]);
            p.category = t[3];
            p.rating = stod(t[4]);
            p.soldCount = stoi(t[5]);
            p.stock = stoi(t[6]);
            p.brand = t[7];
            p.description = t[8];
            list.add(p);
        }
    }
    void save(LinkedList &list) {
        ofstream file(filename);
        file << "id,name,price,category,rating,soldCount,stock,brand,description\n";
        Node* t = list.getHead();
        while (t) {
            Product p = t->data;
            file << p.id << "," << p.name << "," << p.price << "," 
                 << p.category << "," << p.rating << "," << p.soldCount << ","
                 << p.stock << "," << p.brand << "," << p.description;
            if (t->next) file << "\n";
            t = t->next;
        }
    }
};

class ProductManager {
private:
    LinkedList products;
    CSVManager csv;
public:
    ProductManager(string file) : csv(file) {
        csv.load(products);
    }
    LinkedList& getList() { return products; }
    void addProduct() {
        Product p;
        cout << "ID: "; cin >> p.id;
        cout << "Name: "; cin.ignore(); getline(cin, p.name);
        cout << "Price: "; cin >> p.price;
        cout << "Category: "; cin.ignore(); getline(cin, p.category);
        cout << "Rating: "; cin >> p.rating;
        cout << "Sold: "; cin >> p.soldCount;
        cout << "Stock: "; cin >> p.stock;
        cout << "Brand: "; cin.ignore(); getline(cin, p.brand);
        cout << "Description: "; getline(cin, p.description);
        products.add(p);
        csv.save(products);
    }

    void showProducts() { products.display(); }
    void removeProduct() {
        int id; cout << "ID: "; cin >> id;
        products.removeById(id);
        csv.save(products);
    }
    void editProduct() {
        int id; cout << "ID: "; cin >> id;
        Product* p = products.findById(id);
        if (!p) { cout << "Not found\n"; return; }
        cout << "Name: "; cin.ignore(); getline(cin, p->name);
        cout << "Price: "; cin >> p->price;
        cout << "Category: "; cin.ignore(); getline(cin, p->category);
        cout << "Rating: "; cin >> p->rating;
        cout << "Sold: "; cin >> p->soldCount;
        cout << "Stock: "; cin >> p->stock;
        cout << "Brand: "; cin.ignore(); getline(cin, p->brand);
        cout << "Description: "; getline(cin, p->description);
        csv.save(products);
    }
};
class BSTNode {
public:
    Product data;
    BSTNode* left;
    BSTNode* right;
    BSTNode(Product p) { data=p; left=right=nullptr; }
};

class BST {
private:
    BSTNode* root=nullptr;
    BSTNode* insert(BSTNode* n, Product p) {
        if (!n) return new BSTNode(p);
        if (p.name < n->data.name) n->left = insert(n->left,p);
        else n->right = insert(n->right,p);
        return n;
    }
    void search(BSTNode* n, string name) {
        if (!n) return;
        if (n->data.name == name)
            cout << n->data.id << " | " << n->data.name << endl;
        if (name < n->data.name) search(n->left,name);
        else search(n->right,name);
    }

public:
    void insert(Product p) { root = insert(root,p); }
    void search(string name) { search(root,name); }
};


class HashTable {
private:
    static const int S = 50;
    vector<Product> table[S];
    int h(string k) { int s=0; for(char c:k) s+=c; return s%S; }
public:
    void insert(Product p) { table[h(p.category)].push_back(p); }

    void search(string cat) {
        int i = h(cat);
        for (auto &p : table[i])
            if (p.category == cat)
                cout << p.id << " | " << p.name << endl;
    }
};

class PriceRangeSearch {
public:
    static void search(LinkedList &l, double a, double b) {
        Node* t = l.getHead();
        while (t) {
            if (t->data.price >= a && t->data.price <= b)
                cout << t->data.id << " | " << t->data.name << endl;
            t = t->next;
        }
    }
};

class SearchManager {
private:
    BST bst;
    HashTable ht;
    LinkedList &list;
public:
    SearchManager(LinkedList &l) : list(l) {
        Node* t = l.getHead();
        while (t) {
            bst.insert(t->data);
            ht.insert(t->data);
            t = t->next;
        }
    }

    void byName() {
        string n; cin.ignore(); getline(cin,n);
        bst.search(n);
    }

    void byCat() {
        string c; cin.ignore(); getline(cin,c);
        ht.search(c);
    }

    void byPrice() {
        double a,b; cin>>a>>b;
        PriceRangeSearch::search(list,a,b);
    }
};

class QuickSort {
public:
    static int part(vector<Product>& a,int l,int r,bool asc){
        double p = a[r].price; int i=l-1;
        for(int j=l;j<r;j++){
            if(asc? a[j].price<=p : a[j].price>=p)
                swap(a[++i],a[j]);
        }
        swap(a[i+1],a[r]);
        return i+1;
    }
    static void sort(vector<Product>& a,int l,int r,bool asc){
        if(l<r){
            int pi=part(a,l,r,asc);
            sort(a,l,pi-1,asc);
            sort(a,pi+1,r,asc);
        }
    }
};
class MergeSort {
public:
    static void merge(vector<Product>& a,int l,int m,int r,bool asc){
        int n1=m-l+1,n2=r-m;
        vector<Product> L(n1),R(n2);
        for(int i=0;i<n1;i++) L[i]=a[l+i];
        for(int j=0;j<n2;j++) R[j]=a[m+1+j];
        int i=0,j=0,k=l;
        while(i<n1 && j<n2){
            if(asc? L[i].rating<=R[j].rating : L[i].rating>=R[j].rating)
                a[k++]=L[i++];
            else a[k++]=R[j++];
        }
        while(i<n1) a[k++]=L[i++];
        while(j<n2) a[k++]=R[j++];
    }
    static void sort(vector<Product>& a,int l,int r,bool asc){
        if(l<r){
            int m=(l+r)/2;
            sort(a,l,m,asc);
            sort(a,m+1,r,asc);
            merge(a,l,m,r,asc);
        }
    }
};
class HeapSort {
public:
    static void heapify(vector<Product>& a,int n,int i,bool asc){
        int lg=i,l=2*i+1,r=2*i+2;
        auto cmp=[&](int x,int y){
            return asc? a[x].soldCount > a[y].soldCount : a[x].soldCount < a[y].soldCount;
        };
        if(l<n && cmp(l,lg)) lg=l;
        if(r<n && cmp(r,lg)) lg=r;
        if(lg!=i){ swap(a[i],a[lg]); heapify(a,n,lg,asc); }
    }
    static void sort(vector<Product>& a,bool asc){
        int n=a.size();
        for(int i=n/2-1;i>=0;i--) heapify(a,n,i,asc);
        for(int i=n-1;i>0;i--){
            swap(a[0],a[i]);
            heapify(a,i,0,asc);
        }
    }
};

class SortManager {
private:
    LinkedList &list;
public:
    SortManager(LinkedList &l):list(l){}
    vector<Product> toVec(){
        vector<Product> v;
        for(Node* t=list.getHead(); t; t=t->next)
            v.push_back(t->data);
        return v;
    }
    void menu(){
        int c; cin>>c;
        int o; cin>>o;
        bool asc=o==1;
        auto v=toVec();

        if(c==1) QuickSort::sort(v,0,v.size()-1,asc);
        else if(c==2) MergeSort::sort(v,0,v.size()-1,asc);
        else HeapSort::sort(v,asc);

        for(auto&p:v)
            cout<<p.id<<" | "<<p.name<<" | "<<p.price<<" | "
                <<p.rating<<" | "<<p.soldCount<<endl;
    }
};


class Recommender {
public:
    static void go(LinkedList &l,Product t){
        vector<pair<double,Product>> v;
        Node* n=l.getHead();
        while(n){
            Product p=n->data;
            if(p.id!=t.id){
                double s=0;
                if(p.category==t.category) s+=50;
                s+=(5-abs(p.price-t.price))*0.5;
                s+=p.rating*2;
                v.push_back({s,p});
            }
            n=n->next;
        }
        sort(v.begin(),v.end(),[](auto&a,auto&b){return a.first>b.first;});
        for(int i=0;i<min(5,(int)v.size());i++)
            cout<<v[i].second.name<<" | score="<<v[i].first<<endl;
    }
};

class Cart {
private:
    vector<Product> items;
public:
    void add(Product p){ items.push_back(p); }
    void rem(int id){
        for(int i=0;i<items.size();i++)
            if(items[i].id==id){ items.erase(items.begin()+i); return; }
    }
    void show(){
        double tot=0;
        for(auto&p:items){
            cout<<p.id<<" | "<<p.name<<" | "<<p.price<<endl;
            tot+=p.price;
        }
        cout<<"Total="<<tot<<endl;
    }
};


int main() {
    ProductManager pm("products.csv");

    while(true){
        cout<<"\n1 Add\n2 Del\n3 Edit\n4 Show\n5 Search\n6 Sort\n7 Rec\n8 Cart\n9 Exit\n";
        int c; cin>>c;
        if(c==1) pm.addProduct();
        else if(c==2) pm.removeProduct();
        else if(c==3) pm.editProduct();
        else if(c==4) pm.showProducts();
        else if(c==5){
            cout<<"1 Name 2 Cat 3 Price\n";
            int sc; cin>>sc;
            SearchManager sm(pm.getList());
            if(sc==1) sm.byName();
            else if(sc==2) sm.byCat();
            else sm.byPrice();
        }
        else if(c==6){
            cout<<"1 Price 2 Rating 3 Sold\n1 Asc 2 Desc\n";
            SortManager sm(pm.getList());
            sm.menu();
        }
        else if(c==7){
            int id; cin>>id;
            Product* p=pm.getList().findById(id);
            if(p) Recommender::go(pm.getList(),*p);
        }
        else if(c==8){
            Cart cart;
            while(true){
                cout<<"1 Add 2 Del 3 Show 4 Exit\n";
                int cc; cin>>cc;
                if(cc==4) break;
                if(cc==1){
                    int id; cin>>id;
                    Product* p=pm.getList().findById(id);
                    if(p) cart.add(*p);
                }
                else if(cc==2){
                    int id; cin>>id;
                    cart.rem(id);
                }
                else cart.show();
            }
        }
        else break;
    }
}
