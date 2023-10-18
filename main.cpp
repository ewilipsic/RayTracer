#include<iostream>
#include<algorithm>
#include"vec3.h"
#include"collisions.h"
#include"objects.h"

using namespace std;

int main(){
    //getting ratio of img width and img ratio
    auto AspectRatio = 16.0/9.0;
    int image_width = 400;
    int image_height = image_width/AspectRatio;
    image_height = (image_height< 1) ? 1:image_height;

    //getting camera set-up (focal length,eye,center of viewport)

    auto focal_len = 1.0;
    auto viewport_height = 2.0;
    auto viewport_width = 2.0 * static_cast<double>(image_width)/image_height;
    vec3 eye = vec3(0,0,0);

    // getting the vectors to iterate over the pixels

    auto viewport_u = vec3(viewport_width,0,0);
    auto viewport_v = vec3(0,-viewport_height,0);

    auto pixel_delta_u = viewport_u / image_width;
    auto pixel_delta_v = viewport_v / image_height;

    auto viewport_topleft = eye - vec3(0,0,focal_len) - viewport_u/2 - viewport_v/2;
    auto pixel_topleft = viewport_topleft+pixel_delta_u/2 + pixel_delta_v/2;

    // render 

    //open the file and make list 
    ofstream f;
    f.open("image2.ppm",fstream::binary|fstream::out);
    f<<"P6\n"<<image_width<<" "<<image_height<<"\n255\n";
    int numberof_pixel_values = 3*image_height*image_width;
    uint8_t image_pixels[numberof_pixel_values] = {0};
    int pixel_value_index = 0;

    for(int j = 0;j<image_height;j++){
        auto pixel_start = pixel_topleft+pixel_delta_v*j;
        for(int i =0;i<image_width;i++){
            auto pixel = pixel_start + pixel_delta_u*i;
            vec3 dir = pixel - eye;
            ray r = ray(eye,dir);
            for(int o = 0;o<s;o++){
                double t = sphere_collision(sphere_cen[o],sphere_r[o],r);
                ts[o] = t;
            }
            int min_index = 0;
            for(int o = 0;o<s;o++){
                if(ts[o]<ts[min_index]){
                    min_index = o;
                }
            }
            if(ts[min_index]!=__DBL_MAX__){
                r.color = sphere_col[min_index];
            }
            else{
                r.color = vec3(0,0,0);
                
            }
            image_pixels[pixel_value_index] = static_cast<uint8_t>(255.999 * r.color.x);
            image_pixels[pixel_value_index+1] = static_cast<uint8_t>(255.999 * r.color.y);
            image_pixels[pixel_value_index+2] = static_cast<uint8_t>(255.999 * r.color.z);
            pixel_value_index += 3;

        }
    }
//write to file
f.write((char*) &image_pixels,numberof_pixel_values);
cout<<"done";
}