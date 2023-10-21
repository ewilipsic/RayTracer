#pragma once
#include"vec3.hpp"

class World{
    public:

    // spheres  (s)
    #define s 2

    vec3 sphere_cen[s] = {vec3(0,1,-1),vec3(0,0,-2)};
    double sphere_r[s] = {0.5,1.3};
    vec3 sphere_col[s] = {vec3(1.0,1.0,1.0),vec3(0,0,1.0)};

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

    // world.raytrace
    void raytrace(ray& r){
        int min_index = 0;
        double min_t = __DBL_MAX__;
        for(int i = 0;i<s;i+=2){
            double t = sphere_collision(sphere_cen[i],sphere_r[i],r);
            if(t<min_t){
                min_t = t;
                min_index = i;
            }
        }
        r.color = sphere_col[min_index];
    }    

         
};

World world;


//s
