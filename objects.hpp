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

    inline const char* hit_type(int i){
        if (i<s){
            return "sphere";
        }
    }

    void raytracesample(ray& sample){
        double a = (sample.dir.unitvector().y + 1)*0.5; 
        int min_index = 0;
        double min_t = __DBL_MAX__;
        for(int i = 0;i<s;i++){
            double t = sphere_collision(sphere_cen[i],sphere_r[i],sample);
            if(t<min_t){
                min_t = t;
                min_index = i;
            }
        }
        auto HitType = hit_type(min_index);
        if (min_t != __DBL_MAX__){
            vec3 outward_normal;
            if (HitType == "sphere"){
                outward_normal = sample.point(min_t) - sphere_cen[min_index];
            }
            vec3 child_ray = sample.point(min_t)+random_sphere();
            if(dot(outward_normal,child_ray)<0){
                child_ray = child_ray*-1;
            }
            
        }
        //(min_t == __DBL_MAX__) ? sample.color = vec3(1,1,1)*a+vec3(0,0,1)*(1-a) : sample.color = sphere_col[min_index];
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

    vec3 random_sphere(){
        while (true)
        {
            vec3 randvec(random_double()*2 -1,random_double()*2 - 1,random_double()*2 - 1) ;
            if(randvec.length()<=1){
                return randvec.unitvector();
            }
        }
        
    }





};

World world;


