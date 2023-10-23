#include<iostream>
#include<algorithm>
#include"camera.hpp"
#include"objects.hpp"


using namespace std;

int main(){

    camera.initialize();
    // render 

    //open the file and make list 
    ofstream f;
    f.open("image.ppm",fstream::binary|fstream::out);
    f<<"P6\n"<<camera.image_width<<" "<<camera.image_height<<"\n255\n";
    int numberof_pixel_values = 3*camera.image_height*camera.image_width;
    uint8_t image_pixels[numberof_pixel_values] = {0};
    int pixel_value_index = 0;

    for(int j = 0;j<camera.image_height;j++){
        auto pixel_start = camera.pixel_topleft+camera.pixel_delta_v*j;
        for(int i =0;i<camera.image_width;i++){

            auto pixel = pixel_start + camera.pixel_delta_u*i;
            vec3 dir = pixel - camera.eye;
            ray r = ray(camera.eye,dir);


            world.raytrace(r);


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