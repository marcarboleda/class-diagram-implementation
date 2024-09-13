#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

class Product {
public:
    string prodId;
    string prodName;
    double prodPrice;
    double prodStock;

    Product(string prodId, string prodName, double prodPrice, double prodStock) :
            prodId(prodId), prodName(prodName), prodPrice(prodPrice), prodStock(prodStock) {}
};

vector<Product> items = {
        Product("001", "Pencil", 10.00, 35),
        Product("002", "Pad Paper", 40.00, 20),
        Product("003", "Eraser", 15.00, 40),
        Product("004", "Ballpen", 12.00, 45),
        Product("005", "Ruler", 20.00, 23)
};

class ShopCart {
public:
    vector<Product> cartItems;
    vector<int> quantities;

    void addProduct(const Product& product, int quantity) {
        cartItems.push_back(product);
        quantities.push_back(quantity);
    }

    void viewCart() {
        if (cartItems.empty()) {
            cout << "\nShopping cart is empty.\n" << endl;
            return;
        }

        cout << "\nShopping Cart:\n";
        cout << setw(10) << "Product ID "
                << setw(15) << "Name"
                << setw(10) << "Price"
                << setw(10) << "Quantity" << endl;

        double totalAmount = 0.0;
        for (size_t i = 0; i < cartItems.size(); i++) {
            const Product& product = cartItems[i];
            totalAmount += product.prodPrice * quantities[i];
            cout << setw(10) << product.prodId << setw(15) << product.prodName << setw(10)
                 << product.prodPrice << setw(10) << quantities[i] << endl;
        }
        cout << "Total Amount: " << totalAmount << endl;
    }

    void clearCart() {
        cartItems.clear();
        quantities.clear();
    }
};

ShopCart cart;


void displayProd() {
    char addChoice;
    do {
        cout << "\nProduct Details:\n";
        cout << setw(10) << "Product ID "
                << setw(15) << "Name"
                << setw(10) << "Price"
                << setw(10) << "Quantity" << endl;

        for (const Product &product : items) {
            cout << setw(10) << product.prodId << setw(15) << product.prodName << setw(10)
                 << product.prodPrice << setw(10) << product.prodStock << endl;
        }

        cout << "\nAdd product to shopping cart (Y/N): ";
        cin >> addChoice;

        while (addChoice != 'Y' && addChoice != 'N') {
            cout << "\nInvalid input. Please enter Y or N only: ";
            cin >> addChoice;
        }

        if (addChoice == 'Y' || addChoice == 'y') {
            string selectedId;
            int quantity;
            cout << "\nEnter product ID to add to cart: ";
            cin >> selectedId;

            bool found = false;
            for (Product &product : items) {
                if (product.prodId == selectedId) {
                    found = true;
                    cout << "Enter quantity: ";
                    cin >> quantity;
                    if (quantity <= product.prodStock) {
                        cart.addProduct(product, quantity);
                        cout << "Product added to cart." << endl;
                        product.prodStock -= quantity; // Reduce stock
                    } else {
                        cout << "\nInsufficient stock.\n" << endl;
                    }
                    break;
                }
            }
            if (!found) {
                cout << "\nProduct not found.\n" << endl;
            }
        }
    } while (addChoice != 'N');
}

void viewOrder() {
    if (cart.cartItems.empty()) {
        cout << "\nYour order is empty." << endl;
        return;
    }

    cart.viewCart();

    char checkoutChoice;
    cout << "Do you want to checkout? (Y/N): ";
    cin >> checkoutChoice;

    if (checkoutChoice == 'Y' || checkoutChoice == 'y') {
        cart.clearCart();
        cout << "\nCheckout successful!\n" << endl;
    }
}

int main() {
    int choice;
    do {
        cout << "\n---------------------------------" << endl;
        cout << "       Online Grocery Store      " << endl;
        cout << "---------------------------------" << endl;
        cout << "Menu: \n";
        cout << "1 - View products\n";
        cout << "2 - View shopping cart\n";
        cout << "3 - View orders\n";
        cout << "4 - Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        while (choice < 1 || choice > 4) {
            cout << "\nInvalid input. Please try again\n";
            cin >> choice;
        }

        switch (choice) {
            case 1:
                displayProd();
                break;

            case 2:
                cart.viewCart();
                break;

            case 3:
                viewOrder();
                break;

            case 4:
                cout << "\nThank you for using the Online Grocery Store!\n" << endl;
                break;

            default:
                break;
        }
    } while (choice != 4);

    return 0;
}