
#include <iostream>
//#include <Windows.h>
#include <string>
#include <fstream>
using namespace std;

class Point {
private:
    string name, value;
    string* attrs_name;
    string* attrs_value;
    int countAttr;
    Point** sub;
    int countSub;
    Point* predok;
public:
    Point() {
        countSub = 0;
        countAttr = 0;
        value = "";
        name = "";
        sub = new Point * [countSub];
        predok = nullptr;
    }
    void setName(string newName) {
        this->name = newName;
    }
    string getName() {
        return this->name;
    }
    void setValue(string newValue) {
        this->value = newValue;
    }
    void setValue(int newValue) {
        this->value = to_string(newValue);
    }
    void setValue(double newValue) {
        this->value = to_string(newValue);
    }
    string getValue() {
        return this->value;
    }
    bool isInt() {
        for (int i = 0; i < value.size(); i++) {
            if (!(value[i] >= '0' && value[i] <= '9'))return false;
        }
        return true;
    }
    bool isDouble() {
        bool first = false, sep = false, second = false;
        for (int i = 0; i < value.size(); i++) {
            if (value[i] >= '0' && value[i] <= '9') {
                if (!(first))first = true;
                if (!(second) && sep)second = true;
            }
            else {
                if (value[i] == '.') {
                    if (!(first))return false;
                    else sep = true;
                }
                else return false;
            }
        }
        if (sep) {
            return second;
        }
        else {
            return first;
        }
    }
    int getInt() {
        if (isInt())return stoi(value);
        else return 0;
    }
    double getDouble() {
        if (isDouble())return stoi(value);
        else return 0;
    }
    int getCountSub() {
        return countSub;
    }
    Point* getPredok() {
        return predok;
    }
    void setPredok(Point* predok) {
        this->predok = predok;
    }
    Point* getSub(int index) {
        if (index >= 0 && index < countSub) {
            return sub[index];
        }
        else {
            return NULL;
        }
    }
    Point* getSub(string name) {
        for (int i = 0; i < countSub; i++) {
            if (sub[i]->name == name)return sub[i];
        }
        return NULL;
    }
    string getAttrName(int index) {
        return attrs_name[index];
    }
    string getAttrValue(int index) {
        return attrs_value[index];
    }
    void setAttrName(int index, string new_name) {
        if (index >= 0 && index < countAttr)attrs_name[index] = new_name;
    }
    void setAttrValue(int index, string new_value) {
        if (index >= 0 && index < countAttr)attrs_value[index] = new_value;
    }
    int getCountAttrs() {
        return countAttr;
    }
    void addSub(Point* newSub) {
        Point** copySub = new Point * [countSub + 1];
        for (int i = 0; i < countSub; i++) {
            copySub[i] = sub[i];
        }
        copySub[countSub] = newSub;
        countSub++;
        sub = copySub;

    }
    void addAttr(string newAttr, string value) {
        string* new_attrs = new string[countAttr + 1];
        string* new_attrs_value = new string[countAttr + 1];
        for (int i = 0; i < countAttr; i++) {
            new_attrs[i] = attrs_name[i];
            new_attrs_value[i] = attrs_value[i];
        }
        new_attrs[countAttr] = newAttr;
        new_attrs_value[countAttr] = value;
        attrs_name = new_attrs;
        attrs_value = new_attrs_value;
        countAttr++;
    }
    void deleteSub(int index) {
        Point** copySub = new Point * [countSub - 1];
        for (int i = 0,j = 0; i < countSub; j++,i++) {
            if (i == index)i++;
            if (i < countSub)copySub[j] = sub[i];
        }
        countSub--;
        sub = copySub;
    }
};

struct endPars {
    Point* block;
    int index;
    endPars(Point* block, int index) {
        this->block = block;
        this->index = index;
    }
};

