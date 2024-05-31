#include <iostream>
#include <string>
#include <stdio.h> 
#include <time.h>
#include <chrono>
using namespace std;

class Graph {
private:
    int* points;
    int n_points = 0;
    int n_connection = 0;
    int** vertex;
    int* used; 
    int* p;
    int* point_path;
    int n_path;
    int n_used = 1;
    int n_fast_cycle = 123123;
    int* fast_cycle;
public:
    Graph() {
        n_points = 8;
        n_connection = 24;
        points = new int[n_points];
        vertex = new int* [n_connection];
        for (int i = 0; i < n_points; i++) {
            points[i] = i;
        }
        for (int i = 0; i < n_connection; i++) {
            vertex[i] = new int[2];
        }
    }



    void create() {
        cout << "Введите количество узлов: "; cin >> n_points;
        n_connection = 0;
        points = new int[n_points];
        for (int i = 0; i < n_points; i++) {
            points[i] = i;
            int k;
            cout << "Введите количество узлов у точки " << i << ": "; cin >> k;
            for (int j = 0; j < k; j++) {
                int n;
                cout << "Введите точку к которой идет узел: "; cin >> n;
                vertex[n_connection][0] = i;
                vertex[n_connection][1] = n; 
                n_connection++;
            }
        }
    }



    void print_points() {
        for (int i = 0; i < n_points; i++) {
            cout << points[i] << endl;
        }
    }



    void print_connection() {
        for (int i = 0; i < n_connection; i++) {
            if (vertex[i][0] == vertex[i][1] && vertex[i][0] == 0)continue;
            cout << vertex[i][0] << " -> " << vertex[i][1] << endl;
        }
    }



    void add_used(int k, int predok) {
        int* new_used = new int[n_used + 1];
        int* new_p = new int[n_used + 1];
        for (int i = 0; i < n_used; i++) {
            new_used[i] = used[i];
            new_p[i] = p[i];
        }
        new_p[n_used] = predok;
        new_used[n_used] = k;
        used = new_used;
        p = new_p;
        n_used++;
    }



    bool check_in_used(int k) {
        for (int i = 0; i < n_used; i++) {
            if (used[i] == k)return true;
        }
        return false;
    }
 


    void start_fire(int s) {
        n_used = 1;
        used = new int[n_used];
        p = new int[n_used];
        used[0] = s;
        p[0] = -1;
        fire(s);
    }



    void add_path(int k) {
        int* new_array = new int[n_path + 1];
        for (int i = 0; i < n_path; i++) {
            new_array[i] = point_path[i];
        }
        new_array[n_path] = k;
        point_path = new_array;
        n_path++;
    }



    void fire(int index) {
        int *point_vertex = new int[n_connection];
        int k = 0;
        for (int i = 0; i < n_connection; i++) {
            if (vertex[i][0] == index) {
                if (!(check_in_used(vertex[i][1]))) {
                    add_used(vertex[i][1], index);
                    point_vertex[k] = vertex[i][1];
                    k++;
                }
            }
        }
        for (int i = 0; i < k; i++) {
            fire(point_vertex[i]);
        }
    }



    void start_path() {
        int x, y;
        cout << "Введите начальную точку: "; cin >> x;
        cout << "Введите конечную точку: "; cin >> y;
        start_fire(x);
        n_path = 1;
        point_path = new int[n_path];
        point_path[0] = y;
        path(y);
        for (int i = n_path - 2; i >= 0; i--) {
            cout << point_path[i] << " ";
        }
        cout << endl;
    }



    void path(int index) {
        for (int i = 0; i < n_used; i++) {
            if (used[i] == index) {
                add_path(p[i]);
                path(p[i]); 
            }
        }
    }



    void start_fast_cycle() {
        for (int i = 0; i < n_points; i++) {
            n_used = 1;
            used = new int[n_used];
            p = new int[n_used];
            used[0] = i;
            p[0] = -1;
            cycle(points[i]);
        }
        cout << "Кратчайший: " << n_fast_cycle << endl;
        cout << "Путь: "; for (int i = 0; i < n_fast_cycle; i++)cout << fast_cycle[i] << " ";
        cout << endl;
    }



    void cycle(int index) {
        int* point_vertex= new int [n_connection];
        int k = 0;
        for (int i = 0; i < n_connection; i++) {
            if (vertex[i][0] == index) {
                if (!(check_in_used(vertex[i][1]))) {
                    add_used(vertex[i][1], index);
                    point_vertex[k] = vertex[i][1];
                    k++;
                }
                else {
                    if (n_used < n_fast_cycle) {
                        n_fast_cycle = n_used;
                        fast_cycle = new int[n_fast_cycle];
                        for (int j = 0; j < n_fast_cycle; j++)fast_cycle[j] = used[j];
                        return;
                    }
                }
            }
        }
        for (int i = 0; i < k; i++) {
            cycle(point_vertex[i]);
        }
        
    }



    bool in_array(int element, int* array, int n) {
        for (int i = 0; i < n; i++) {
            if (element == array[i])return true;
        }
        return false;
    }



    int find_component() {
        int** components = new int* [n_points]; 
        int n_components = 0;
        int* all_points = new int[n_points];
        int n_all_points = 0;
        int start_point = 0;
        while (n_all_points != n_points) {
            start_fire(start_point);
            for (int i = 0; i < n_used; i++) {
                all_points[n_all_points] = used[i];
                n_all_points++;
            }
            components[n_components] = new int[n_used];
            for (int i = 0; i < n_used; i++) {
                components[n_components][i] = used[i];
            }
            n_components++;
            for (int i = 0; i < n_points; i++) {
                if (!(in_array(points[i], all_points, n_all_points))) {
                    start_point = points[i];
                    break;
                }
            }
        }
        return n_components;

    }



    void find_points() {
        int* copy_points = new int[n_points];
        int** copy_vertex = new int*[n_connection];
        for (int i = 0; i < n_points; i++) {
            copy_points[i] = points[i];
        }
        for (int i = 0; i < n_connection; i++) {
            copy_vertex[i] = vertex[i];
        }
        int copy_connection = n_connection;
        for (int i = 0; i < n_points; i++) {
            int* new_points = new int[n_points - 1];
            for (int j = 0; j < n_points; j++) {
                if (j == i)j++;
                if (j == n_points)break;
                new_points[i] = points[i];
            }
            int** new_vertex = new int* [n_connection];
            int new_connection = 0;
            for (int j = 0; j < n_connection; j++) {
                if (vertex[j][0] != i && vertex[j][1] != i)
                {
                    new_vertex[new_connection] =new int[2];
                    new_vertex[new_connection][0] = vertex[j][0]; new_vertex[new_connection][1] = vertex[j][1];
                    new_connection++;
                }
            }
            points = new_points;
            n_points--;
            n_connection = new_connection;
            vertex = new int*[n_connection];
            for (int j = 0; j < n_connection; j++) {
                vertex[j] = new_vertex[j];
            }
            ///////////////////////////////////////////////////////
            int k = find_component();
            if (k > 1) {
                cout << i << " ";
            }
            ///////////////////////////////////////////////////////
            points = copy_points;
            n_points++;
            vertex = copy_vertex;
            n_connection = copy_connection;
        }
        cout << endl;
    }
};

int main()
{
    setlocale(LC_ALL, "ru");
    Graph test;
    test.create();
    test.print_connection();
    //test.start_fire_while();
    //test.start_fire(0);
    test.find_points();
    return 0;
}
