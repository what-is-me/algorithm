class Number {
public:
    bool negative;

private:
    vector<long long> num;
    const long long _ = 1e8;
    const int lg = 8;

public:
    long long size() const { return num.size(); }
    long long& operator[](long long i) {
        return num[i];
    }

private:
    bool cmp(const Number& b) const {
        if (num.size() < b.num.size()) return 1;
        if (num.size() > b.num.size()) return 0;
        for (int i = num.size() - 1; i >= 0; i--) {
            if (num[i] < b.num[i]) return 1;
            if (num[i] > b.num[i]) return 0;
        }
        return 0;
    }
    Number add(const Number& a, const Number& b) const {
        Number ret;
        long long an = a.size(), bn = b.size(), n = max(an, bn);
        ret.num = vector<long long>(n);
        long long carrage = 0;
        for (long long i = 0; i < n; i++) {
            if (i < an) carrage += a.num[i];
            if (i < bn) carrage += b.num[i];
            ret.num[i] = carrage % _;
            carrage /= _;
        }
        if (carrage) ret.num.push_back(carrage);
        return move(ret);
    }
    void wash(long long k = 1) {
        int n = num.size();
        num.resize(n + k);
        for (int i = n; i < n + k; i++) num[i] = 0;
        n = n + k;
        long long carrage = 0;
        for (int i = 0; i < n; i++) {
            num[i] += carrage;
            if (num[i] < 0) {
                carrage = num[i] / _;
                if (num[i] % _) carrage--;
                num[i] = num[i] + carrage * _;
            } else {
                carrage = num[i] / _;
                num[i] = num[i] - carrage * _;
            }
        }
        if (carrage) num.push_back(carrage);
        while (num.back() == 0) {
            num.pop_back();
        }
    }
    Number minus(const Number& A, const Number& B) const {  //TODO
        Number ret;
        long long an = A.size(), bn = B.size(), n = max(an, bn);
        ret.num = vector<long long>(n, 0);
        if (!A.cmp(B)) {
            long long a = 0, b = 0;
            for (int i = 0; i < n; i++) {
                a = b = 0;
                if (i < an) a = A.num[i];
                if (i < bn) b = B.num[i];
                ret.num[i] = a - b;
            }
            ret.wash();
            return move(ret);
        } else {
            ret.negative = 1;
            long long a = 0, b = 0;
            for (int i = 0; i < n; i++) {
                a = b = 0;
                if (i < bn) a = B.num[i];
                if (i < an) b = A.num[i];
                ret.num[i] = a - b;
            }
            ret.wash();
            return move(ret);
        }
    }

public:
    Number() : negative(0) {}
    Number(long long a) : negative(a < 0), num(vector<long long>(1, a < 0 ? -a : a)) {}
    Number(int a) : negative(a < 0), num(vector<long long>(1, a < 0 ? -a : a)) {}
    Number(const Number& a) : negative(a.negative), num(a.num) {}
    Number(const string& a) {
        long long t = 0;
        if (a[0] == '-') {
            negative = 1;
            t = 1;
        } else {
            negative = 0;
        }
        long long tmp = 0, count = 0, tt = 1;
        for (long long i = a.size() - 1; i >= t; i--) {
            tmp = tmp + (a[i] - '0') * tt;
            count++;
            if (count == lg) {
                count = 0;
                num.push_back(tmp);
                tmp = 0;
                tt = 1;
            } else {
                tt *= 10;
            }
        }
        if (tmp) {
            num.push_back(tmp);
        }
    }
    void operator=(const Number& b) {
        negative = b.negative;
        num = b.num;
    }
    friend istream& operator>>(istream& in, Number& a) {
        string tmp;
        in >> tmp;
        a = Number(tmp);
        return in;
    }
    friend ostream& operator<<(ostream& out, Number a) {
        if (a.num.empty()) {
            out << 0;
            return out;
        }
        char buff[10];
        if (a.negative) {
            out << '-';
        }
        sprintf(buff, "%lld", a.num.back());
        out << buff;
        for (int i = a.num.size() - 2; i >= 0; i--) {
            sprintf(buff, "%08d", a.num[i]);
            out << buff;
        }
        return out;
    }
    bool operator<(const Number& b) const {
        if (negative) {
            if (b.negative) {
                return !cmp(b);
            } else {
                return 1;
            }
        } else {
            if (b.negative) {
                return 0;
            } else {
                return cmp(b);
            }
        }
    }
    bool operator>(const Number& b) const {
        return b < *this;
    }
    bool operator>=(const Number& b) const {
        return !(*this < b);
    }
    bool operator<=(const Number& b) const {
        return !(*this > b);
    }
    bool operator==(const Number& b) const {
        return (*this >= b) && (*this <= b);
    }
    Number operator+(const Number& b) const {
        const Number& a = *this;
        if (negative ^ b.negative) {
            if (negative)
                return minus(b, a);
            else
                return minus(a, b);
        } else {
            Number ret(add(a, b));
            ret.negative = negative;
            return ret;
        }
    }
    Number operator-(const Number& b) const {
        Number ret = b;
        ret.negative = !ret.negative;
        return *this + ret;
    }
    Number operator*(const Number& b) const {
        Number ret;
        ret.negative = negative ^ b.negative;
        long long an = num.size(), bn = b.size(), n = max(an, bn);
        ret.num = vector<long long>(n * 2 + 5, 0);
        for (int i = 0; i < an; i++) {
            for (int j = 0; j < bn; j++) {
                long long tmp = num[i] * b.num[j];
                ret.num[i + j] += tmp % _;
                ret.num[i + j + 1] += tmp / _;
                ret.num[i + j + 1] += ret.num[i + j] / _;
                ret.num[i + j] %= _;
            }
        }
        ret.wash();
        return ret;
    }
};