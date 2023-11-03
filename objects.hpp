#pragma once
#include"camera.hpp"
#include"geometry.hpp"
#include<cstdlib>

class World{
    public:

    int samples  = 50; //number of rays for anti aliasing
    int max_depth = 5; //maximum number of child rays

    // world.raytrace
    inline double random_double() {
        return rand() / (RAND_MAX + 1.0);
    }

    const char* hit_combined(ray const& incident,int* i,double* min_t){
        int iplane,isphere;
        double tplane,tsphere;
        tsphere = spheres.hit(incident,&isphere);
        tplane = planes.hit(incident,&iplane);
        if(tsphere<=tplane){
            *i = isphere;

            *min_t = tsphere;
            return "sphere";
        }
       else{
            *i = iplane;
            *min_t = tplane;
            return "plane";
        }
    }

    vec3 raytracesample(ray& sample,int depth){
        
        if(depth<0){
            return vec3(0,0,0);
        }
        depth--;
        double hit_t;
        int hit_index;

        const char* hit_type = hit_combined(sample,&hit_index,&hit_t);
        if (hit_t != __DBL_MAX__){
            vec3 outward_normal;
            if (hit_type == "sphere"){
                outward_normal = spheres.outnormal(sample,hit_t,hit_index);
                ray child_ray(sample.point(hit_t),outward_normal.unitvector() + random_sphere());
                return vecmult(raytracesample(child_ray,depth),spheres.sphere_col[hit_index]);
                
            }
            if (hit_type == "plane"){
                outward_normal = planes.outnormal(sample,hit_index);
                ray child_ray(sample.point(hit_t),outward_normal.unitvector() + random_sphere());
                return vecmult(raytracesample(child_ray,depth),planes.plane_col[hit_index]);
            }
        }
        else{
            double a = 0.5*(sample.dir.unitvector().y + 1.0);
            //return vec3(1,1,1)*a+vec3(0,0,1)*(1-a);                   //void color gradient
            return vec3(1,1,1); // void color white
        }
    }

    void raytrace(ray& r){
        vec3 color;
        for(int i = 0;i<samples;i++){
            ray smpl(r.start,r.dir + camera.pixel_delta_u*(-0.5+random_double())+camera.pixel_delta_v*(-0.5+random_double()));
            color = color + raytracesample(smpl,max_depth);
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


