#include <iostream>
#include <string>
#include <random>
#include <ctime>
using namespace std;

random_device rd;
mt19937 gen(rd());
int random(int low, int high)
{
    uniform_int_distribution<> dist(low, high);
    return dist(gen);
}

class Date {
private:
    int day = 0, month = 0, year = 0;
public:
    Date() {
        day = random(1, 31);
        month = random(1, 12);
        year = random(1950, 2023);
    };

    friend ostream& operator << (ostream& stream, const Date& p) {
        stream << p.day << "." << p.month << "." << p.year;
        return stream;
    }
    friend bool operator < (const Date dt1, const Date dt2)
    {
        if (dt1.year < dt2.year)return true;
        else {
            if (dt1.year == dt2.year) {
                if (dt1.month < dt2.month)return true;
                else {
                    if (dt1.month == dt2.month) {
                        return dt1.day < dt2.day;
                    }
                    else return false;
                }
            }
            else return false;
        }
    }
    friend bool operator > (const Date dt1, const Date& dt2)
    {
        if (dt1.year > dt2.year)return true;
        else {
            if (dt1.year == dt2.year) {
                if (dt1.month > dt2.month)return true;
                else {
                    if (dt1.month == dt2.month) {
                        return dt1.day > dt2.day;
                    }
                    else return false;
                }
            }
            else return false;
        }
    }
};

class Person {
private:
    string fullName;
    Date birthDate;
    int brainVolume;
public:
    Person() {
        fullName = generate_fullName();
        brainVolume = random(1000, 1700);
    }

    Person(const string& name, const Date& date, int volume) : fullName(name), birthDate(date), brainVolume(volume) {}

    string generate_fullName() {
        string s = "qazwsxedcrfvtgbyhnujmikolp";
        string new_str = "";
        for (int i = 0; i < 5; i++) {
            new_str += s[random(0, 25)];
        }
        return new_str;
    }

    void print() {
        cout << fullName << ' ' << birthDate << ' ' << brainVolume << endl;
    }
    string getfullName() {
        return fullName;
    }
    Date getBirthDate() {
        return birthDate;
    }
    int getBrainVolume() {
        return brainVolume;
    }
};

class Container {
private:
    Person* records;
    int count;
    int capacity;

public:
    Container() {
        count = 100;
        records = new Person[count];
    }

    void addRecord(const string& fullName, const Date& birthDate, int brainVolume) {

        Person* new_records = new Person[count + 1];
        for (int i = 0; i < count; i++) {
            new_records[i] = records[i];
        }
        Person newP(fullName, birthDate, brainVolume);
        new_records[count] = newP;
        count++;
        records = new_records;

        cout << "Запись добавлена" << endl;
    }

    void printAllRecords() {
        for (int i = 0; i < count; i++) {
            records[i].print();
        }
    }

    void swap(int i, int j) {
        Person copy = records[i];
        records[i] = records[j];
        records[j] = copy;
    }

    //Bubble
    void BubbleSort() {
        int choose = 0,n_swap = 0,n_match = 0;
        cout << "Выберите по каким данным сортировать записи" << endl;
        cout << "[1] ФИО." << endl;
        cout << "[2] Дата." << endl;
        cout << "[3] Объем мозга." << endl;
        while (choose < 1 || choose>3) {
            cin >> choose;
        }
        double start_time = clock(); // начальное время
        for (int i = 0; i + 1 < count; ++i) {
            for (int j = 0; j + 1 < count - i; ++j) {
                n_match++;
                if (choose == 1) {
                    if (records[j + 1].getfullName() < records[j].getfullName())
                    {
                        swap(j, j + 1);
                        n_swap++;
                    }
                }
                if (choose == 2) {
                    if (records[j + 1].getBirthDate() < records[j].getBirthDate()) 
                    {
                        swap(j, j + 1);
                        n_swap++;
                    }
                }
                if (choose == 3) {
                    if (records[j + 1].getBrainVolume() < records[j].getBrainVolume())\
                    {
                        swap(j, j + 1);
                        n_swap++;
                    }
                }
            }
        }
        double end_time = clock(); // конечное время
        double seconds = (double)(end_time - start_time) / CLOCKS_PER_SEC; // искомое время
        cout << "Количество сравнений: " << n_match <<endl;
        cout << "Количество изменений: " << n_swap << endl;
        cout <<"Время: " << seconds << endl;
    }

