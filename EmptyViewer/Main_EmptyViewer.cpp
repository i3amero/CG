#include <Windows.h>
#include <iostream>
#include <GL/glew.h>
#include <GL/GL.h>
#include <GL/freeglut.h>

#define GLFW_INCLUDE_GLU
#define GLFW_DLL
#include <GLFW/glfw3.h>
#include <vector>

#define GLM_SWIZZLE
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

using namespace glm;

//Set Screen Resolution
const int WIDTH = 512, HEIGHT = 512;//Resolution that assigned in HW1(512 * 512)
const float INF = std::numeric_limits<float>::infinity(); //Float Variable that use to expression infinity

//Ray Class
struct Ray {
    vec3 origin, direction;
    Ray(const vec3& o, const vec3& d) : origin(o), direction(normalize(d)) {}// Set the origin and orientation of the Ray
};

//Surface Class (Abstract Class)
struct Surface {
    virtual bool intersect(const Ray& ray, float& t) const = 0;// Virtual function to check for intersection
};

//Plane Class
struct Plane : public Surface {
    vec3 normal;// normal vector
    float d;// d value of the plane equation
    Plane(const vec3& n, float d) : normal(normalize(n)), d(d) {}

    bool intersect(const Ray& ray, float& t) const override {
        float denom = dot(normal, ray.direction);
        if (fabs(denom) < 1e-6) return false;// Almost parallel, no intersection
        t = -(dot(normal, ray.origin) + d) / denom;
        return t >= 0;
    }
};

//Sphere Class
struct Sphere : public Surface {
    vec3 center;//Center of the Sphere
    float radius;//Radius of the Sphere
    Sphere(const vec3& c, float r) : center(c), radius(r) {}

    bool intersect(const Ray& ray, float& t) const override {
        vec3 oc = ray.origin - center;
        float a = dot(ray.direction, ray.direction);
        float b = 2.0f * dot(oc, ray.direction);
        float c = dot(oc, oc) - radius * radius;
        float discriminant = b * b - 4 * a * c;

        if (discriminant < 0) return false;// No cross if discriminant is less than 0

        float sqrtDiscriminant = sqrtf(discriminant);
        float t0 = (-b - sqrtDiscriminant) / (2.0f * a);
        float t1 = (-b + sqrtDiscriminant) / (2.0f * a);

        if (t0 > 0) t = t0;
        else if (t1 > 0) t = t1;
        else return false;

        return true;
    }
};

//Camera Class
struct Camera {
    vec3 eye, u, v, w; // Location of Camera and Direction Vector
    float l, r, b, t, d;// Viewport Setting

    Camera() : eye(0, 0, 0), u(1, 0, 0), v(0, 1, 0), w(0, 0, 1),
        l(-0.1f), r(0.1f), b(-0.1f), t(0.1f), d(0.1f) {}

    Ray generateRay(float i, float j) {
        float px = l + (r - l) * (i + 0.5f) / WIDTH;
        float py = b + (t - b) * (j + 0.5f) / HEIGHT;
        vec3 direction = -d * w + px * u + py * v;
        return Ray(eye, direction);
    }
};

//Scene Class
struct Scene {
    std::vector<Surface*> objects;// List of objects in the scene
    void addObject(Surface* obj) { objects.push_back(obj); }
    bool trace(const Ray& ray) {
        float closest_t = INF;
        bool hit = false;

        for (auto obj : objects) {
            float t;
            if (obj->intersect(ray, t) && t < closest_t) {
                closest_t = t;
                hit = true;
            }
        }
        return hit;
    }
};

// Function that Renders Scene.
void render(Scene& scene, Camera& camera) {
    std::vector<unsigned char> image(WIDTH * HEIGHT, 0);

    for (int j = 0; j < HEIGHT; ++j) {
        for (int i = 0; i < WIDTH; ++i) {
            Ray ray = camera.generateRay(i, j);
            image[j * WIDTH + i] = scene.trace(ray) ? 255 : 0;
        }
    }

    glDrawPixels(WIDTH, HEIGHT, GL_LUMINANCE, GL_UNSIGNED_BYTE, image.data());
}

int main() {
    if (!glfwInit()) return -1;
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "CG HW1 - Ray Tracer", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glewInit();

    Camera camera;
    Scene scene;
    scene.addObject(new Plane(vec3(0, 1, 0), 2)); //Add Plane
    scene.addObject(new Sphere(vec3(-4, 0, -7), 1)); //Add Sphere S1
    scene.addObject(new Sphere(vec3(0, 0, -7), 2)); //Add Sphere S2
    scene.addObject(new Sphere(vec3(4, 0, -7), 1)); //Add Sphere S3

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        render(scene, camera);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
