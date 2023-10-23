#pragma once
#include"camera.hpp"
#include<cstdlib>

class World{
    public:

    int samples  = 100;

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

    inline double random_double() {
        return rand() / (RAND_MAX + 1.0);
    }

    void raytracesample(ray& sample){
        int min_index = 0;
        double min_t = __DBL_MAX__;
        for(int i = 0;i<s;i++){
            double t = sphere_collision(sphere_cen[i],sphere_r[i],sample);
            if(t<min_t){
                min_t = t;
                min_index = i;
            }
        }
        (min_t == __DBL_MAX__) ? sample.color = vec3() : sample.color = sphere_col[min_index];
    }

    void raytrace(ray& r){
        vec3 color;
        for(int i = 0;i<samples;i++){
            vec3 start = r.start;
            vec3 dir = r.dir + camera.pixel_delta_u*(-0.5+random_double())+camera.pixel_delta_v*(-0.5+random_double());
            ray smpl(r.start,dir);
            raytracesample(smpl);
            color = color + smpl.color;
        }
        r.color = color/samples;
    }






};

World world;


