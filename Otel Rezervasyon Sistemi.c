#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>

// Müşteri detayları kısmı
struct CustomerDetails {
    char roomnumber[10];
    char name[20];
    char address[25];
    char phonenumber[15];
    char email[20];
    char period[10];
    char arrivaldate[10];
};

// Ağaç düğüm yapısı
struct TreeNode {
    struct CustomerDetails customer;
    struct TreeNode* left;
    struct TreeNode* right;
};

// Kök düğüm 
struct TreeNode* root = NULL;

// Yeni node oluşturma
struct TreeNode* createNode(struct CustomerDetails customer) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->customer = customer;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Müşteri ekleme
struct TreeNode* insertCustomer(struct TreeNode* root, struct CustomerDetails customer) {
    if (root == NULL) {
        return createNode(customer);
    }
    if (strcmp(customer.roomnumber, root->customer.roomnumber) < 0) {
        root->left = insertCustomer(root->left, customer);
    } else if (strcmp(customer.roomnumber, root->customer.roomnumber) > 0) {
        root->right = insertCustomer(root->right, customer);
    }
    return root;
}

// Müşteriyi arama
struct TreeNode* searchCustomer(struct TreeNode* root, char roomnumber[]) {
    if (root == NULL || strcmp(root->customer.roomnumber, roomnumber) == 0) {
        return root;
    }
    if (strcmp(roomnumber, root->customer.roomnumber) < 0) {
        return searchCustomer(root->left, roomnumber);
    }
    return searchCustomer(root->right, roomnumber);
}

// Müşteri silme
struct TreeNode* deleteCustomer(struct TreeNode* root, char roomnumber[]) {
    if (root == NULL) {
        return root;
    }
    if (strcmp(roomnumber, root->customer.roomnumber) < 0) {
        root->left = deleteCustomer(root->left, roomnumber);
    } else if (strcmp(roomnumber, root->customer.roomnumber) > 0) {
        root->right = deleteCustomer(root->right, roomnumber);
    } else {
        if (root->left == NULL) {
            struct TreeNode* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct TreeNode* temp = root->left;
            free(root);
            return temp;
        }
        struct TreeNode* temp = root->right;
        while (temp && temp->left != NULL) {
            temp = temp->left;
        }
        root->customer = temp->customer;
        root->right = deleteCustomer(root->right, temp->customer.roomnumber);
    }
    return root;
}

// Müşteri yazdırma
void printCustomers(struct TreeNode* root) {
    if (root != NULL) {
        printCustomers(root->left);
        printf("Oda No: %s, Isim: %s, Telefon: %s\n",
               root->customer.roomnumber,
               root->customer.name,
               root->customer.phonenumber);
        printCustomers(root->right);
    }
}

// Yeni müşteri ekleme
void add() {
    struct CustomerDetails customer;
    printf("\nMusteri Bilgisi Giriniz:");
    printf("\nOda Numarasi: ");
    scanf("%s", customer.roomnumber);
    printf("Ad: ");
    scanf("%s", customer.name);
    printf("Adres: ");
    scanf("%s", customer.address);
    printf("Telefon Numarasi: ");
    scanf("%s", customer.phonenumber);
    printf("Email: ");
    scanf("%s", customer.email);
    printf("Rezervasyon Suresi ('x' Gun): ");
    scanf("%s", customer.period);
    printf("Giris Tarihi (gg\\ay\\yyyy): ");
    scanf("%s", customer.arrivaldate);

    root = insertCustomer(root, customer);
    printf("\nMusteri basariyla eklendi!\n");
    getchar();
}

// Müşteri listeleme
void list() {
    printf("\nMusteri detaylari:\n");
    printCustomers(root);
    getchar();
}

// Müşteri arama
void search() {
    char roomnumber[10];
    printf("\nAramak istediginiz oda numarasini giriniz: ");
    scanf("%s", roomnumber);

    struct TreeNode* result = searchCustomer(root, roomnumber);
    if (result != NULL) {
        printf("\nMusteri Bulundu:\n");
        printf("Oda No: %s\nAd: %s\nAdres: %s\nTelefon: %s\nEmail: %s\nSure: %s\nGiris Tarihi: %s\n",
               result->customer.roomnumber,
               result->customer.name,
               result->customer.address,
               result->customer.phonenumber,
               result->customer.email,
               result->customer.period,
               result->customer.arrivaldate);
    } else {
        printf("\nMusteri bulunamadi.\n");
    }
    getchar();
}

// Müşteri silme
void delete1() {
    char roomnumber[10];
    printf("\nSilmek istediginiz oda numarasini giriniz: ");
    scanf("%s", roomnumber);

    root = deleteCustomer(root, roomnumber);
    printf("\nMusteri basariyla silindi.\n");
    getchar();
}

int main() {
    char choice;
    while (1) {
        printf("\n1. Oda Rezervi\n2. Musteri Detayi\n3. Musteri Silme\n4. Kayit Sorusturma\n5. Cikis\nSecim: ");
        choice = getchar();
        getchar(); // Enter tuşunu yutmak için
        switch (choice) {
            case '1': add(); break;
            case '2': list(); break;
            case '3': delete1(); break;
            case '4': search(); break;
            case '5': exit(0);
            default: printf("\nHatali giris!"); break;
        }
    }
    return 0;
}
