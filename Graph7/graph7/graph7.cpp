#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <string>
#include <vector>

using namespace std;
struct Point {
    int index; //номер точки для удобства
    int* in; //Массив индексов точек которые ведут в эту
    int n_in; //Количество этих точек
    int* out;//Массив индексов точек в которые можно пойти из текущей
    int n_out; //Количество этих точек
    int* path; //Путь до этой точки из заданной (для алгоритма используется)
    int n_path; //Длина пути
    int p;
    Point() {
        in = new int[1];
        n_in = 0;
        out = new int[1];
        n_out = 0;
        path = new int[1];
        n_path = 0;
    }
    Point(int index, int* in, int n_in, int* out, int n_out, int* path, int n_path) {
        this->index = index;
        this->in = in;
        this->n_in = n_in;
        this->out = out,
            this->n_out = n_out;
        this->path = path;
        this->n_path = n_path;
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
    void clear_path(){
        path = new int[1];
        path[0] = index;
        n_path = 1;
    }
};

struct Dei {
    Point** used;
    int n_used;
    Dei(Point** used, int n_used) {
        this->used = used;
        this->n_used = n_used;
    }
};

struct Rib {
    Point* start;
    Point* end;
    int index;
    Rib() {
        start = nullptr;
        end = nullptr;
        index = -1;
    }
    Rib(Point* start, Point* end, int index) {
        this->start = start;
        this->end = end;
        this->index = index;
    }
};

class Graph {
private:
    Point* points;
    int n_points;
    Rib* vertex;
    int n_vertex;
    int** routes;
    int n_routes;
    int* len_routes;
public:
    Graph() {
        points = nullptr;
        vertex = nullptr;
        routes = nullptr;
        len_routes = nullptr;
        n_points = 0;
        n_routes = 0;
        n_vertex = 0;
    }
    void create() {
        
        cout << "Введите количество остановок: "; cin >> n_points;
        points = new Point[n_points];
        for (int i = 0;i<n_points;i++){
            points[i].index = i;
            points[i].path[0] = i;
            points[i].n_path++;
        }

        cout<<"Введите количество маршрутов: ";cin>>n_routes;
        routes = new int*[n_routes];
        len_routes = new int[n_routes];
        for (int i = 0; i < n_routes; i++) {
            int k;
            int* local_route=new int[0];
            int n_local_route=0;
            cout<<"Введите количество остановок в маршруте "<<i<<": ";cin>>k;
            for (int j = 0;j<k;j++){
                int n;
                cout<<"Введите номер остановки: ";cin>>n;
                local_route = add_local_route(n,local_route,n_local_route);
                n_local_route++;
            }
            add_routes(i,local_route,n_local_route);
        }
        for (int i = 0;i<n_routes;i++){
            for (int j = 1;j<len_routes[i];j++){
                add_vertex(&points[routes[i][j-1]],&points[routes[i][j]],i);
                add_vertex(&points[routes[i][j]],&points[routes[i][j-1]],i);
            }
        }
    }

    void add_routes(int index, int* local_route, int n_local_route) {
        routes[index] = local_route;
        len_routes[index] = n_local_route;
    }

    int* add_local_route(int point, int* local_route, int n) {
        int* new_route = new int[n + 1];
        for (int i = 0; i < n; i++) {
            new_route[i] = local_route[i];
        }
        new_route[n] = point;
        return new_route;
    }

    void add_vertex(Point* start, Point* end, int index) {
        Rib* new_vertex = new Rib[n_vertex + 1];
        for (int i = 0; i < n_vertex; i++) {
            new_vertex[i] = vertex[i];
        }
        new_vertex[n_vertex] = Rib(start, end, index);
        vertex = new_vertex;
        n_vertex++;
    }



    void print_points() {
        for (int i = 0; i < n_routes; i++) {
            for (int j = 0; j < len_routes[i]; j++) {
                cout << routes[i][j] << " ";
            }
            cout << endl;
        }
    }



    void print_vertex() {
        for (int i = 0; i < n_vertex; i++) {
            cout << vertex[i].start->index << " -> " << vertex[i].end->index << " " << vertex[i].index << endl;
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


    bool check_one_route(int start = NULL, int end = NULL, int index = NULL) {
        if (start == NULL) {
            int start, end, index;
            cout << "Введите начальную остановку: "; cin >> start;
            cout << "Введите конечную остановку: "; cin >> end;
            cout << "Введите индекс маршрута: "; cin >> index;
        }
        bool is_started, is_ended;
        for (int i = 0; i < len_routes[index]; i++) {
            cout << routes[index][i] << endl;
            if (routes[index][i] == start)is_started = true;
            if (routes[index][i] == end)is_ended = true;
            if (is_started && is_ended)return true;
        }
        return false;
    }
    void go() {
        int start, end, k;
        cout << "Введите начальную остановку: "; cin >> start;
        cout << "Введите конечную остановку: "; cin >> end;
        start_DFS(start);
        for (int i = 0; i < n_points; i++) {
            if (points[i].n_path < 2) {
                cout << "Невозможно добраться из любой остановки до любой другой остановки" << endl;
            }
        }
        cout << "Из любой остановки до любой другой остановки возможно добраться" << endl;
    }
    void go_k() {
        int start, end, k;
        cout << "Введите начальную остановку: "; cin >> start;
        cout << "Введите конечную остановку: "; cin >> end;
        cout << "Введите количество пересадок: "; cin >> k;
        start_DFS(start);
        if (points[end].n_path < 2)return;
        int change = 0;
        int active_route = -1;
        for (int i = 1; i < points[end].n_path; i++) {
            for (int j = 0; j < n_vertex; j++) {
                if (vertex[j].start->index == points[end].path[i - 1] && vertex[j].end->index == points[end].path[i]) {

                    if (active_route == -1)active_route = vertex[j].index;
                    else {
                        //cout<<vertex[j].start->index<<" -> "<<vertex[j].end->index<<" "<<active_route<<endl;
                        if (vertex[j].index != active_route) {
                            //cout<<active_route<<" ";
                            //cout<<vertex[j].start->index<<" -> "<<vertex[j].end->index<<endl;
                            active_route = vertex[j].index;
                            change++;
                            if (change > k) {
                                cout << "С заданным количеством пересадок невозможно добраться." << endl;
                                return;
                            }
                        }
                    }

                    break;
                }
            }
        }
        cout << "С заданным количеством пересадок возможно добраться." << endl;
    }
    void start_DFS(int start) {
        Point** used = new Point * [n_points];
        int n_used = 0;
        used = add_in_used(used, n_used, &points[start]);
        n_used++;
        points[start].set_p(-1);
        DFS(used, n_used, &points[start]);
    }
    void DFS(Point** used, int n_used, Point* active_point) {
        for (int i = 0; i < n_vertex; i++) {
            if (vertex[i].start->index == active_point->index) {
                if (!(in_used(used, n_used, vertex[i].end->index))) {
                    used = add_in_used(used, n_used, vertex[i].end);
                    n_used++;
                    vertex[i].end->set_p(active_point->index);
                    vertex[i].end->add_path(active_point->path, active_point->n_path, vertex[i].end->index);
                    DFS(used, n_used, vertex[i].end);
                    return;
                }
            }
        }
        if (active_point->get_p() == -1) {
            return;
        }
        DFS(used, n_used, &points[active_point->get_p()]);
    }
};

int main()
{
    setlocale(LC_ALL, "ru");
    Graph test;
    test.create();
    return 0;
}
