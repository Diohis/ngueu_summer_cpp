#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <string>

using namespace std;
struct Point {
    int index; //номер точки для удобства
    int* in; //Массив индексов точек которые ведут в эту
    int n_in; //Количество этих точек
    int* out;//Массив индексов точек в которые можно пойти из текущей
    int n_out; //Количество этих точек
    int* path; //Путь до этой точки из заданной (для алгоритма используется)
    int n_path; //Длина пути
    int weight_path; //Вес пути (также для алгоритма) (Для самолетов - расстояние)
    int time; //Время пути из заданной дальше точки
    int price; //Cтоимость пути из заданной дальше точки
    string name_city; //Название города

    Point() {
        in = new int[1];
        n_in = 0;
        out = new int[1];
        n_out = 0;
        path = new int[1];
        n_path = 0;
        weight_path = INT_MAX;
    }
    Point(int index, int* in, int n_in, int* out, int n_out, int* path, int n_path,int time,int price,string name_city) {
        this->index = index;
        this->in = in;
        this->n_in = n_in;
        this->out = out,
            this->n_out = n_out;
        this->path = path;
        this->n_path = n_path;
        this->price = price;
        this->time = time;
        this->name_city = name_city;
    }
    void add_in(int point) {
        int* new_in = new int[n_in + 1];
        for (int i = 0; i < n_in; i++) {
            new_in[i] = in[i];
        }
        new_in[n_in] = point;
        in = new_in;
        n_in++;
    }
    void add_out(int point) {
        int* new_out = new int[n_out + 1];
        for (int i = 0; i < n_out; i++) {
            new_out[i] = out[i];
        }
        new_out[n_out] = point;
        out = new_out;
        n_out++;
    }
    void add_path(int* active_path, int n_active_path, int index) {
        int* new_path = new int[n_active_path + 1];
        for (int i = 0; i < n_active_path; i++) {
            new_path[i] = active_path[i];
        }
        new_path[n_active_path] = index;
        path = new_path;
        n_path = n_active_path + 1;
    }
};

struct Dei {
    Point** used;
    int n_used;
    Dei(Point** used,int n_used){
        this->used = used;
        this->n_used = n_used;
    }
};

struct Rib {
    Point* start;
    Point* end;
    int price;
    int dist;
    int time;
    int weight;
    Rib() {
        start = nullptr;
        end = nullptr;
        price = 0;
        weight = 0;
        dist = 0;
        time= 0;
    }
    Rib(Point* start, Point* end, int dist, int price,int time) {
        this->start = start;
        this->end = end;
        this->dist = dist;
        this->price = price;
        this->time = time;
    }
};

class Graph {
private:
    Point* points;
    int n_points;
    Rib* vertex;
    int n_vertex;
public:
    Graph() {
        points = nullptr;
        vertex = nullptr;
        n_points = 0;
        n_vertex = 0;
    }
    void create() {
        cout << "Введите количество городов: "; cin >> n_points;
        points = new Point[n_points];
        for (int i = 0; i < n_points; i++) {
            int k;
            string name;
            cout << "Введите название города: "; cin >> name;
            points[i].name_city = name;
            points[i].index = i;
            points[i].path[0] = i;
            points[i].n_path++;
            cout << "Введите количество рейсов из города " << name<<" (" << i << ")"<<": "; cin >> k;
            for (int j = 0; j < k; j++) {
                int index;
                cout << "Введите индекс города к которому идет рейс: "; cin >> index;

                points[i].add_out(points[index].index);
                points[index].add_in(points[i].index);

                int dist, price = 0,time = 0;
                cout << "Введите расстояние между городами: "; cin >> dist;
                cout<<"Введите стоимость перелета между этими городами: ";cin>>price;
                cout << "Укажите длительность перелета между этими городами (в минутах): "; cin >> time;
                add_vertex(&points[i], &points[index], dist, price,time);
            }
        }
    }


    void add_vertex(Point* start, Point* end, int dist, int price,int time) {
        Rib* new_vertex = new Rib[n_vertex + 1];
        for (int i = 0; i < n_vertex; i++) {
            new_vertex[i] = vertex[i];
        }
        new_vertex[n_vertex] = Rib(start, end, dist, price,time);
        vertex = new_vertex;
        n_vertex++;
    }



    void print_points() {
        for (int i = 0; i < n_points; i++) {
            cout << points[i].index << " ";
        }
        cout << endl;
    }



    void print_vertex() {
        for (int i = 0; i < n_vertex; i++) {
            cout << vertex[i].start->name_city <<" ("<< vertex[i].start->index<<")" << " -> " << vertex[i].end->name_city<<" (" <<vertex[i].end->index <<")" << " ";
            //cout<<vertex[i].start<<" -> "<<vertex[i].end<<endl;
        }
    }



    int* add_in_array(int* array, int n, int k) {
        int* new_array = new int[n + 1];
        for (int i = 0; i < n; i++) {
            new_array[i] = array[i];
        }
        new_array[n] = k;
        return new_array;
    }
    Point** add_in_used(Point** used, int n, Point* point) {
        Point** new_used = new Point*[n + 1];
        for (int i = 0; i < n; i++) {
            new_used[i] = used[i];
        }
        new_used[n] = point;
        return new_used;
    }


