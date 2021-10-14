// чм.1лаба.дубль2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "Rational.h"
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;
void edinica(int i, int k, int n, Rational* a, Rational* b, Rational* c, Rational* p, Rational* q, Rational* f, Rational* ft, double* ftt);
void resToOne(int k, int n, Rational* a, Rational* b, Rational* c, Rational* p, Rational* q, Rational* f);
void obnulSnizu(int i, int k, int n, Rational* a, Rational* b, Rational* c, Rational* p, Rational* q, Rational* f, Rational* ft, double* ftt);
void print(int k, int n, Rational* a, Rational* b, Rational* c, Rational* p, Rational* q, Rational* f);
void print(int n, Rational* x);
void print(int n, double* x);
double delta(int n, double* ftt);
void copy(int n, double* ft, Rational* f);
//double showDecimals(const double& x, const int& numDecimals);
void obnulSverhu(int i, int k, Rational* a, Rational* b, Rational* c, Rational* p, Rational* q, Rational* f, Rational* ft, double* ftt);
void rabota(int k, int n, Rational* a, Rational* b, Rational* c, Rational* p, Rational* q, Rational* f, Rational* ft, double* ftt, Rational* x);
void result(int n, Rational* f, Rational* x);
bool proverka(int k, Rational* a, Rational* b, Rational* c, Rational* p, Rational* q, Rational* f);
void readVector(ifstream& fin, int n, Rational* arr, bool flag) {
    if (!flag) n = n - 1;
    for (int i = 0; i < n; i++) {
        int k;
        fin >> k;
        arr[i].set(k);
    }
}
void readFromFile(ifstream& fin, int& n, int& k, Rational* a, Rational* b, Rational* c, Rational* p, Rational* q, Rational* f) {
    readVector(fin, n, a, true);
    readVector(fin, n, b, false);
    readVector(fin, n, c, false);
    readVector(fin, n, p, true);
    readVector(fin, n, q, true);
    readVector(fin, n, f, true);
}

