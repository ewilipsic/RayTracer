#pragma once
#include"vec3.h"
#include"math.h"

//sphere

double sphere_collision(const vec3& center,double r,const ray& i_ray){
    vec3 sc = i_ray.start - center;
    double a =  dot(i_ray.dir,i_ray.dir);
    double b  = dot(i_ray.dir,sc);
    double c = dot(sc,sc) - r*r;
    double discrimant = b*b - a*c;
    if (discrimant > 0){
        return ((-b-sqrt(discrimant))/a);
    }
    else{
        return (__DBL_MAX__);
    }
}