    Dei start_Dijkstr(int start, int mode) {
        /*int start, end;
        cout << "Введите начальную точку: ";
        cin >> start;
        cout << "Введите конечную точку: ";
        cin >> end;*/
        if (mode == 1) {
            for (int i = 0; i < n_vertex; i++) {
                vertex[i].weight == vertex[i].dist;
            }
        }
        else if (mode == 2) {
            for (int i = 0; i < n_vertex; i++) {
                vertex[i].weight == vertex[i].time;
            }
        }
        else if (mode == 3) {
            for (int i = 0; i < n_vertex; i++) {
                vertex[i].weight == vertex[i].price;
            }
        }
        points[start].weight_path = 0;
        Point** used = new Point*[n_points];
        int n_used = 0;
        return Dijkstr(used, n_used, &points[start]);
    }



    Point* min_weight(Point** used, int n_used) {
        Point* min_point=nullptr;
        int min_weight = INT_MAX;
        for (int i = 0; i < n_points; i++) {
            bool use = false;
            for (int j = 0; j < n_used; j++) {
                if (points[i].index == used[j]->index)use = true;
            }
            if (use)continue;
            if (points[i].weight_path < min_weight) {
                min_point = &points[i];
                min_weight = points[i].weight_path;
            }
        }
        return min_point;
    }



    Dei Dijkstr(Point** used, int n_used, Point* active_point) {
        for (int i = 0; i < n_vertex; i++) {
            if (vertex[i].start->index == active_point->index) {
                if (vertex[i].weight + active_point->weight_path < vertex[i].end->weight_path) {
                    vertex[i].end->weight_path = vertex[i].weight + active_point->weight_path;
                    vertex[i].end->add_path(active_point->path, active_point->n_path, vertex[i].end->index);
                }
            }
        }
        used = add_in_used(used, n_used, active_point);
        n_used++;
        if (n_used == n_points) {
            //finish_Dijkstr(used, n_used);
            return Dei(used,n_used);
        }
        Point* next_point = min_weight(used, n_used);
        Dijkstr(used, n_used, next_point);
    }
    void zadanie_1() {
        int choice=0, index;
        cout << "Введите индекс города, из которого планируете лететь: "; cin >> index;
        cout << "Введите по какому признаку минимизорать рейсы: 1 - время;  2 - стоимость ";
        while (choice < 1 || choice>2) { cin >> choice; }
        cout << "Список городов достпуных для перелета" << endl;
        Dei list = start_Dijkstr(index, choice);
        string mode;
        Point* min_city;
        int min_value = INT_MAX;
        if (choice == 1) {
            for (int i = 0; i < list.n_used; i++) {
                if (list.used[i]->n_path > 1) {
                    if (list.used[i]->weight_path < min_value) {
                        min_value = list.used[i]->weight_path;
                        min_city = list.used[i];
                    }
                }
            }
            mode = "времени";     
        }
        if (choice == 2) {;
            for (int i = 0; i < list.n_used; i++) {
                if (list.used[i]->n_path > 1) {
                    if (list.used[i]->weight_path < min_value) {
                        min_value = list.used[i]->weight_path;
                        min_city = list.used[i];
                    }
                }
            }
            mode = "стоимости";
        }
        cout << "Ближайший несовместный город по "<<mode<<": " << min_city->name_city << endl;;
    }
    void zadanie_2() {
        int sum,index;
        cout << "Введите индекс города, из которого планируете лететь: "; cin >> index;
        cout << "Введите сумму денег, которая у вас имеется для перелета: "; cin >> sum;
        cout << "Список городов достпуных для перелета" << endl;
        Dei list = start_Dijkstr(index,3);
        for (int i = 0; i < list.n_used; i++) {
            if (list.used[i]->price <= sum)cout << "[-]" << list.used[i]->name_city << endl;
        }
    }
    void zadanie_3() {
        int time, index;
        cout << "Введите индекс города, из которого планируете лететь: "; cin >> index;
        cout << "Введите время, которое у вас имеется для перелета: "; cin >> time;
        cout << "Список городов достпуных для перелета" << endl;
        Dei list = start_Dijkstr(index,2);
        for (int i = 0; i < list.n_used; i++) {
            if (list.used[i]->time <= time)cout << "[-]" << list.used[i]->name_city << endl;
        }
    }
    void zadanie_4() {
        int start,end;
        cout << "Введите индекс города, из которого планируете лететь: "; cin >> start;
        cout << "Введите индекс города, в который планируете лететь: "; cin >> end;
        Dei list = start_Dijkstr(start,1);
        for (int i = 0; i < list.n_used; i++) {
            if (list.used[i]->index == end) {
                if (list.used[i]->n_path <= 4)
                {
                    cout << "Можно перелететь за 2-3 пересадки" << endl;
                    return;
                }
            }
        }
        cout << "Нельзя перелететь за 2-3 пересадки" << endl;
    }
    void zadanie_5() {
        int start, end;
        cout << "Введите индекс города, из которого планируете лететь: "; cin >> start;
        Dei list = start_Dijkstr(start,1);
        int dist = -1;
        for (int i = 0; i < list.n_used; i++) {
            if (list.used[i]->weight_path >dist ) {
                dist = list.used[i]->weight_path;
            }
        }
        cout << "Максимальное расстрояние на которое можно улететь: " << dist;
    }
};

int main()
{
    setlocale(LC_ALL, "ru");
    Graph test;
    test.create();
    test.print_points();
    test.print_vertex();
    test.start_Dijkstr(0,2);
    return 0;
}
