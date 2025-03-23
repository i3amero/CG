202011378 차현준
Computer Graphics HW Repository

--HW1 Description-</br>
It can be run without the need to install an additional separate library.</br>

Differences between pseudocode and implementation code</br>

1. Rendering Differences (Ray Tracing vs Rasterization)</br>
Pseudocode: Examine collisions with objects by emitting light rays per pixel (light tracking, ray tracing method).</br>
OpenGL Code: A method of drawing the results of Ray Tracking using glDrawPixels directly, rather than a rasterization method that utilizes Z-buffer operations based on triangles.</br>
In other words, it uses OpenGL but is implementing ray tracing rather than rasterization.</br>

2. Differences in the way light is generated</br>
a doctor's code</br>
Call camera.getRay(ix, iy) to generate a ray from the camera.</br>
A process exists to calculate the direction of the light rays, but no specific formula exists.</br>
OpenGL Code</br>
Create a ray using generateRay(i,j) in the Camera class.</br>
Official:</br>
𝑑𝑖𝑟𝑒𝑐𝑡𝑖𝑜𝑛=−𝑑⋅𝑤+𝑝𝑥⋅𝑢+𝑝𝑦⋅𝑣</br>
direction=−d⋅w+px⋅u+py⋅v</br>
px, py: Calculate the in-plane position based on pixel coordinates.</br>
w: The direction vector of the camera.</br>
u, v: X and Y direction vectors of the camera.</br>
Produced and launched a ray for each pixel through the formula above.</br>
Conclusion: Camera::generateRay() of OpenGL code is more clearly and mathematically organized than pseudo code.</br>

3. Ray-Object Intersection</br>
a doctor's code</br>
Call scene.trace (ray, 0, +inf) to check for collisions between rays and objects in the scene.</br>
Checked surfs.intersect (ray, tMin, tMax) for collisions.</br>
OpenGL Code</br>
at Scene::trace(ray)</br>
Check for conflicts with all objects in the std::vector<Surface*> objects list.</br>
Invoke intercept (ray, t) to find the nearest collision object.</br>
The method of implementation of Sphere::intersect(), Plane::intersect() is specifically included in the OpenGL code.</br>
Conclusion:</br>
The pseudocode simply calls intercept(), but the OpenGL code directly implements the cross-examination of Sphere and Plane in detail.</br>
OpenGL code is more specifically handling crash detection.</br>

4. Result Rendering Differences</br>
a doctor's code</br>
Set the pixel by calling image.set (ix, iy, c).</br>
This part corresponds to OpenGL code.</br>
OpenGL Code</br>
std::vector<unsigned char> image(WIDTH * HEIGHT, 0);</br>
Create an image buffer to store pixel data.</br>
glDrawPixels(WIDTH, HEIGHT, GL_LUMINANCE, GL_UNSIGNED_BYTE, image.data());</br>
Output pixel data directly to the screen using glDrawPixels().</br>
Direct pixel manipulation instead of the usual rasterization method of OpenGL.</br>
Conclusion: The method of manipulating pixels directly from OpenGL code to glDrawPixels() corresponds to the image.set() in the pseudocode.
</br>

Result Screenshot</br></br>
![image](https://github.com/user-attachments/assets/cb66453d-6caf-4675-a21f-459cc763efa5)