class MultiplTree {
private:
    Point* root;
    Point* current_point;
    string xml;
    ifstream file;
    ofstream out;
    string first;
    bool file_is_load;
public:
    MultiplTree() {
        root = new Point();
        root->setName("~");
        current_point = root;
        file_is_load = false;
    }
    void ls() {
        if (!(file_is_load)) {
            not_load();
            return;
        }
        for (int i = 0; i < current_point->getCountSub(); i++) {
            cout <<"'"<< current_point->getSub(i)->getName()<<"'" << " ";
        }
        cout << endl;
    }
    bool get_load() {
        return file_is_load;
    }
    void cd(string path) {
        if (!(file_is_load)) {
            not_load();
            return;
        }
        cd_recur(path);
    }
    void cd_recur(string path) {
        if (path.size() == 0)return;
        string name_next = "";
        if (path.find("/") != -1) {
            name_next = path.substr(0, path.find("/"));
            path = path.substr(path.find("/") + 1, path.size());
        }
        else {
            name_next = path.substr(0, path.size());
            path = "";
        }
        try {
            if (name_next == "..") {
                current_point = current_point->getPredok();
                cd_recur(path);
                return;
            }
            else {
                for (int i = 0; i < current_point->getCountSub(); i++) {
                    if (current_point->getSub(i)->getName() == name_next) {
                        current_point = current_point->getSub(i);
                        cd_recur(path);
                        return;
                    }
                }
                throw "";
            }
        }
        catch (...) {
            cout << "Не удалось перейте в узел '" << name_next << "'" << endl;
        }
    }
    
