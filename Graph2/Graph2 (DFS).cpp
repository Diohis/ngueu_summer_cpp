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
    int p; //индекс предка

    Point() {
        in = new int[1];
        n_in = 0;
        out = new int[1];
        n_out = 0;
    }
    Point(int index, int* in, int n_in, int* out, int n_out) {
        this->index = index;
        this->in = in;
        this->n_in = n_in;
        this->out = out,
        this->n_out = n_out;
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
    int weight;
    int time;
    Rib() {
        start = nullptr;
        end = nullptr;
        price = 0;
        weight = 0;
        time = 0;
    }
    Rib(Point* start, Point* end) {
        this->start = start;
        this->end = end;
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
        cout << "Введите количество узлов: "; cin >> n_points;
        points = new Point[n_points];
        for (int i = 0; i < n_points; i++) {
            int k;
            points[i].index = i;
            cout << "Введите количество узлов из точки " << "(" << i << ")" << ": "; cin >> k;
            for (int j = 0; j < k; j++) {
                int index;
                cout << "Введите индекс узла: "; cin >> index;

                points[i].add_out(points[index].index);
                points[index].add_in(points[i].index);

                add_vertex(&points[i], &points[index]);
            }
        }
    }
    void add_vertex(Point* start, Point* end) {
        Rib* new_vertex = new Rib[n_vertex + 1];
        for (int i = 0; i < n_vertex; i++) {
            new_vertex[i] = vertex[i];
        }
        new_vertex[n_vertex] = Rib(start, end);
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
            cout << "(" << vertex[i].start->index << ")" << " -> " << "(" << vertex[i].end->index << ")" <<endl;
            //cout<<vertex[i].start<<" -> "<<vertex[i].end<<endl;
        }
    }
    int* add_in_array(int* array, int n, int k) {
        int* new_array = new int[n + 1];
        new_array[0] = k;
        for (int i = 0; i < n; i++) {
            new_array[i+1] = array[i];
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
    bool in_used(Point** used, int n_used, int index) {
        for (int i = 0; i < n_used; i++) {
            if (used[i]->index == index)return true;
        }
        return false;
    }
    void DFS_while() {
        Point** used = new Point*[n_points];
        int n_used = 0, k;
        cout << "Введите точку, с которой надо начать обход в глубину: "; cin >> k;
        used = add_in_used(used, n_used,  &points[k]);
        n_used++;
        int* q = new int[1];
        q[0] = k;
        int n_q = 1;
        while (n_q > 0) {
            bool new_point = false;
            for (int i = 0; i < n_vertex; i++) {
                if (vertex[i].start->index == q[0]) {
                    if (!(in_used(used, n_used, vertex[i].end->index))) {            
                        used = add_in_used(used, n_used, vertex[i].end);
                        n_used++;
                        q = add_in_array(q, n_q, vertex[i].end->index);
                        n_q++;
                        new_point = true;
                        break;
                    }
                }
            }
            if (!(new_point)) {
                q = remove_from_array(q, n_q);
                n_q--;
            }
        }
        for (int i = 0; i < n_used; i++) {
            cout << used[i]->index << " ";
        }
        cout <<endl;
    }
    void start_DFS() {
        Point** used = new Point * [n_points];
        int n_used = 0, k;
        cout << "Введите точку, с которой надо начать обход в глубину: "; cin >> k;
        used = add_in_used(used, n_used, &points[k]);
        n_used++;
        points[k].set_p(-1);
        DFS(used, n_used, &points[k]);
    }
    void DFS(Point** used, int n_used, Point* active_point) {
        for (int i = 0; i < n_vertex; i++) {
            if (vertex[i].start->index == active_point->index) {
                if (!(in_used(used, n_used, vertex[i].end->index))) {
                    used = add_in_used(used, n_used, vertex[i].end);
                    n_used++;
                    vertex[i].end->set_p(active_point->index);
                    DFS(used, n_used, vertex[i].end);
                    return;
                }
            }
        }
        if (active_point->get_p() == -1) {
            for (int i = 0; i < n_used; i++) {
                cout << used[i]->index << " ";
            }
            cout << endl;
            return;
        }
        DFS(used, n_used, &points[active_point->get_p()]);
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
        cout <<boolalpha << IsBipartite;
    }
    void find_cycle() {
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
                        if (colors[vertex[i].end->index] ==  1) {
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
        cout << boolalpha <<IsCycle;
    }
};

int main()
{
    setlocale(LC_ALL, "ru");
    Graph test;
    test.create();
    test.print_points();
    test.print_vertex();
    test.find_cycle();
    return 0;
}
