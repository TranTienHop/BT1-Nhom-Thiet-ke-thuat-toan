#include <iostream>
#include <string>
using namespace std;

struct GiaoDich
{
    string maGD;
    string thoiGian;
    double soTien;
};

int doiNgay(string s)
{
    int ngay = (s[0] - '0') * 10 + (s[1] - '0');
    int thang = (s[3] - '0') * 10 + (s[4] - '0');
    int nam = (s[6] - '0') * 1000 + (s[7] - '0') * 100
            + (s[8] - '0') * 10 + (s[9] - '0');

    return nam * 10000 + thang * 100 + ngay;
}

void merge(GiaoDich a[], int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    GiaoDich* L = new GiaoDich[n1];
    GiaoDich* R = new GiaoDich[n2];

    for (int i = 0; i < n1; i++)
        L[i] = a[left + i];

    for (int i = 0; i < n2; i++)
        R[i] = a[mid + 1 + i];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2)
    {
        if (doiNgay(L[i].thoiGian) <= doiNgay(R[j].thoiGian))
        {
            a[k] = L[i];
            i++;
        }
        else
        {
            a[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        a[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        a[k] = R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
}

void mergeSort(GiaoDich a[], int left, int right)
{
    if (left < right)
    {
        int mid = (left + right) / 2;

        mergeSort(a, left, mid);
        mergeSort(a, mid + 1, right);

        merge(a, left, mid, right);
    }
}

void xuat(GiaoDich a[], int n)
{
    cout << "\nDanh sach giao dich sau khi sap xep:\n";

    for (int i = 0; i < n; i++)
    {
        cout << "Ma GD: " << a[i].maGD
             << " | Thoi gian giao dich: " << a[i].thoiGian
             << " | So tien: " << a[i].soTien << endl;
    }
}

int main()
{
    int n;

    cout << "Nhap so luong giao dich: ";
    cin >> n;

    GiaoDich* a = new GiaoDich[n];

    for (int i = 0; i < n; i++)
    {
        cout << "\nGiao dich " << i + 1 << ":\n";

        cout << "Ma giao dich: ";
        cin >> a[i].maGD;

        cout << "Ngay-Thang-Nam: ";
        cin >> a[i].thoiGian;

        cout << "So tien: ";
        cin >> a[i].soTien;
    }

    mergeSort(a, 0, n - 1);

    xuat(a, n);

    delete[] a;

    return 0;
}