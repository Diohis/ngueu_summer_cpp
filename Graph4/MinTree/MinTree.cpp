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
    int p; //индекс предка

    Point() {
        in = new int[1];
        n_in = 0;
        out = new int[1];
        n_out = 0;
        path = new int[1];
        n_path = 0;
        weight_path = INT_MAX;
    }
    Point(int index, int* in, int n_in, int* out, int n_out, int* path, int n_path, int time, int price, string name_city) {
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
    void set_p(int p) {
        this->p = p;
    }
    int get_p() {
        return p;
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
        time = 0;
    }
    Rib(Point* start, Point* end, int dist, int price, int time) {
        this->start = start;
        this->end = end;
        this->dist = dist;
        this->price = price;
        this->time = time;
        this->weight = dist;
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
            points[i].index = i;
            points[i].path[0] = i;
            points[i].n_path++;
            cout << "Введите количество рейсов из города " << "(" << i << ")" << ": "; cin >> k;
            for (int j = 0; j < k; j++) {
                int index,dist,time,price;
                cout << "Введите индекс города: "; cin >> index;
                cout << "Введите дистанцию этого рейса: "; cin >> dist;
                cout << "Введите время этого рейса: "; cin >> time;
                cout << "Введите стоимость этого рейса: "; cin >> price;
                points[i].add_out(points[index].index);
                points[index].add_in(points[i].index);

                add_vertex(&points[i], &points[index],dist,time,price);
            }
        }
    }

    struct Dei {
        Point** used;
        int n_used;
        Dei(Point** used, int n_used) {
            this->used = used;
            this->n_used = n_used;
        }
    };


    void add_vertex(Point* start, Point* end, int dist, int price, int time) {
        Rib* new_vertex = new Rib[n_vertex + 1];
        for (int i = 0; i < n_vertex; i++) {
            new_vertex[i] = vertex[i];
        }
        new_vertex[n_vertex] = Rib(start, end, dist, price, time);
        vertex = new_vertex;
        n_vertex++;
    }
    void append_vertex(Rib* rib) {
        Rib* new_vertex = new Rib[n_vertex + 1];
        for (int i = 0; i < n_vertex; i++) {
            new_vertex[i] = vertex[i];
        }
        new_vertex[n_vertex] = *rib;
        vertex = new_vertex;
        n_vertex++;
    }
    void remove_vertex() {
        Rib* new_vertex = new Rib[n_vertex - 1];
        for (int i = 0; i < n_vertex-1; i++) {
            new_vertex[i] = vertex[i];
        }
        vertex = new_vertex;
        n_vertex--;
    }
    void remove_vertex(int index) {
        Rib* new_vertex = new Rib[n_vertex - 1];
        for (int i = 0,j = 0; i < n_vertex; j++,i++) {
            if (i == index)i++;
            if (i<n_vertex)new_vertex[j] = vertex[i];
        }
        vertex = new_vertex;
        n_vertex--;
    }

    void print_points() {
        for (int i = 0; i < n_points; i++) {
            cout << points[i].index << " ";
        }
        cout << endl;
    }



    void print_vertex() {
        for (int i = 0; i < n_vertex; i++) {
            cout << "(" << vertex[i].start->index << ")" << " -> " << "(" << vertex[i].end->index << ")";
            cout << " --- " << vertex[i].weight << endl;
            //cout<<vertex[i].start<<" -> "<<vertex[i].end<<endl;
        }
    }
    Dei* start_Dijkstr(int start, int mode) {
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
        Point** used = new Point * [n_points];
        int n_used = 0;
        return Dijkstr(used, n_used, &points[start]);
    }



    Point* min_weight(Point** used, int n_used) {
        Point* min_point = nullptr;
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



    Dei* Dijkstr(Point** used, int n_used, Point* active_point) {
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
            return new Dei(used, n_used);
        }
        Point* next_point = min_weight(used, n_used);
        Dijkstr(used, n_used, next_point);
    }


    int* add_in_array(int* array, int n, int k) {
        int* new_array = new int[n + 1];
        new_array[0] = k;
        for (int i = 0; i < n; i++) {
            new_array[i + 1] = array[i];
        }

        return new_array;
    }
    int* remove_from_array(int* array, int n) {
        int* new_array = new int[n - 1];
        for (int i = 1; i < n; i++) {
            new_array[i - 1] = array[i];
        }
        return new_array;
    }
    Point** add_in_used(Point** used, int n, Point* point) {
        Point** new_used = new Point * [n + 1];
        for (int i = 0; i < n; i++) {
            new_used[i] = used[i];
        }
        new_used[n] = point;
        return new_used;
    }
    Point** add_in_points(Point** points_arr,int n,Point* new_point) {
        Point** new_points = new Point*[n + 1];
        for (int i = 0; i < n; i++) {
            new_points[i] = points_arr[i];
        }
        new_points[n] = new_point;
        return new_points;
    }
    bool in_used(Point** used, int n_used, int index) {
        for (int i = 0; i < n_used; i++) {
            if (used[i]->index == index)return true;
        }
        return false;
    }


    void color() {
        int* colors = new int[n_points];
        for (int i = 0; i < n_points; i++) {
            colors[i] = 0;
        }
        colors[0] = 1;
        int k = 0;
        int* q = new int[1];
        q[0] = k;
        int n_q = 1;
        bool IsBipartite = true;
        while (n_q > 0) {
            bool new_point = false;
            for (int i = 0; i < n_vertex; i++) {
                if (vertex[i].start->index == q[0]) {
                    if (colors[vertex[i].end->index] == 0) {
                        colors[vertex[i].end->index] = colors[vertex[i].start->index] * -1;
                        q = add_in_array(q, n_q, vertex[i].end->index);
                        n_q++;
                        new_point = true;
                        break;
                    }
                    else {
                        if (colors[vertex[i].end->index] == colors[vertex[i].start->index]) {
                            IsBipartite = false;
                        }
                    }
                }
            }
            if (!(new_point)) {
                q = remove_from_array(q, n_q);
                n_q--;
            }
        }
        for (int i = 0; i < n_points; i++) {
            cout << colors[i] << " ";
        }
        cout << boolalpha << IsBipartite;
    }

    bool find_cycle() {
        int* colors = new int[n_points];
        for (int i = 0; i < n_points; i++) {
            colors[i] = 0;
        }
        colors[0] = 1;
        int k = 0;
        int* q = new int[1];
        q[0] = k;
        int n_q = 1;
        bool IsCycle = false;
        while (n_q > 0) {
            colors[q[0]] = 1;
            bool new_point = false;
            for (int i = 0; i < n_vertex; i++) {
                if (vertex[i].start->index == q[0]) {
                    if (colors[vertex[i].end->index] == 0) {
                        colors[vertex[i].end->index] = colors[vertex[i].start->index] * -1;
                        q = add_in_array(q, n_q, vertex[i].end->index);
                        n_q++;
                        new_point = true;
                        break;
                    }
                    else {
                        if (colors[vertex[i].end->index] == 1) {
                            IsCycle = true;
                        }
                    }
                }
            }
            if (!(new_point)) {
                colors[q[0]] = 2;
                q = remove_from_array(q, n_q);
                n_q--;
            }
        }
        return IsCycle;
    }
    void swap(int i, int j) {
        Rib copy = vertex[i];
        vertex[i] = vertex[j];
        vertex[j] = copy;
    }
    void BubbleSort() {
        int count = n_vertex;
        for (int i = 0; i + 1 < count; ++i) {
            for (int j = 0; j + 1 < count - i; ++j) {
                if (vertex[j + 1].weight < vertex[j].weight)swap(j, j + 1);
            }
        }
    }
    bool in_points(Point** points_arr, int n ,int index) {
        for (int i = 0; i < n; i++) {
            if (points_arr[i]->index == index)return true;
        }
        return false;
    }
    void Kruskal() {
        BubbleSort();
        Rib** copy_vertex = new Rib*[n_vertex];
        int n_new_vertex = n_vertex;
        for (int i = 0; i < n_vertex; i++) {
            copy_vertex[i] = &vertex[i];
        }
        vertex = nullptr;
        n_vertex = 0;
        for (int i = 0; i < n_new_vertex; i++) {
            append_vertex(copy_vertex[i]);
            if (find_cycle())remove_vertex();
        }
        cout << "--------------" << endl;
        print_vertex();
    }
    void Prima(int start) {
        /*
        int start;
        int max_out = -1;
        for (int i = 0; i < n_points; i++) {
            if (points[i].n_out > max_out) {
                max_out = points[i].n_out;
                start = i;
            }
        }*/
        BubbleSort();
        Rib** copy_vertex = new Rib * [n_vertex];
        int n_new_vertex = n_vertex;

        for (int i = 0; i < n_vertex; i++) {
            copy_vertex[i] = &vertex[i];
        }
        Point start_point = points[start];
        vertex = nullptr;
        n_vertex = 0;
        Point** new_points = new Point*[0];
        int n_new_points = 0;
        new_points = add_in_points(new_points, n_new_points,&start_point);
        n_new_points++;
        while (true) {
            int min_rib=INT_MAX;
            int k_rib = 0;
            bool newv = false;
            for (int i = 0; i < n_new_points; i++) {
                for (int j = 0; j < n_new_vertex; j++) {
                    if (copy_vertex[j]->start->index == new_points[i]->index) {
                        append_vertex(copy_vertex[j]);
                        if (find_cycle())remove_vertex();
                        else {
                            if (!in_points(new_points,n_new_points,copy_vertex[j]->end->index)) {
                                new_points = add_in_points(new_points, n_new_points, copy_vertex[j]->end);
                                n_new_points++;
                            }
                            Rib** new_vertex = new Rib * [n_new_vertex - 1];
                            for (int i1 = 0, j1 = 0; i1 < n_new_vertex; j1++, i1++) {
                                if (i1 == j)i1++;
                                if (i1 < n_new_vertex)new_vertex[j1] = copy_vertex[i1];
                            }
                            copy_vertex = new_vertex;
                            n_new_vertex--;
                            newv = true;
                            break;
                        }
                    }
                }
                if (newv)break;
            }
            if(!newv)break;
        }

        
        
        cout << "--------------" << endl;
        print_vertex();
    }
    void start() {
        int choice=0,city = 0;
        cout << "По какому признаку запустить алгоритм дейкстры?" << endl;
        cout << "1 - Расстояние" << endl << "2 - Время" << endl << "3 - Стоимость" << endl;
        while (choice < 1 || choice>3) {
            cin >> choice;
        }
        cout << "Введите индекс стартового города: "; cin >> city;
        Prima(city);
        Dei* list = start_Dijkstr(city, choice);
        cout << "Результаты: N - result" << endl;
        for (int i = 0; i < list->n_used; i++) {
            cout << list->used[i]->index << " - " << list->used[i]->weight_path << endl;
        }
    }
};

int main()
{
    setlocale(LC_ALL, "ru");
    Graph test;
    test.create();
    test.print_points();
    test.print_vertex();
    test.start();
    return 0;
}
