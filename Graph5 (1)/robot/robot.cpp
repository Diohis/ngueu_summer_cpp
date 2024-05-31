#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>

using namespace std;

class Storage {
private:
    int** storage;
    int n, m, min, row, col;
public:
    Storage() {
        ifstream file;
        file.open("input.txt");
        if (file.is_open())
        {
            string line;
            getline(file, line);
            n = stoi(line.substr(0, 1));
            line = line.erase(0, 2);
            m = stoi(line.substr(0, 1));
            storage = new int* [n];
            for (int i = 0; i < n; i++) {
                getline(file, line);
                storage[i] = new int[m];
                for (int j = 0; j < m; j++) {
                    int x = stoi(line.substr(0, 1));
                    if (x == 2) {
                        col = j;
                        row = i;
                    }
                    line = line.erase(0, 2);
                    storage[i][j] = x;
                }
            }
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                }
            }
            min = n * m + 1;
            string path = "";
            if(bfs(row, col, 0, path)==-1) {
                cout << "Невозможно добраться" << endl;
            }
            else cout << min << endl;
            file.close();
        }
    }
    int** create_copy() {
        int** copy = new int* [n];
        for (int i = 0; i < n; i++) {
            copy[i] = new int[m];
            for (int j = 0; j < m; j++) {
                copy[i][j] = storage[i][j];
            }
        }
        return copy;
    }
    int bfs(int row, int col, int k, string path) {
        string newpath = path + to_string(row) + ":" + to_string(col) + " ";
        if (storage[row][col] == 3) {
            if (k < min) {
                min = k;
            }
        }
        storage[row][col] = 4;
        if (row - 1 > 0) {
            if (storage[row - 1][col] != 1 && storage[row - 1][col] != 4) {
                bfs(row - 1, col, k + 1, newpath);
            }
        }
        if (row + 1 < this->n) {
            if (storage[row + 1][col] != 1 && storage[row + 1][col] != 4) {
                bfs(row + 1, col, k + 1, newpath);

            }
        }
        if (col - 1 > 0) {
            if (storage[row][col - 1] != 1 && storage[row][col - 1] != 4) {
                bfs(row, col - 1, k + 1, newpath);

            }
        }
        if (col + 1 < this->m) {
            if (storage[row][col + 1] != 1 && storage[row][col + 1] != 4) {
                bfs(row, col + 1, k + 1, newpath);

            }
        }
        storage[row][col] = 0;
        return -1;
    }

};

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
    void clear_path() {
        path = new int[1];
        path[0] = index;
        n_path = 1;
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

class Security {
private:

    int n_points, n_vertex;
    Point* points;
    Rib* vertex;
    int* visited;
    int* back_to_start;
    int n, m, min_path, k_min_path;

public:
    Security() {
        ifstream file;
        file.open("input.txt");
        if (file.is_open())
        {
            string line;
            getline(file, line);
            n = stoi(line.substr(0, 3));
            line = line.erase(0, 2);
            m = stoi(line.substr(0, 3));
            n =5;
            m =5;
            points = new Point[(n + 1) * (m + 1)];
            n_points = (n + 1) * (m + 1);
            cout << "###" << n << " " << m << endl;
            for (int i = 0; i < m + 1; i++) {
                for (int j = 0; j < n + 1; j++) {
                    points[i * (n + 1) + j].index = i * (n + 1) + (j + 1);
                    //cout<<i*(n+1)+(j+1)<<" ";
                }
                //cout<<endl;
            }
            int k = 1;
            for (int i = 0; i < m + 1; i++) {
                for (int j = 0; j < n + 1; j++) {
                    if (i < m) {
                        add_vertex(&points[i * (n + 1) + j], &points[(i + 1) * (n + 1) + j], k);
                        k++;
                    }

                    if (j < n) {
                        add_vertex(&points[i * (n + 1) + j], &points[i * (n + 1) + j + 1], k);
                        k++;
                    }
                }
            }
            visited = new int[n_vertex];
            min_path = n_vertex * n_vertex;
            for (int i = 0; i < n_vertex; i++) {
                visited[i] = 0;
            }
            k_min_path = 0;
            ////////////////////////////////
            Point** used = new Point * [n_points];
            int n_used = 0;
            used = add_in_used(used, n_used, &points[0]);
            n_used++;
            int* q = new int[1];
            q[0] = 1;
            int n_q = 1;
            while (n_q > 0) {
                bool new_point = false;
                for (int i = 0; i < n_vertex; i++) {
                    if (vertex[i].start->index == q[0]) {
                        if (!(in_used(used, n_used, vertex[i].end->index))) {
                            used = add_in_used(used, n_used, vertex[i].end);
                            vertex[i].end->n_path = (vertex[i].start->n_path) + 1;
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
            //////////////////////////////////
            back_to_start = new int[n_points];
            for (int i = 0; i < n_points; i++) {
                back_to_start[i] = points[i].n_path;
            }
            file.close();
        }
    }

    int* add_in_array(int* array, int n, int k) {
        int* new_array = new int[n + 1];
        for (int i = 0; i < n; i++) {
            new_array[i] = array[i];
        }
        delete[]array;
        new_array[n] = k;
        return new_array;
    }
    int* remove_from_array(int* array, int n) {
        int* new_array = new int[n - 1];
        for (int i = 1; i < n; i++) {
            new_array[i - 1] = array[i];
        }
        delete[]array;
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
    void add_vertex(Point* start, Point* end, int index) {
        Rib* new_vertex = new Rib[n_vertex + 1];
        for (int i = 0; i < n_vertex; i++) {
            new_vertex[i] = vertex[i];
        }
        new_vertex[n_vertex] = Rib(start, end, index);
        vertex = new_vertex;
        n_vertex++;
    }
    int get_min_path() {
        return min_path;
    }
    void output(int index, int k, string path) {
        bool jump = false;
        for (int i = 0; i < n_vertex; i++) {
            if ((vertex[i].end->index == index || vertex[i].start->index == index) && visited[i] == 0) {
                visited[i] = 1;
                int index_next_point = index;
                if (vertex[i].end->index == index)index_next_point = vertex[i].start->index;
                else index_next_point = vertex[i].end->index;
                jump = true;
                string new_path = to_string(index_next_point) + " ";
                output(index_next_point, k + 1,path+new_path);
                visited[i] = 0;
            }
        }
        int k_rib = 0;
        for (int i = 0; i < n_vertex; i++) {
            if (visited[i] == 1)k_rib++;
        }
        if (k_rib == n_vertex) {
            if (k + back_to_start[index - 1] < min_path) {
                min_path = k + back_to_start[index - 1];
                cout << min_path << endl;
                /*
                if (k + back_to_start[index - 1] < min_path) {
                    k_min_path = 1;
                }
                else {
                    k_min_path++;
                }
                min_path = k + back_to_start[index - 1];
                cout << "K: "<<k_min_path <<" "<<min_path<< endl;
                
                if (index == 1) {
                    cout << "###: " << k + back_to_start[index - 1] << endl;
                    cout << path<< endl;
                    cout << k_min_path << endl;
                    string newpath = path;
                    int z = newpath.find(" ");
                    int last = stoi(newpath.substr(0, z));
                    newpath = newpath.substr(z + 1, newpath.size());
                    int current;
                    while (newpath.find(" ") != -1) {
                        z = newpath.find(" ");
                        current = stoi(newpath.substr(0, z));
                        newpath = newpath.substr(z + 1, newpath.size());
                        int razn = current - last;
                        if (razn == 1)cout << "--> ";
                        else if (razn == -1)cout << "<-- ";
                        else if (razn == n + 1)cout << "V ";
                        else if (razn == -1 * (n + 1))cout << "^ ";
                        last = current;
                    }
                    cout << endl;
                    cout << "-----------------" << endl;
                   
                }
                */
            }


            return;
        }
        if (!jump) {
            //cout<<index<<endl;
            int index_next_point = find_rib(index);
            string new_path = to_string(index_next_point) + " ";
            output(index_next_point, k + 1,path+new_path);
        }

        //после обхода всех возожных ребер обнулять посещение (для других путей)
    }
    int find_rib(int index) {
        int* used = new int[n_points];
        int* p = new int[n_points];
        used[index - 1] = 1;
        int* q = new int[1];
        q[0] = index;
        int n_q = 1;
        p[index - 1] = -1;
        points[index - 1].n_path = 0;
        while (n_q > 0) {
            bool new_point = false;
            for (int i = 0; i < n_vertex; i++) {
                if (vertex[i].start->index == q[0] || vertex[i].end->index == q[0]) {
                    //cout<<q[0]<<" "<<vertex[i].start->index<<" "<<vertex[i].end->index<<endl;
                    int start_point, end_point;
                    if (vertex[i].start->index == q[0]) {
                        start_point = vertex[i].start->index;
                        end_point = vertex[i].end->index;
                    }
                    else {
                        start_point = vertex[i].end->index;
                        end_point = vertex[i].start->index;
                    }
                    if (used[end_point - 1] != 1) {
                        q = add_in_array(q, n_q, end_point);
                        n_q++;
                        p[end_point - 1] = start_point;
                        used[end_point - 1] = 1;
                        points[end_point - 1].n_path = points[start_point - 1].n_path + 1;
                    }
                }
            }
            q = remove_from_array(q, n_q);
            n_q--;
        }
        int min_path = n_points;
        int index_new_point;
        for (int i = 0; i < n_points; i++) {
            //cout<<points[i].index<<" "<<points[i].n_path<<endl;
        }
        //cout<<endl;
        for (int i = 0; i < n_points; i++) {
            for (int j = 0; j < n_vertex; j++) {
                if (vertex[j].start->index == points[i].index || vertex[j].end->index == points[i].index) {
                    if (visited[j] == 0 && points[i].n_path < min_path && points[i].n_path != 0) {
                        index_new_point = points[i].index;
                        min_path = points[i].n_path;
                    }
                }

            }
        }

        while (true) {
            if (p[index_new_point - 1] == index)break;
            index_new_point = p[index_new_point - 1];
        }
        //cout<<"NOT JUNP: "<<index_new_point<<endl;
        delete[] used;
        delete[]p;
        delete[]q;
        return index_new_point;
    }
    /*
    int** create_copy(){
        int** copy = new int*[n];
        for (int i = 0;i<n;i++){
            copy[i]=new int[m];
            for (int j = 0;j<m;j++){
                copy[i][j]=storage[i][j];
            }
        }
        return copy;
    }
    int bfs(int row,int col,int k,string path){
        string newpath = path+to_string(row)+":"+to_string(col)+" ";
        if (storage[row][col]==3){
            if (k<min){
                min = k;
            }
            return k;
        }
        storage[row][col]=4;
        if (row-1>0){
            if (storage[row-1][col]!=1&&storage[row-1][col]!=4){
                bfs(row-1,col,k+1,newpath);
            }
        }
        if (row+1<this->n){
            if (storage[row+1][col]!=1&&storage[row+1][col]!=4){
                bfs(row+1,col,k+1,newpath);

            }
        }
        if (col-1>0){
            if (storage[row][col-1]!=1&&storage[row][col-1]!=4){
                bfs(row,col-1,k+1,newpath);

            }
        }
        if (col+1<this->m){
            if (storage[row][col+1]!=1&&storage[row][col+1]!=4){
                bfs(row,col+1,k+1,newpath);

            }
        }
        storage[row][col]=0;
        return -1;
    }
    */
    void print() {
        for (int i = 0; i < n_points; i++) {
            cout << points[i].index << " " << points[i].n_path << endl;;
        }
        cout << endl;
    }
    void print_vertex() {
        for (int i = 0; i < n_vertex; i++) {
            cout << vertex[i].start->index << " -> " << vertex[i].end->index << " " << vertex[i].index << endl;
        }
    }

};

int main()
{

    Security test;
    test.print();
    cout << "---------------------------" << endl;
    test.output(1, 0, "1 ");
    cout << endl << test.get_min_path() << endl;
    test.print_vertex();
    return 0;
}
