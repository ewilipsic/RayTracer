#include"vec3.hpp"

class camera{
    public:

    int image_height,image_width;
    double AspectRatio = 16.0/9.0;

    double viewport_width,viewport_height;
    vec3 focal_vec;
    vec3 eye;

    vec3 pixel_delta_u,pixel_delta_v,pixel_topleft;

    void initialize(int a_image_width = 400,double a_viewport_height = 2.0,
    vec3 a_eye = vec3(0,0,0),vec3 a_focal_vec = vec3(0,0,-1)){

        // setting member variables to the a_

        image_width = a_image_width;
        viewport_height = a_viewport_height;
        eye = a_eye;
        focal_vec = a_focal_vec;

        //getting other member variables

        image_height = image_width/AspectRatio;
        image_height = (image_height< 1) ? 1:image_height;

        viewport_width = viewport_height * static_cast<double>(image_width)/image_height;

        // getting the vectors to iterate over the pixels

        vec3 viewport_u = vec3(viewport_width,0,0);
        vec3 viewport_v = vec3(0,-viewport_height,0);

        pixel_delta_u = viewport_u / image_width;
        pixel_delta_v = viewport_v / image_height;

        vec3 viewport_topleft = eye + focal_vec - viewport_u/2 - viewport_v/2;
        pixel_topleft = viewport_topleft+pixel_delta_u/2 + pixel_delta_v/2;

    }

};