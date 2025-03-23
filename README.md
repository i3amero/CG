202011378 차현준
Computer Graphics HW Repository

--HW1 Description-
It can be run without the need to install an additional separate library.

Differences between pseudocode and implementation code

1. Rendering Differences (Ray Tracing vs Rasterization)
Pseudocode: Examine collisions with objects by emitting light rays per pixel (light tracking, ray tracing method).
OpenGL Code: A method of drawing the results of Ray Tracking using glDrawPixels directly, rather than a rasterization method that utilizes Z-buffer operations based on triangles.
In other words, it uses OpenGL but is implementing ray tracing rather than rasterization.

2. Differences in the way light is generated
a doctor's code
Call camera.getRay(ix, iy) to generate a ray from the camera.
A process exists to calculate the direction of the light rays, but no specific formula exists.
OpenGL Code
Create a ray using generateRay(i,j) in the Camera class.
Official:
𝑑𝑖𝑟𝑒𝑐𝑡𝑖𝑜𝑛=−𝑑⋅𝑤+𝑝𝑥⋅𝑢+𝑝𝑦⋅𝑣
direction=−d⋅w+px⋅u+py⋅v
px, py: Calculate the in-plane position based on pixel coordinates.
w: The direction vector of the camera.
u, v: X and Y direction vectors of the camera.
Produced and launched a ray for each pixel through the formula above.
Conclusion: Camera::generateRay() of OpenGL code is more clearly and mathematically organized than pseudo code.

3. Ray-Object Intersection
a doctor's code
Call scene.trace (ray, 0, +inf) to check for collisions between rays and objects in the scene.
Checked surfs.intersect (ray, tMin, tMax) for collisions.
OpenGL Code
at Scene::trace(ray)
Check for conflicts with all objects in the std::vector<Surface*> objects list.
Invoke intercept (ray, t) to find the nearest collision object.
The method of implementation of Sphere::intersect(), Plane::intersect() is specifically included in the OpenGL code.
Conclusion:
The pseudocode simply calls intercept(), but the OpenGL code directly implements the cross-examination of Sphere and Plane in detail.
OpenGL code is more specifically handling crash detection.

4. Result Rendering Differences
a doctor's code
Set the pixel by calling image.set (ix, iy, c).
This part corresponds to OpenGL code.
OpenGL Code
std::vector<unsigned char> image(WIDTH * HEIGHT, 0);
Create an image buffer to store pixel data.
glDrawPixels(WIDTH, HEIGHT, GL_LUMINANCE, GL_UNSIGNED_BYTE, image.data());
Output pixel data directly to the screen using glDrawPixels().
Direct pixel manipulation instead of the usual rasterization method of OpenGL.
Conclusion: The method of manipulating pixels directly from OpenGL code to glDrawPixels() corresponds to the image.set() in the pseudocode.


Result Screenshot
![image](https://github.com/user-attachments/assets/cb66453d-6caf-4675-a21f-459cc763efa5)
