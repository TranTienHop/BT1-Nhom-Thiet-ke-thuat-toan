#include <iostream>
#include <string>
#include <map>
#include <queue>

using namespace std;

struct Node {
    char data;
    int freq;
    Node *left, *right;

    Node(char data, int freq) {
        this->data = data;
        this->freq = freq;
        left = right = NULL;
    }

    Node(Node* left, Node* right) {
        data = '\0';
        freq = left->freq + right->freq;
        this->left = left;
        this->right = right;
    }
};

struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

void taoMa(Node* root, string code, map<char, string>& huffmanCode) {
    if (root == NULL)
        return;

    if (root->left == NULL && root->right == NULL) {
        huffmanCode[root->data] = code;
        return;
    }

    taoMa(root->left, code + "0", huffmanCode);
    taoMa(root->right, code + "1", huffmanCode);
}

void inCay(Node* root, string space = "") {
    if (root == NULL)
        return;

    if (root->left == NULL && root->right == NULL) {
        cout << space << root->data << " : " << root->freq << endl;
        return;
    }

    inCay(root->left, space + "0");
    inCay(root->right, space + "1");
}

int main() {
    string text;

    cout << "Nhap van ban: ";
    getline(cin, text);

    if (text.empty()) {
        cout << "Van ban rong!";
        return 0;
    }

    // 1. Dem tan suat cac ky tu
    
    map<char, int> freq;

    for (int i = 0; i < text.length(); i++) {
        freq[text[i]]++;
    }

    cout << "\nTan suat cac ky tu:\n";

    for (map<char, int>::iterator it = freq.begin(); it != freq.end(); ++it) {
        if (it->first == ' ')
            cout << "[SPACE] : " << it->second << endl;
        else
            cout << it->first << " : " << it->second << endl;
    }

    // 2. Tao hang doi uu tien
    
    priority_queue<Node*, vector<Node*>, Compare> pq;

    for (map<char, int>::iterator it = freq.begin(); it != freq.end(); ++it) {
        pq.push(new Node(it->first, it->second));
    }

    // 3. Xay dung cay Huffman
    
    while (pq.size() > 1) {
        Node* left = pq.top();
        pq.pop();

        Node* right = pq.top();
        pq.pop();

        Node* newNode = new Node(left, right);
        pq.push(newNode);
    }

    Node* root = pq.top();

    // 4. Tao ma Huffman
    
    map<char, string> huffmanCode;

    taoMa(root, "", huffmanCode);

    cout << "\nMa Huffman:\n";

    for (map<char, string>::iterator it = huffmanCode.begin();
         it != huffmanCode.end(); ++it) {

        if (it->first == ' ')
            cout << "[SPACE] : " << it->second << endl;
        else
            cout << it->first << " : " << it->second << endl;
    }

    // 5. In cay Huffman
    
    cout << "\nCay Huffman:\n";
    inCay(root);

    // 6. Ma hoa van ban
    
    string encodedText = "";

    for (int i = 0; i < text.length(); i++) {
        encodedText += huffmanCode[text[i]];
    }

    cout << "\nVan ban ban dau:\n";
    cout << text << endl;

    cout << "\nVan ban sau khi ma hoa:\n";
    cout << encodedText << endl;

    // 7. Tinh so bit
    
    int bitBanDau = text.length() * 8;
    int bitSauKhiMaHoa = encodedText.length();

    cout << "\nSo bit ban dau: " << bitBanDau;
    cout << "\nSo bit sau khi ma hoa: " << bitSauKhiMaHoa;

    if (bitBanDau > 0) {
        double tiLe = (double)bitSauKhiMaHoa / bitBanDau * 100;

        cout << "\nTi le kich thuoc sau ma hoa: "
             << tiLe << "%";
    }

    return 0;
}