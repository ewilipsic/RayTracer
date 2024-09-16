#pragma once
#include<math.h>
#include<fstream>
class vec3
{
public:
    double x,y,z;
    vec3(double X = 0,double Y = 0,double Z = 0){
        x=X;
        y=Y;
        z=Z;
    }
    // operator here
    vec3 operator+(const vec3& other) const {
        return vec3(x+other.x,y+other.y,z+other.z);
    }
    vec3 operator*(const double i) const{
        return vec3(x*i,y*i,z*i);
    
    }
     vec3 operator/(const double i) const{
        return vec3(x/i,y/i,z/i);
    
    }
    vec3 operator-(const vec3& other) const {
        return vec3(x-other.x,y-other.y,z-other.z);
    }
    // utility functions here
        double length(){
        return sqrt(x*x + y*y + z*z);
    }
    vec3 unitvector(){
        return vec3(x,y,z)/length();
    }
    void write_color(std::ostream &out) {
    out << static_cast<int>(255.999 * x) << ' '
        << static_cast<int>(255.999 * y) << ' '
        << static_cast<int>(255.999 * z) << '\n';
    }
    void write_vec3(std::ostream &out) {
    out << x << ' '
        << y << ' '
        << z << '\n';
    }
    //static
    
    static vec3 zero(){
        return(vec3(0,0,0));
    }
};
vec3 vecmult(const vec3& first,const vec3& other){
    return vec3(first.x*other.x,first.y*other.y,first.z*other.z);
} 
double dot(const vec3& first,const vec3& other){
        return first.x*other.x + first.y*other.y + first.z*other.z;
    }



class ray
{
public:
    vec3 start,dir;
    vec3 color;
    ray(){}
    ray(vec3 s ,vec3 d){
        start = s;
        dir = d;
    }
    vec3 point(double i) const {
        return start + dir*i;
    }
};
