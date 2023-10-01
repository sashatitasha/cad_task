#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

namespace geometry {
    class Curve {
    public:
        virtual double get_radius() const = 0;
        virtual double get_step() const = 0;
        virtual vector<double> get_point(double t) const = 0;
        virtual vector<double> get_der(double t) const = 0;
        virtual ~Curve() {};
        virtual string class_name() const = 0;
    };

    class Circle : public Curve {
        double radius;
    public:
        Circle(double r) {
            radius = r;
        }
        
        string class_name() const override {
            return "Circle";
        }

        double get_radius() const override {
            return radius;
        }

        double get_step() const override {
            return 0.0;
        }

        vector<double> get_point(double t) const override {
            vector<double> point;
            point.push_back(radius * cos(t));
            point.push_back(radius * sin(t));
            point.push_back(0.0);
            
            return point;
        }

        vector<double> get_der(double t) const override {
            vector<double> der;
            der.push_back(-radius * sin(t));
            der.push_back(radius * cos(t));
            der.push_back(0.0);
            
            return der;
        }
    };

    class Ellipse : public Curve {
        double radius_x;
        double radius_y;
    public:
        Ellipse(double r_x, double r_y) {
            radius_x = r_x;
            radius_y = r_y;
        }
        
        string class_name() const override {
            return "Ellipse";
        }

        double get_radius() const override {
            return max(radius_x, radius_y);
        }

        double get_step() const override {
            return 0.0;
        }

        vector<double> get_point(double t) const override {
            vector<double> point;
            point.push_back(radius_x * cos(t));
            point.push_back(radius_y * sin(t));
            point.push_back(0.0);
            
            return point;
        }

        vector<double> get_der(double t) const override {
            vector<double> der;
            der.push_back(-radius_x * sin(t));
            der.push_back(radius_y * cos(t));
            der.push_back(0.0);
            
            return der;
        }
    };

    class Helix : public Curve {
        double radius;
        double step;

    public:
        Helix(double r, double s) {
            radius = r;
            step = s;
        }
        
        string class_name() const override {
            return "Helix";
        }

        double get_radius() const override {
            return radius;
        }

        double get_step() const override {
            return step;
        }

        vector<double> get_point(double t) const override {
            vector<double> point;
            point.push_back(radius * cos(t));
            point.push_back(radius * sin(t));
            point.push_back(step * t / (2 * M_PI));
            
            return point;
        }

        vector<double> get_der(double t) const override {
            vector<double> der;
            der.push_back(-radius * sin(t));
            der.push_back(radius * cos(t));
            der.push_back(step / (2 * M_PI));
            
            return der;
        }
    };
};
