#pragma once
#include"vec3.hpp"

#define reflective 1
#define diffuse 0

#define p 1
#define s 1

#if s != 0
class Spheres{
    private:
    vec3 sphere_cen[s] = {vec3(0,0,-1)};
    double sphere_r[s] = {0.5};

    double sphere_collision(const vec3& center,double r,const ray& i_ray){
        vec3 sc = i_ray.start - center;
        double a =  dot(i_ray.dir,i_ray.dir);
        double b  = dot(i_ray.dir,sc);
        double c = dot(sc,sc) - r*r;
        double discrimant = b*b - a*c;
        if (discrimant < 0){
            return (__DBL_MAX__);
        }
        if(((-b-sqrt(discrimant))/a)<0){
            return (__DBL_MAX__);
        }
        return ((-b-sqrt(discrimant))/a);
    }

    public:
    vec3 sphere_col[s] = {vec3(1.0,0,0)};
    int sphere_mat[s] = {diffuse};
    double hit(const ray& incident,int* index){
        int min_index = 0;
        double min_t = __DBL_MAX__;
        for(int i = 0;i<s;i++){
            double t = sphere_collision(sphere_cen[i],sphere_r[i],incident);
            if(t<min_t){
                //debug
                min_t = t;
                min_index = i;
            }
        }
        *index = min_index;
        
        return min_t;
    }

    vec3 outnormal(ray const& i_ray,double t,int index){
        return i_ray.point(t) - sphere_cen[index];
    }
};
#else 
class Spheres{
    public:
    vec3 sphere_col[1] = {vec3(0,0,0)};
    int sphere_mat[s] = {diffuse};
    double hit(const ray& incident,int* index){
        *index = 0;
        return __DBL_MAX__;
    }

    vec3 outnormal(ray const& i_ray,double t,int index){
        return vec3(0,0,0);
    }
};
#endif
#undef s

#if p!= 0
class Planes{
    private:
    vec3 plane_n[p] = {vec3(0,1,0)};
    vec3 plane_point[p] = {vec3(0,-1,-1)};

    double
    
     plane_collision(const vec3& normal,const vec3& point,const ray& i_ray){
        double numerator = dot((point-i_ray.start),normal);
        double denominator = dot(i_ray.dir,normal);
        if(denominator == 0){      // because floating point exact zero will be rare so we might want to change that
            return(__DBL_MAX__);
        }
        if (numerator/denominator < 0.001){
            return(__DBL_MAX__);
        }
        return numerator/denominator;
    }

    public:
    vec3 plane_col[p] = {vec3(0,1,0)};
    int plane_mat[p] = {diffuse};
    double hit(const ray& incident,int* index){
        int min_index = 0;
        double min_t = __DBL_MAX__;
        for(int i = 0;i<p;i++){
            double t = plane_collision(plane_n[i],plane_point[i],incident);
            if(t<min_t){
                min_t = t;
                min_index = i;
            }
        }
        *index = min_index;
        return min_t;
    }
    vec3 outnormal(ray const& i_ray,int index){
        if(dot(i_ray.dir,plane_n[index])<0){
            return plane_n[index];
        }
        return plane_n[index]*-1;
    }
};
#else
class Planes{
    public:
    vec3 plane_col[1] = {vec3(0,0,1.0)};
    int plane_mat[p] = {reflective};
    double hit(const ray& incident,int* index){
        *index = 0;
        return __DBL_MAX__;
    }
    vec3 outnormal(ray const& i_ray,int index){
    return vec3(0,0,0);
    }
};

#endif
#undef p

Spheres spheres;
Planes planes;


