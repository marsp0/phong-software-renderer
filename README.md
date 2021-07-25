[![Build](https://github.com/marsp0/software-renderer/actions/workflows/build.yml/badge.svg)](https://github.com/marsp0/software-renderer/actions/workflows/build.yml)

# Software Renderer

### Dependencies

- SDL2 `apt install libsdl2-dev`

## References

### General

- [Scratchapixel](https://www.scratchapixel.com/)
- [Software Renderer by Angelo1211](https://github.com/Angelo1211/SoftwareRenderer)
- [Software Renderer by Zauonlok](https://github.com/zauonlok/renderer)
- [Software Renderer by Ssloy](https://github.com/ssloy/tinyrenderer)

### Math

- General Matrix Knowledge - any linear algebra book
- [Quaternions 1](https://en.wikipedia.org/wiki/Quaternion)
- [Quaternions 2](https://en.wikipedia.org/wiki/Quaternions_and_spatial_rotation#Proof_of_the_quaternion_rotation_identity)
- [Quaternions 3](http://graphics.stanford.edu/courses/cs348a-17-winter/Papers/quaternion.pdf)
- [Quaternions 4](https://fgiesen.wordpress.com/2019/02/09/rotating-a-single-vector-using-a-quaternion/)
- [Quaternions 5](https://www.3dgep.com/understanding-quaternions/)
- [Quaternions 6](http://www.neil.dantam.name/note/dantam-quaternion.pdf)
- [Matrix Inversion - Gauss Jordan](https://en.wikipedia.org/wiki/Gaussian_elimination#Pseudocode)
- [Matrix Inversion - GLU implementation](https://stackoverflow.com/questions/1148309/inverting-a-4x4-matrix)
- Note that the below was not actually implemented as from what i found LU decomposition (crout/doolittle) does not work in all invertible cases.
    - [Matrix Inversion - LU decomposition 1](https://en.wikipedia.org/wiki/LU_decomposition)
    - [Matrix Inversion - LU decomposition 2](https://www.cl.cam.ac.uk/teaching/1314/NumMethods/supporting/mcmaster-kiruba-ludecomp.pdf)
    - [Matrix Inversion - LU decomposition 3](https://www.youtube.com/watch?v=rhNKncraJMk)
    - [Matrix Inversion - LU decomposition 4](http://www.mymathlib.com/matrices/linearsystems/doolittle.html)
    - [Matrix Inversion - LU decomposition calc 1](https://www.atozmath.com/MatrixEv.aspx?q=doolit&q1=1%2c2%2c3%2c4%3b5%2c6%2c7%2c8%3b9%2c1%2c3%2c3%3b4%2c5%2c6%2c6%60doolit%60&dm=D&dp=8&do=1#PrevPart) - shows different methods
    - [Matrix Inversion - LU decomposition calc 2](https://keisan.casio.com/exec/system/15076953047019#) - i think this one uses gauss elimination variant instead of crout/doolittle

### Drawing a line

- [The Bresenham Line-Drawing Algorithm](https://www.cs.helsinki.fi/group/goa/mallinnus/lines/bresenh.html)
- [Computer Graphics from Scratch - Lines](https://www.gabrielgambetta.com/computer-graphics-from-scratch/06-lines.html)
- [Another article on Bresenham algorithm](http://www.sunshine2k.de/coding/java/Bresenham/RasterisingLinesCircles.pdf)

### Drawing a triangle

- [A Parallel Algorithm for Polygon Rasterization](https://www.cs.drexel.edu/~david/Classes/Papers/comp175-06-pineda.pdf)
- [Barycentric Coordinates 1](https://fgiesen.wordpress.com/2013/02/06/the-barycentric-conspirac/)
- [Barycentric Coordinates 2](https://users.csc.calpoly.edu/~zwood/teaching/csc471/2017F/barycentric.pdf)
- [Barycentric Coordinates 3](https://www.scratchapixel.com/lessons/3d-basic-rendering/rasterization-practical-implementation/rasterization-stage)
- [Perspective correct interpolation](https://www.scratchapixel.com/lessons/3d-basic-rendering/rasterization-practical-implementation/perspective-correct-interpolation-vertex-attributes)
- [Triangle rasterization in practice](https://fgiesen.wordpress.com/2013/02/08/triangle-rasterization-in-practice/)

### Orientation

- Euler Angles (Proper Euler and Tait–Bryan)
- [Euler Angles 1](https://en.wikipedia.org/wiki/Euler_angles)
- [Euler Angles 2](https://adipandas.github.io/posts/2020/02/euler-rotation/)
- [Euler Angles 3](https://www.geometrictools.com/Documentation/EulerAngles.pdf)
- [Euler Angles 4](https://math.stackexchange.com/questions/4199481/rotation-matrices-for-euler-angles)
- [Rotation Calculator](https://www.andre-gaschler.com/rotationconverter/)
- [Rotations 1](https://www.cs.utexas.edu/~theshark/courses/cs354/lectures/cs354-14.pdf)
- [Rotations 2](https://en.wikipedia.org/wiki/Rotation_matrix)
- [Rotations 3](https://ntrs.nasa.gov/api/citations/19770024290/downloads/19770024290.pdf)
- Quaternions - see the Math secion
- [Axis-Angle 1](https://en.wikipedia.org/wiki/Axis%E2%80%93angle_representation)
- [Axis-Angle 2](https://en.wikipedia.org/wiki/Rodrigues%27_rotation_formula)
- [Conversions between representations - Three.js source](https://github.com/mrdoob/three.js/)
- [Conversion between representations](https://en.wikipedia.org/wiki/Rotation_formalisms_in_three_dimensions)