    void changeName() {
        if (!(file_is_load)) {
            not_load();
            return;
        }
        string new_name;
        cout << "Введите новое имя узла: "; cin >> new_name;
        current_point->setName(new_name);
        cout << "Имя успешно изменено." << endl;
    }
    void changeValue() {
        if (!(file_is_load)) {
            not_load();
            return;
        }
        if (current_point->getValue() == "") {
            cout << "У данного узла не может быть установлено значение." << endl;
            return;
        }
        string new_value;
        cout << "Введите новое значение узла: "; cin >> new_value;
        current_point->setValue(new_value);
        cout << "Значене узла успешно изменено." << endl;
    }
    int choiceAttr() {
        if (!(file_is_load)) {
            not_load();
            return NULL;
        }
        if (current_point->getCountAttrs() == 0) {
            cout << "У узла нет параметра для изменения." << endl;
            return NULL;
        }
        cout << "Выберите номер параметра для изменения" << endl;
        for (int i = 0; i < current_point->getCountAttrs(); i++) {
            cout << "(" << i + 1 << ") " << current_point->getAttrName(i) << endl;
        }
        int choice = 0;
        while (choice<1 || choice>current_point->getCountAttrs()) {
            cin >> choice;
        }
        return choice;

    }
    void changeNameAttr() {
        int index = choiceAttr();
        if (!(index))return;
        string new_name;
        cout << "Введите новое имя параметра: "; cin >> new_name;
        current_point->setAttrName(index-1, new_name);
        cout << "Имя параметра изменено." << endl;
    }
    void changeValueAttr() {
        int index = choiceAttr();
        if (!(index))return;
        string new_value;
        cout << "Введите новое значение параметра: "; cin >> new_value;
        current_point->setAttrValue(index-1, new_value);
        cout << "Значение параметра изменено." << endl;
    }
    void createAttr() {
        string name, value;
        cout << "Введите имя нового параметра: "; cin >> name; 
        cout << "Введите значение нового параметра: "; cin >> value;
        current_point->addAttr(name, value);
        cout << "Параметра добавлен." << endl;
    }
    string get_full_path() {
        string path = xml+":"+current_point->getName();
        if (current_point->getPredok() != nullptr)path = recur_path(current_point->getPredok()) + "/" + path;
        return path+"# ";
    }
    string recur_path(Point* point) {
        string path = point->getName();
        if (point->getPredok()!=nullptr)path = recur_path(point->getPredok()) + "/" + path;
        return path;
    }
    void del_path(string path,Point* temppoint) {
        string name_next = "";
        if (path.find("/") != -1) {
            name_next = path.substr(0, path.find("/"));

            path = path.substr(path.find("/") + 1, path.size());
            
            try {
                if (name_next == "..") {
                    temppoint = temppoint->getPredok();
                    del_path(path, temppoint);
                    return;
                }
                else {
                    for (int i = 0; i < temppoint->getCountSub(); i++) {
                        if (temppoint->getSub(i)->getName() == name_next) {
                            temppoint = temppoint->getSub(i);
                            del_path(path, temppoint);
                            return;
                        }
                    }
                    throw "";
                }
            }
            catch (...) {
                cout << "Не удалось перейте в узел '" << name_next << "'" << endl;
                return;
            }
        }
        else {
            name_next = path.substr(0, path.size());
            for (int i = 0; i < temppoint->getCountSub(); i++) {
                if (temppoint->getSub(i)->getName() == name_next) {
                    bfc_delete(temppoint->getSub(i));
                    temppoint->deleteSub(i);
                    return;
                }
            }
            cout << "Узла с именем '" << name_next << "' не найдено" << endl;
        }
    }
    void add_path(string path, Point* temppoint,Point* new_point) {
        string name_next = "";
        if (path.find("/") != -1) {
            name_next = path.substr(0, path.find("/"));

            path = path.substr(path.find("/") + 1, path.size());

            try {
                if (name_next == "..") {
                    temppoint = temppoint->getPredok();
                    add_path(path, temppoint,new_point);
                    return;
                }
                else {
                    for (int i = 0; i < temppoint->getCountSub(); i++) {
                        if (temppoint->getSub(i)->getName() == name_next) {
                            temppoint = temppoint->getSub(i);
                            add_path(path, temppoint,new_point);
                            return;
                        }
                    }
                    throw "";
                }
            }
            catch (...) {
                cout << "Не удалось перейте в узел '" << name_next << "'" << endl;
                return;
            }
        }
        else {
            name_next = path.substr(0, path.size());
            if (temppoint->getValue() != "") {
                cout << "У данного узла ("<< temppoint->getName()<<") не может быть потомков" << endl;
                return;
            }
            new_point->setPredok(temppoint);
            
            string index = "";
            if (temppoint->getSub(name_next)) {
                index = "1";
                for (int i = 0; i < temppoint->getCountSub(); i++) {
                    if (temppoint->getSub(i)->getName().substr(0, name_next.size()) == name_next) {
                        string name = temppoint->getSub(i)->getName();     
                        if (name.size() > name_next.size()) {
                            int new_index = stoi(name.substr(name_next.size(), name.size() - name_next.size())) + 1;
                            index = to_string(new_index);
                        }
                    }
                }
            }
            new_point->setName(name_next+index);
            temppoint->addSub(new_point);
        }
    }
    void bfc_delete(Point* point_to_delete) {
        for (int i = 0; i < point_to_delete->getCountSub(); i++) {
            Point* sub = point_to_delete->getSub(0);
            if (sub->getCountSub() > 0) {
                
                for (int j = 0; j < sub->getCountSub(); j++) {
                    bfc_delete(sub->getSub(0));
                    sub->deleteSub(0);
                }
            }
            point_to_delete->deleteSub(0);
        }
    }
    void delete_point(string path) {
        if (!(file_is_load)) {
            not_load();
            return;
        }
        del_path(path, current_point);
    }
    void add_point(string path) {
        if (!(file_is_load)) {
            not_load();
            return;
        }
        Point* new_point = new Point;
        bool value = false;
        string choice="";
        cout << "Будет ли value у этого узла? y/n" << endl;
        while (choice != "y" && choice != "n") {
            cin >> choice;
        }
        if (choice == "y")new_point->setValue("none");
        add_path(path, current_point, new_point);
    }
    void print_value() {
        if (!(file_is_load)) {
            not_load();
            return;
        }
        if (current_point->getValue() != "") {
            cout << current_point->getValue() << endl;
        }
        else {
            cout << "У данного узла нет value" << endl;
        }
    }
    void print_attr() {
        if (!(file_is_load)) {
            not_load();
            return;
        }
        if (current_point->getCountAttrs() > 0) {
            for (int i = 0; i < current_point->getCountAttrs(); i++) {
                cout << "(" << i + 1 << ") " << current_point->getAttrName(i) <<" ==> "<< current_point->getAttrValue(i) << endl;
            }
        }
        else {
            cout << "У данного узла нет атрибутов" << endl;
        }
    }
    void not_load() {
        cout << "Файл не загружен!" << endl;
    }
    void load(string path) {
        root = new Point();
        root->setName("~");
        current_point = root;
        file_is_load = false;
        file.open(path);
        if (file.is_open())
        {   
            xml = path;
            char current_char;
            getline(file, first);
            while (file.get(current_char))
            {
                if (current_char == '<') {
                    Point* new_sub = pars_block();
                    new_sub->setPredok(root);
                    root->addSub(new_sub);
                }
                    
            }
            file.close();
            file_is_load = true;
        }
        else {
            cout << "Такого файла не существует!" << endl;
        }
    }
    void save() {
        
        out.open(xml);
        if (out.is_open())
        {
            out << first << endl;
        }
        for (int i = 0; i < root->getCountSub(); i++) {
            Point* sub = root->getSub(i);
            save_block(sub,0);
        }
        out.close();
        cout << "Файл успешно сохранен!" << endl;
    }
    void print() {
        cout << root->getCountSub() << endl;
        Point* sub = root->getSub(0);
        cout << sub->getName() << " ";
        for (int i = 0; i < sub->getCountAttrs(); i++) {
            cout << sub->getAttrName(i) << " = '" << sub->getAttrValue(i) << "'" << " ";
        }
        cout << endl;
        cout << sub->getCountSub() << endl;
        for (int i = 0; i < sub->getCountSub(); i++) {
            Point* newsub = sub->getSub(i);
            cout << newsub->getName() << " " << newsub->getCountSub() << endl;
        }
    }
    void save_block(Point* sub,int k){
        for (int i = 0; i < k; i++) {
            out << "\t";
        }
        out << "<" + sub->getName();
        if (sub->getCountAttrs() > 0) {
            for (int j = 0; j < sub->getCountAttrs(); j++) {
                out << " ";
                string nameAttr = sub->getAttrName(j);
                out << nameAttr;
                out << "=";
                out << '"';
                string valueAttr = sub->getAttrValue(j);
                out << valueAttr;
                out << '"';

            }
        }
        out << ">";
        if (sub->getValue() != "") {
            out << sub->getValue();
        }
        if(sub->getCountSub()>0) {
            out << "\n";
            for (int i = 0; i < sub->getCountSub(); i++) {
                save_block(sub->getSub(i),k+1);
                
            }
            for (int i = 0; i < k; i++) {
                out << "\t";
            }
        }
        
        out << "</" + sub->getName() + ">\n";
    }
    Point* pars_block() {
        char current_char;
        Point* new_point = new Point();
        int k = 0;
        string name, value, close_name, attr_name, attr_value;
        bool read_name = true, read_attr_name=false, read_attr_value = false, check_value = false, add_sub = false, read_value = false, close = false, read_close_name = false;
        while (file.get(current_char)) {
            if (int(current_char) == 13)continue;
            if (current_char == '<' && file.peek() == '/') {
                close = true;
                if (read_value) {
                    new_point->setValue(value);
                    read_value = false;
                }
                if (add_sub)add_sub = false;
                read_close_name = true;
            }
            if (current_char == '>' && close) {
                close = false;
                read_close_name = false;
                if (close_name != name) {
                    cout << "Ошибка в файле!\nОткрыт блок: '" << name << "', а закрывается: '" << close_name << "'" << endl;
                    exit(0);
                }
                return new_point;
            }
            if (read_name) {
                if (read_attr_value) {
                    if (current_char == '"') {
                        k++;
                    }
                    if (k == 1 && current_char != '"')attr_value += current_char;
                    if (k == 2) {
                        new_point->addAttr(attr_name, attr_value);
                        k = 0;
                        attr_name = ""; attr_value = ""; read_attr_value = false;
                    }
                }
                else if (read_attr_name) {
                    if (current_char == '=') {
                        read_attr_name = false;
                        read_attr_value = true;
                    }
                    else attr_name += current_char;
                }
                else if (current_char == ' ') {
                    read_attr_name = true;

                }
                else if (current_char == '>') {
                    read_name = false;
                    new_point->setName(name);
                    check_value = true;
                    file.get(current_char);
                }
                else name += current_char;

            }
            if (check_value) {
                if (current_char == ' ' || current_char == '\t' || current_char == '\n' || int(current_char) == 13)continue;
                if (current_char == '<') {
                    add_sub = true;
                }
                else read_value = true;
                check_value = false;
            }
            if (add_sub) {
                if (current_char == '<') {
                    Point* new_sub = pars_block();
                    new_sub->setPredok(new_point);
                    new_point->addSub(new_sub);
                } 
            }
            if (read_value)value += current_char;

            if (read_close_name) {
                if (current_char != '<' && current_char != '/') close_name += current_char;
            }
        }
        return new_point;
    }
};