int main() {
    int n;
    int k;
    Rational* a, * b, * c, * p, * q, * f, * x, * ft;
    double* ftt;
    double delt;
    ifstream fin("Текст.txt");
    if (!fin.is_open())
        return -1;
    else {
        fin >> n;
        fin >> k;
        a = new Rational[n];
        b = new Rational[n - 1];
        c = new Rational[n - 1];
        p = new Rational[n];
        q = new Rational[n];
        f = new Rational[n];
        ft = new Rational[n];
        ftt = new double[n];
        x = new Rational[n];
        readFromFile(fin, n, k, a, b, c, p, q, f);
        cout << proverka(k, a, b, c, p, q, f)<<endl;
        print(k, n, a, b, c, p, q, f);
        resToOne(k, n, a, b, c, p, q, ft);
        copy(n, ftt, ft);

        cout << "F~rtnl = ";
        print(n, ft);
        cout << endl;

        cout << "F~dbl = ";
        print(n, ftt);
        cout << endl;

        rabota(k, n, a, b, c, p, q, f, ft, ftt, x);

        print(k, n, a, b, c, p, q, f);
        cout << endl;

        cout << "X = ";
        print(n, x);
        cout << endl;

        cout << "F~rtnl = ";
        print(n, ft);
        cout << endl;

        cout << "F~dbl = ";
        print(n, ftt);
        cout << endl;

        delt = delta(n, ftt);
        cout << "OCENKA TOCNOSTI RESHENIA:" << endl;
        cout << " deltaX~ = " << delt << endl;
    }
    system("Pause");
    return 0;
}
double delta(int n,double* ftt) {
    double d = 0;
    for (int i = 0; i < n; i++) {
        if (abs(ftt[i] - 1) > d)
            d = abs(ftt[i] - 1);
    }
    return d;
}
void resToOne(int k, int n, Rational* a, Rational* b, Rational* c, Rational* p, Rational* q, Rational* f) {
    for (int i = 0; i < n; i++) {
        if (i == 0) {

            f[i] = a[i] + b[i];
            if (i != k - 1) {
                f[i] = f[i] + p[i];
            }

        }
        else if (i == n - 1)
        {
            f[i] = a[i] + c[i - 1];
            if (i != k + 1) {
                f[i] = f[i] + p[i];
            }
        }
        else if (i == k) {
            for (int j = 0; j < n; j++) {
                f[i] = f[i] + q[j];
            }
        }
        else if ((i == k - 1) || (i == k + 1)) {
            f[i] = a[i] + b[i] + c[i - 1];
        }

        else {
            f[i] = a[i] + b[i] + c[i - 1] + p[i];
        }
    }
}
void copy(int n, double* ft, Rational* f) {
    for (int i = 0; i < n; i++) {
        ft[i] = f[i].toDouble();
    }
}
void print(int n, Rational* x) {
    for (int i = 0; i < n; i++) {
        cout << x[i] << " ";
    }
    cout << endl;
}
void print(int n, double* x) {
    for (int i = 0; i < n; i++) {
        cout << fixed << setprecision(5) << x[i] << " ";
    }
    cout << endl;
}
void print(int k, int n, Rational* a, Rational* b, Rational* c, Rational* p, Rational* q, Rational* f) {
    for (int i = 0; i < n; i++) {
        cout << '|';
        for (int j = 0; j < n; j++) {
            if (j == k)
                cout << p[i];
            else if (i == k) {
                for (int m = 0; m < n; m++) {
                    cout << q[m];
                }
                break;
            }
            else if (i == j + 1) {
                /*if (i == n-1) {
                    cout << c[i - 1];
                }
                else*/
                cout << c[i - 1];
            }
            else if (i == j)
                cout << a[i];
            else if (i == j - 1)
                cout << b[i];
            else
                cout << "0" << "\t";
        }
        cout << '=';
        cout << f[i];
        cout << '|';
        cout << endl;
    }
    cout << "----------------------------" << endl;
    cout << endl;

}
void result(int n, Rational* f, Rational* x) {
    for (int i = 0; i < n; i++) {
        x[i] = f[i];
    }
}
//double showDecimals(const double& x, const int& numDecimals) {
//    int y = x;
//    double z = x - y;
//    double m = pow(10, numDecimals);
//    double q = z * m;
//    double r = round(q);
//
//    return static_cast<double>(y) + (1.0 / m) * r;
//}
void rabota(int k, int n, Rational* a, Rational* b, Rational* c, Rational* p, Rational* q, Rational* f, Rational* ft, double* ftt, Rational* x) {
    for (int i = 0; i < k; i++) {
        edinica(i, k, n, a, b, c, p, q, f, ft, ftt);
        obnulSnizu(i, k, n, a, b, c, p, q, f, ft, ftt);

    }
    cout << "OBLUL SNIZU DO K" << endl;
    cout << endl;
    cout << "F~rtnl = ";
    print(n, ft);
    cout << endl;
    cout << "F~dbl = ";
    print(n, ftt);
    cout << endl;

    for (int i = n - 1; i > k; i--) {
        edinica(i, k, n, a, b, c, p, q, f, ft, ftt);
        obnulSverhu(i, k, a, b, c, p, q, f, ft, ftt);

    }
    cout << "OBLUL SVERHU POSLE K" << endl;
    cout << endl;
    cout << "F~rtnl = ";
    print(n, ft);
    cout << endl;
    cout << "F~dbl = ";
    print(n, ftt);
    cout << endl;
    edinica(k, k, n, a, b, c, p, q, f, ft, ftt);
    for (int i = k; i < n - 1; i++) {

        obnulSnizu(i, k, n, a, b, c, p, q, f, ft, ftt);

    }
    cout << "OBLUL SNIZU POSLE K" << endl;
    cout << endl;
    cout << "F~rtnl = ";
    print(n, ft);
    cout << endl;
    cout << "F~dbl = ";
    print(n, ftt);
    cout << endl;
    for (int i = k; i > 0; i--) {

        obnulSverhu(i, k, a, b, c, p, q, f, ft, ftt);

    }
    result(n, f, x);
}
bool proverka(int k, Rational* a, Rational* b, Rational* c, Rational* p, Rational* q, Rational* f) {
    if ((a[k] == p[k]) && (a[k] == q[k]) && (b[k - 1] == p[k - 1]) && (b[k] == q[k + 1]) && (c[k - 1] == q[k - 1]) && (c[k] == p[k + 1]))
        return 1;
    return 0;
}
void edinica(int i, int k, int n, Rational* a, Rational* b, Rational* c, Rational* p, Rational* q, Rational* f, Rational* ft, double* ftt) {
    Rational koef(a[i]);
    a[i] = a[i] / a[i];
    p[i] = p[i] / koef;
    f[i] = f[i] / koef;
    ft[i] = ft[i] / koef;
    //ftt[i] = showDecimals(ftt[i] / showDecimals(koef.toDouble(), 5),5);
    ftt[i] = ftt[i] / koef.toDouble();
    if (i <= k) {
        b[i] = b[i] / koef;
        if (i == k) {
            q[i] = a[i];
        }
    }
    else {
        c[i - 1] = c[i - 1] / koef;
    }
}
void obnulSnizu(int i, int k, int n, Rational* a, Rational* b, Rational* c, Rational* p, Rational* q, Rational* f, Rational* ft, double* ftt) {
    if (i < k) {
        Rational koef(c[i]);
        c[i] = c[i] - koef * a[i];
        a[i + 1] = a[i + 1] - koef * b[i];
        p[i + 1] = p[i + 1] - koef * p[i];
        f[i + 1] = f[i + 1] - koef * f[i];
        ft[i + 1] = ft[i + 1] - koef * ft[i];
        //ftt[i + 1] = showDecimals(ftt[i + 1] - showDecimals(showDecimals(koef.toDouble(), 5) * ftt[i],5),5);
        ftt[i + 1] = ftt[i + 1] - koef.toDouble() * ftt[i];
        if (i != k - 1) {
            koef = q[i];
            q[i] = q[i] - koef * a[i];
            q[i + 1] = q[i + 1] - koef * b[i];
            p[k] = a[k] = q[k] = q[k] - koef * p[i];
            f[k] = f[k] - koef * f[i];
            ft[k] = ft[k] - koef * ft[i];
            //ftt[k] = showDecimals( ftt[k] - showDecimals(showDecimals(koef.toDouble(), 5) * ftt[i],5),5);
            ftt[k] = ftt[k] - koef.toDouble() * ftt[i];
        }
        else {
            q[i + 1] = p[i + 1];
            q[i] = c[i];
        }
        if (i == k - 2) {
            b[i + 1] = p[i + 1];
            c[i + 1] = q[i + 1];
        }
    }
    else if (i == k) {
        for (int j = k; j < n - 1; j++) {
            Rational koef(p[j + 1]);
            p[j + 1] = p[j + 1] - koef * p[k];
            if (j == k) {
                c[j] = p[j + 1];
            }
            f[j + 1] = f[j + 1] - koef * f[k];
            ft[j + 1] = ft[j + 1] - koef * ft[k];
            //ftt[j + 1] = showDecimals(ftt[j + 1] - showDecimals(showDecimals(koef.toDouble(), 5) * ftt[k],5),5);
            ftt[j + 1] = ftt[j + 1] - koef.toDouble() * ftt[k];
        }
    }
    else {
        Rational koef(c[i]);
        c[i] = c[i] - koef * a[i];
        f[i + 1] = f[i + 1] - koef * f[i];
        ft[i + 1] = ft[i + 1] - koef * ft[i];
        //ftt[i + 1] = showDecimals( ftt[i + 1] - showDecimals(showDecimals(koef.toDouble(), 5) * ftt[i],5),5);
        ftt[i + 1] = ftt[i + 1] - koef.toDouble() * ftt[i];
    }
}

