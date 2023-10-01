#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <random>
#include "geometry.cpp"

using namespace std;
using namespace geometry;

bool sort_func(const Circle* c1, const Circle* c2) {
    return c1->get_radius() < c2->get_radius();
}

void generate_array(vector<Curve*> &curves, double t) {
    srand(time(0));
    int random_len = abs((rand() % 20 + 1) * (rand() % 5) + 1);
    
    for (int i = 0; i < random_len; i++) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<double> dis(0.0, 10000.0);
        
        int random_class = abs(rand()) % 3;
        
        switch (random_class) {
            case 0:
                {
                Curve* circl = new Circle(dis(gen));
                curves.push_back(circl);
                break;
                }
            case 1:
                {
                Curve* ellips = new Ellipse(dis(gen), rand() / (double)RAND_MAX);
                curves.push_back(ellips);
                break;
                }
            default:
                {
                Curve* heli = new Helix(dis(gen), rand()/ (double)RAND_MAX);
                curves.push_back(heli);
                }
        }
    }
    
    cout << "Координаты точек и производных при t = PI/4:" << endl;
    cout << "--------------------------------------------" << endl;
    
    for (int i = 0; i < curves.size(); i++) {
        vector<double> points = curves[i]->get_point(t);
        vector<double> der = curves[i]->get_der(t);
        
        cout << curves[i]->class_name() << endl;
        cout << "Радиус фигуры: " << curves[i]->get_radius() << endl;
        
        cout << "Точка: (" << points[0] << ", " << points[1] <<
        ", " << points[2] << ")" << endl;
        
        cout << "Производная: (" << der[0] << ", " << der[1] << ", "
        << der[2] << ")" << endl;
        cout << endl;
    }
    
    cout << "--------------------------------------------" << endl;
}

void generate_circles(vector<Curve*>& curves, vector<Circle*>& circles) {
    for (int i = 0; i < curves.size(); i++) {
        if (curves[i]->class_name() == "Circle") {
            circles.push_back(dynamic_cast<Circle*>(curves[i]));
        }
    }
}

void sort_and_print(vector<Circle*> circles) {
    sort(circles.begin(), circles.end(), sort_func);
    
    cout << "\n\n-------------------------------------------" << endl;
    cout << "Отсортированные окружности по радиусам:" << endl;
    
    for (int i = 0; i < circles.size(); i++) {
        cout << circles[i]->get_radius() << endl;
    }

    double sum_rad = 0.0;

    for (int i = 0; i < circles.size(); i++) {
        sum_rad += circles[i]->get_radius();
    }
    
    cout << "--------------------------------------------" << endl;
    cout << "Сумма радиусов окружностей: " << sum_rad << endl;
}

int main(void) {
    const double t = M_PI / 4.0;
    vector<Curve*> curves;
    
    generate_array(curves, t);
    
    vector<Circle*> circles;

    generate_circles(curves, circles);
    
    if (circles.empty()) {
        cout << "Окружностей не сгенерировалось!" << endl;
    } else {
        sort_and_print(circles);
    }
    
    for (const auto& curve : curves) {
           delete curve;
    }
    
    curves.clear();
    circles.clear();

    return 0;
}