    //Insert
    void InsertionSort() {
        int choose = 0, n_swap = 0, n_match = 0;
        cout << "Выберите по каким данным сортировать записи" << endl;
        cout << "[1] ФИО." << endl;
        cout << "[2] Дата." << endl;
        cout << "[3] Объем мозга." << endl;
        while (choose < 1 || choose>3) {
            cin >> choose;
        }
        double start_time = clock(); // начальное время
        if (choose == 1) {
            for (int i = 1; i < count; i++) {
                string x = records[i].getfullName();
                int j = i;
                while (j > 0 && records[j - 1].getfullName() > x) {
                    n_match++;
                    n_swap++;
                    records[j] = records[j - 1];
                    --j;
                }
                records[j] = records[i];
                n_swap++;
            }
        }
        if (choose == 2) {
            for (int i = 1; i < count; i++) {
                Date x = records[i].getBirthDate();
                int j = i;
                while (j > 0 && records[j - 1].getBirthDate() > x) {
                    n_match++;
                    n_swap++;
                    records[j] = records[j - 1];
                    --j;
                }
                records[j] = records[i];
                n_swap++;
            }
        }
        if (choose == 3) {
            for (int i = 1; i < count; ++i) {
                int x = records[i].getBrainVolume();
                int j = i;
                while (j > 0 && records[j - 1].getBrainVolume() > x) {
                    n_match++;
                    n_swap++;
                    records[j] = records[j - 1];
                    --j;
                }
                records[j] = records[i];
                n_swap++;
            }
        }
        double end_time = clock(); // конечное время
        double seconds = (double)(end_time - start_time) / CLOCKS_PER_SEC; // искомое время
        cout << "Количество сравнений: " << n_match << endl;
        cout << "Количество изменений: " << n_swap << endl;
        cout << "Время: " << seconds << endl;
    }

    //Shake
    void ShakerSort() {
        int choose = 0, n_swap = 0, n_match = 0;
        cout << "Выберите по каким данным сортировать записи" << endl;
        cout << "[1] ФИО." << endl;
        cout << "[2] Дата." << endl;
        cout << "[3] Объем мозга." << endl;
        while (choose < 1 || choose>3) {
            cin >> choose;
        }
        double start_time = clock(); // начальное время
        if (choose == 1) {
            int left = 0;
            int right = count - 1;
            while (left <= right) {
                for (int i = right; i > left; --i) {
                    n_match++;
                    if (records[i - 1].getfullName() > records[i].getfullName()) {
                        swap(i - 1, i);
                        n_swap++;
                    }
                }
                ++left;
                for (int i = left; i < right; ++i) {
                    n_match++;
                    if (records[i].getfullName() > records[i + 1].getfullName()) {
                        swap(i, i + 1);
                        n_swap++;
                    }
                }
                --right;
            }
        }
        if (choose == 2) {
            int left = 0;
            int right = count - 1;
            while (left <= right) {
                for (int i = right; i > left; --i) {
                    n_match++;
                    if (records[i - 1].getBirthDate() > records[i].getBirthDate()) {
                        swap(i - 1, i);
                        n_swap++;
                    }
                }
                ++left;
                for (int i = left; i < right; ++i) {
                    n_match++;
                    if (records[i].getBirthDate() > records[i + 1].getBirthDate()) {
                        swap(i, i + 1);
                        n_swap++;
                    }
                }
                --right;
            }
        }
        if (choose == 3) {
            int left = 0;
            int right = count - 1;
            while (left <= right) {
                for (int i = right; i > left; --i) {
                    n_match++;
                    if (records[i - 1].getBrainVolume() > records[i].getBrainVolume()) {
                        swap(i - 1, i);
                        n_swap++;
                    }
                }
                ++left;
                for (int i = left; i < right; ++i) {
                    n_match++;
                    if (records[i].getfullName() > records[i + 1].getfullName()) {
                        swap(i, i + 1);
                        n_swap++;
                    }
                }
                --right;
            }
        }
        double end_time = clock(); // конечное время
        double seconds = (double)(end_time - start_time) / CLOCKS_PER_SEC; // искомое время
        cout << "Количество сравнений: " << n_match << endl;
        cout << "Количество изменений: " << n_swap << endl;
        cout << "Время: " << seconds << endl;

    }

    //QuichStart