class Controller {
private:
    MultiplTree mainTree;
public:
    void execute() {
        
        bool run = true;
        string help = "help load ls value attr cd del add edit save exit";
        cout <<help  << endl;
        while (run) {
            string line;
            cout <<mainTree.get_full_path();
            getline(cin, line);
            string command, arg;
            if (line.find(" ") == -1) {
                command = command = line.substr(0, line.size());
            }
            else {
                command = line.substr(0, line.find(" "));
                arg = line.substr(line.find(" ")+1, line.size());
            }
            if (command == "help") {
                cout << help << endl;
            }
            if (command == "load") {
                mainTree.load(arg);
            }
            if (command == "ls") {
                mainTree.ls();
            }
            if (command == "save") {
                mainTree.save();
            }
            if (command == "value") {
                mainTree.print_value();
            }
            if (command == "attr") {
                mainTree.print_attr();
            }
            if (command == "cd") {
                mainTree.cd(arg);
            }
            if (command == "del") {
                mainTree.delete_point(arg);
            }
            if (command == "add") {
                mainTree.add_point(arg);
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            if (command == "exit") {
                break;
            }
            if (command == "edit") {
                if (!(mainTree.get_load())) {
                    mainTree.not_load();
                    continue;
                }
                cout << "Выберите, какой пункт редактирования узла" << endl;
                cout << "1) Название узла" << endl;
                cout << "2) Значение узла" << endl;
                cout << "3) Название параметра" << endl;
                cout << "4) Значение параметра" << endl;
                cout << "5) Добавить параметр" << endl;
                int choice = 0;
                while (choice < 1 || choice >5) {
                    cin >> choice;
                }
                switch (choice)
                {
                case 1:
                    mainTree.changeName();
                    break;
                case 2:
                    mainTree.changeValue();
                    break;
                case 3:
                    mainTree.changeNameAttr();
                    break;
                case 4:
                    mainTree.changeValueAttr();
                    break;
                case 5:
                    mainTree.createAttr();
                    break;
                default:
                    break;
                    
                }
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            
        }
    }
};


int main()
{
    setlocale(LC_ALL, "RU");
    Controller ctrl;
    ctrl.execute();
    return 0;
}
