#include <iostream>
#include <vector>
#include <algorithm>  // for remove_if

using namespace std;

class product {
public:
    int id;
    string name;
    double price;
    int stock;

    product(int p_id, string p_name, double p_price, int p_stock) {
        id = p_id;
        name = p_name;
        price = p_price;
        stock = p_stock;
    }
};

class Cart {
public:
    vector<pair<product, int>> items;

    void addProduct(product p, int quantity) {
        items.push_back(make_pair(p, quantity));
    }
};

vector<product> productList;
cart cart;  // Use lowercase 'cart'

void addProduct(int id, string name, double price, int stock) {
    product newProduct(id, name, price, stock);
    productList.push_back(newProduct);
    cout << "Product added: " << name << endl;
}

void listProducts() {
    cout << "Available Products:" << endl;
    for (auto &product : productList) {
        cout << "ID: " << product.id << ", Name: " << product.name
             << ", Price: " << product.price << ", Stock: " << product.stock << endl;
    }
}

void editProduct(int id, string newName, double newPrice, int newStock) {
    for (auto &product : productList) {
        if (product.id == id) {
            product.name = newName;
            product.price = newPrice;
            product.stock = newStock;
            cout << "Product updated: " << newName << endl;
            return;
        }
    }
    cout << "Product not found!" << endl;
}

void deleteProduct(int id) {
    productList.erase(remove_if(productList.begin(), productList.end(),
                                [id](product &product) { return product.id == id; }),
                      productList.end());
    cout << "Product deleted!" << endl;
}

void addToCart(int productId, int quantity) {
    for (auto &product : productList) {
        if (product.id == productId) {
            if (product.stock >= quantity) {
                cart.addProduct(product, quantity);
                product.stock -= quantity;
                cout << quantity << " x " << product.name << " added to cart." << endl;
            } else {
                cout << "Not enough stock!" << endl;
            }
            return;
        }
    }
    cout << "Product not found!" << endl;
}

void viewCart() {
    cout << "Cart Items:" << endl;
    for (auto &item : cart.items) {
        cout << item.second << " x " << item.first.name << " - Total: "
             << item.second * item.first.price << endl;
    }
}

void removeFromCart(int productId) {
    cart.items.erase(remove_if(cart.items.begin(), cart.items.end(),
                               [productId](pair<product, int> &item) {
                                   return item.first.id == productId;
                               }),
                     cart.items.end());
    cout << "Product removed from cart!" << endl;
}

void updateCartQuantity(int productId, int newQuantity) {
    for (auto &item : cart.items) {
        if (item.first.id == productId) {
            item.second = newQuantity;
            cout << "Cart updated!" << endl;
            return;
        }
    }
    cout << "Product not found in cart!" << endl;
}

void checkout() {
    double total = 0;
    for (auto &item : cart.items) {
        total += item.first.price * item.second;
    }
    cout << "Total amount: $" << total << ". Payment processed!" << endl;
    cart.items.clear();
}

int main() {
    // Test product functions
    addProduct(1, "Laptop", 1000.0, 5);
    addProduct(2, "Mouse", 25.0, 50);
    addProduct(3, "Keyboard", 50.0, 10);
    listProducts();
    editProduct(1, "Gaming Laptop", 1500.0, 3);
    listProducts();
    deleteProduct(2);
    listProducts();

    // Test cart features
    addToCart(1, 2);
    viewCart();
    updateCartQuantity(1, 3);
    viewCart();
    removeFromCart(1);
    viewCart();

    // Test checkout
    addToCart(3, 2);
    viewCart();
    checkout();

    return 0;
}