    void QuickSortImpl(int choose, int l, int r) {
        if (choose == 1) {
            if (l < r) {
                string x = records[r].getfullName();
                int less = l;
                for (int i = l; i < r; ++i) {
                    if (records[i].getfullName() <= x) {
                        swap(i, less);
                        ++less;
                    }
                }
                swap(less, r);
                int q = less;
                QuickSortImpl(choose, l, q - 1);
                QuickSortImpl(choose, q + 1, r);
            }
        }
        if (choose == 2) {
            if (l < r) {
                Date x = records[r].getBirthDate();
                int less = l;
                for (int i = l; i < r; ++i) {
                    if (x > records[i].getBirthDate()) {
                        swap(i, less);
                        ++less;
                    }
                }
                swap(less, r);
                int q = less;
                QuickSortImpl(choose, l, q - 1);
                QuickSortImpl(choose, q + 1, r);
            }
        }
        if (choose == 3) {
            if (l < r) {
                int x = records[r].getBrainVolume();
                int less = l;
                for (int i = l; i < r; ++i) {
                    if (records[i].getBrainVolume() <= x) {
                        swap(i, less);
                        ++less;
                    }
                }
                swap(less, r);
                int q = less;
                QuickSortImpl(choose, l, q - 1);
                QuickSortImpl(choose, q + 1, r);
            }
        }

    }

    void QuickSort(vector<int>& values) {
        if (count > 0) {
            int choose = 0;
            cout << "Выберите по каким данным сортировать записи" << endl;
            cout << "[1] ФИО." << endl;
            cout << "[2] Дата." << endl;
            cout << "[3] Объем мозга." << endl;
            while (choose < 1 || choose>3) {
                cin >> choose;
            }
            QuickSortImpl(choose, 0, values.size() - 1);
        }

    }
    //QuickEnd

    //Gnome
    void gnomeSort() {
        int choose = 0, n_swap = 0, n_match = 0;
        double start_time = clock(); // начальное время
        cout << "Выберите по каким данным сортировать записи" << endl;
        cout << "[1] ФИО." << endl;
        cout << "[2] Дата." << endl;
        cout << "[3] Объем мозга." << endl;
        while (choose < 1 || choose>3) {
            cin >> choose;
        }
        
        if (choose == 1) {
            int n = count;
            int index = 0; 
            while (index < n) {
                if (index == 0) index++;
                n_match++;
                if (records[index].getfullName() >= records[index - 1].getfullName())
                    index++;
                else {
                    swap(index, index - 1);
                    n_swap++;
                    index--;
                }
            }
        }
        if (choose == 2) {
            int n = count;
            int index = 0;  while (index < n) {
                if (index == 0)
                    index++;
                n_match++;
                if (records[index - 1].getBirthDate() < records[index].getBirthDate())
                    index++;
                else {
                    swap(index, index - 1);
                    n_swap++;
                    index--;
                }
            }
        }
        if (choose == 3) {
            int n = count;
            int index = 0;  while (index < n) {
                if (index == 0)
                    index++;
                n_match++;
                if (records[index].getBrainVolume() >= records[index - 1].getBrainVolume())
                    index++;
                else {
                    swap(index, index - 1);
                    n_swap++;
                    index--;
                }
            }
        }
        double end_time = clock(); // конечное время
        double seconds = (double)(end_time - start_time) / CLOCKS_PER_SEC; // искомое время
        cout << "Количество сравнений: " << n_match << endl;
        cout << "Количество изменений: " << n_swap << endl;
        cout << "Время: " << seconds << endl;

    }

    //Shell
    void shellSort()
    {
        int choose = 0, n_swap = 0, n_match = 0;
        double start_time = clock(); // начальное время
        cout << "Выберите по каким данным сортировать записи" << endl;
        cout << "[1] ФИО." << endl;
        cout << "[2] Дата." << endl;
        cout << "[3] Объем мозга." << endl;
        while (choose < 1 || choose>3) {
            cin >> choose;
        }

        if (choose == 1) {
            for (int step = count / 2; step > 0; step /= 2)
            {
                for (int i = step; i < count; i += 1)
                {
                    int j = i;
                    
                    while (j >= step && records[j - step].getfullName() > records[i].getfullName())
                    {
                        n_match++;
                        swap(j, j - step);
                        n_swap++;
                        j -= step;
                    }
                }
            }
        }
        if (choose == 2) {
            for (int step = count / 2; step > 0; step /= 2)
            {
                for (int i = step; i < count; i += 1)
                {
                    int j = i;
                    while (j >= step && records[j - step].getBirthDate() > records[i].getBirthDate())
                    {
                        n_match++;
                        swap(j, j - step);
                        n_swap++;
                        j -= step;
                    }
                }
            }
        }
        if (choose == 3) {
            for (int step = count / 2; step > 0; step /= 2)
            {
                for (int i = step; i < count; i += 1)
                {
                    int j = i;
                    while (j >= step && records[j - step].getBrainVolume() > records[i].getBrainVolume())
                    {
                        n_match++;
                        swap(j, j - step);
                        n_swap++;
                        j -= step;
                    }
                }
            }
        }
        double end_time = clock(); // конечное время
        double seconds = (double)(end_time - start_time) / CLOCKS_PER_SEC; // искомое время
        cout << "Количество сравнений: " << n_match << endl;
        cout << "Количество изменений: " << n_swap << endl;
        cout << "Время: " << seconds << endl;

    }