void obnulSverhu(int i, int k, Rational* a, Rational* b, Rational* c, Rational* p, Rational* q, Rational* f, Rational* ft, double* ftt) {

    Rational koef(b[i - 1]);
    b[i - 1] = b[i - 1] - koef * a[i];
    f[i - 1] = f[i - 1] - koef * f[i];
    ft[i - 1] = ft[i - 1] - koef * ft[i];
    //ftt[i - 1] = ftt[i - 1] - showDecimals(koef.toDouble(), 5) * ftt[i];
    ftt[i - 1] = ftt[i - 1] - koef.toDouble() * ftt[i];
    if (i > k) {
        a[i - 1] = a[i - 1] - koef * c[i - 1];
        p[i - 1] = p[i - 1] - koef * p[i];
        koef = q[i];
        q[i] = q[i] - koef * a[i];
        q[i - 1] = q[i - 1] - koef * c[i - 1];

        if (i != k + 1) {
            q[k] = a[k] = p[k] = p[k] - koef * p[i];
            f[k] = f[k] - koef * f[i];
            ft[k] = ft[k] - koef * ft[i];
            //ftt[k] = ftt[k] - showDecimals(koef.toDouble(), 5) * ftt[i];
            ftt[k] = ftt[k] - koef.toDouble() * ftt[i];
        }
        if (i == k + 2) {
            c[i - 2] = p[i - 1];
            b[i - 2] = q[i - 1];
        }
    }
    else if (i == k) {
        p[i - 1] = b[i - 1];
        for (int j = k - 2; j >= 0; j--) {
            koef = p[j];
            p[j] = p[j] - koef * p[k];
            f[j] = f[j] - koef * f[k];
            ft[j] = ft[j] - koef * ft[k];
            //ftt[j] = ftt[j] - showDecimals(koef.toDouble(), 5) * ftt[k];
            ftt[j] = ftt[j] - koef.toDouble() * ftt[k];
        }
    }

}