    //MergeStart...GitHub?
    void merge_sort() {
        int choose = 0;
        cout << "Выберите по каким данным сортировать записи" << endl;
        cout << "[1] ФИО." << endl;
        cout << "[2] Дата." << endl;
        cout << "[3] Объем мозга." << endl;
        while (choose < 1 || choose>3) {
            cin >> choose;
        }
        mergeSort(records, count, choose);
    }

    void mergeSort(Person* data, int lenD, int choose)
    {
        if (lenD > 1) {
            int middle = lenD / 2;
            int rem = lenD - middle;
            Person* L = new Person[middle];
            Person* R = new Person[rem];
            for (int i = 0; i < lenD; i++) {
                if (i < middle) {
                    L[i] = data[i];
                }
                else {
                    R[i - middle] = data[i];
                }
            }
            mergeSort(L, middle, choose);
            mergeSort(R, rem, choose);
            merge(data, lenD, L, middle, R, rem, choose);
        }
    }

    void merge(Person* merged, int lenD, Person* L, int lenL, Person* R, int lenR, int choose) {
        if (choose == 1) {
            int i = 0;
            int j = 0;
            while (i < lenL || j < lenR) {
                if (i < lenL & j < lenR) {
                    if (L[i].getfullName() <= R[j].getfullName()) {
                        merged[i + j] = L[i];
                        i++;
                    }
                    else {
                        merged[i + j] = R[j];
                        j++;
                    }
                }
                else if (i < lenL) {
                    merged[i + j] = L[i];
                    i++;
                }
                else if (j < lenR) {
                    merged[i + j] = R[j];
                    j++;
                }
            }
        }
        if (choose == 2) {
            int i = 0;
            int j = 0;
            while (i < lenL || j < lenR) {
                if (i < lenL & j < lenR) {
                    if (!(L[i].getBirthDate() > R[j].getBirthDate())) {
                        merged[i + j] = L[i];
                        i++;
                    }
                    else {
                        merged[i + j] = R[j];
                        j++;
                    }
                }
                else if (i < lenL) {
                    merged[i + j] = L[i];
                    i++;
                }
                else if (j < lenR) {
                    merged[i + j] = R[j];
                    j++;
                }
            }
        }
        if (choose == 3) {
            int i = 0;
            int j = 0;
            while (i < lenL || j < lenR) {
                if (i < lenL & j < lenR) {
                    if (L[i].getBrainVolume() <= R[j].getBrainVolume()) {
                        merged[i + j] = L[i];
                        i++;
                    }
                    else {
                        merged[i + j] = R[j];
                        j++;
                    }
                }
                else if (i < lenL) {
                    merged[i + j] = L[i];
                    i++;
                }
                else if (j < lenR) {
                    merged[i + j] = R[j];
                    j++;
                }
            }
        }

    }
    //MergeEnd

    //PyramidStart
    void pyramid_sort() {
        int choose = 0;
        cout << "Выберите по каким данным сортировать записи" << endl;
        cout << "[1] ФИО." << endl;
        cout << "[2] Дата." << endl;
        cout << "[3] Объем мозга." << endl;
        while (choose < 1 || choose>3) {
            cin >> choose;
        }
        heapSort(records, count, choose);
    }

    void heapify(Person* arr, int n, int i, int choose) {
        if (choose == 1) {
            int largest = i;
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            if (left < n && arr[left].getfullName() > arr[largest].getfullName()) {
                largest = left;
            }
            if (right < n && arr[right].getfullName() > arr[largest].getfullName()) {
                largest = right;
            }
            if (largest != i) {
                swap(i, largest);
                heapify(arr, n, largest, choose);
            }
        }
        if (choose == 2) {
            int largest = i;
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            if (left < n && arr[left].getBirthDate() > arr[largest].getBirthDate()) {
                largest = left;
            }
            if (right < n && arr[right].getBirthDate() > arr[largest].getBirthDate()) {
                largest = right;
            }
            if (largest != i) {
                swap(i, largest);
                heapify(arr, n, largest, choose);
            }
        }
        if (choose == 3) {
            int largest = i;
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            if (left < n && arr[left].getBrainVolume() > arr[largest].getBrainVolume()) {
                largest = left;
            }
            if (right < n && arr[right].getBrainVolume() > arr[largest].getBrainVolume()) {
                largest = right;
            }
            if (largest != i) {
                swap(i, largest);
                heapify(arr, n, largest, choose);
            }
        }

    }
    void heapSort(Person* arr, int n, int choose) {
        for (int i = n / 2 - 1; i >= 0; i--) {
            heapify(arr, n, i, choose);
        }
        for (int i = n - 1; i > 0; i--) {
            std::swap(arr[0], arr[i]);
            heapify(arr, i, 0, choose);
        }
    }
    //PyramidEnd

    //Comb
    void CombSort() {
        const double factor = 1.247; // Фактор уменьшения
        int step = count - 1;
        int choose = 0, n_swap = 0, n_match = 0;
        double start_time = clock(); // начальное время
        cout << "Выберите по каким данным сортировать записи" << endl;
        cout << "[1] ФИО." << endl;
        cout << "[2] Дата." << endl;
        cout << "[3] Объем мозга." << endl;
        while (choose < 1 || choose>3) {
            cin >> choose;
        }
        if (choose == 1) {
            while (step >= 1) {
                for (int i = 0; i + step < count; ++i) {
                    n_match++;
                    if (records[i].getfullName() > records[i + step].getfullName()) {
                        swap(i, i + step);
                        n_swap++;
                    }
                }
                step /= factor;
            }
            for (int idx_i = 0; idx_i + 1 < count; ++idx_i) {
                for (int idx_j = 0; idx_j + 1 < count - idx_i; ++idx_j) {
                    n_match++;
                    if (records[idx_j + 1].getfullName() < records[idx_j].getfullName()) {
                        swap(idx_j, idx_j + 1);
                        n_swap++;
                    }
                }
            }
        }
        if (choose == 2) {
            while (step >= 1) {
                for (int i = 0; i + step < count; ++i) {
                    n_match++;
                    if (records[i].getBirthDate() > records[i + step].getBirthDate()) {
                        swap(i, i + step);
                        n_swap++;
                    }
                }
                step /= factor;
            }
            for (int idx_i = 0; idx_i + 1 < count; ++idx_i) {
                for (int idx_j = 0; idx_j + 1 < count - idx_i; ++idx_j) {
                    n_match++;
                    if (records[idx_j + 1].getBirthDate() < records[idx_j].getBirthDate()) {
                        swap(idx_j, idx_j + 1);
                        n_swap++;
                    }
                }
            }
        }
        if (choose == 3) {
            while (step >= 1) {
                for (int i = 0; i + step < count; ++i) {
                    n_match++;
                    if (records[i].getBrainVolume() > records[i + step].getBrainVolume()) {
                        swap(i, i + step);
                        n_swap++;
                    }
                }
                step /= factor;
            }
            for (int idx_i = 0; idx_i + 1 < count; ++idx_i) {
                for (int idx_j = 0; idx_j + 1 < count - idx_i; ++idx_j) {
                    n_match++;
                    if (records[idx_j + 1].getBrainVolume() < records[idx_j].getBrainVolume()) {
                        swap(idx_j,idx_j + 1);
                        n_swap++;
                    }
                }
            }
        }
        double end_time = clock(); // конечное время
        double seconds = (double)(end_time - start_time) / CLOCKS_PER_SEC; // искомое время
        cout << "Количество сравнений: " << n_match << endl;
        cout << "Количество изменений: " << n_swap << endl;
        cout << "Время: " << seconds << endl;
    }
};

int main() {
    setlocale(LC_ALL, "ru");
    Date dr;
    Container FI202;
    FI202.addRecord("Dima", dana, 1800);
    FI202.addRecord("Nikita", dana, 1800);
    FI202.addRecord("Masha", dana, 1800);
    FI202.printAllRecords();
    cout << "===============================" << endl;
    FI202.BubbleSort();
    return 0;
}