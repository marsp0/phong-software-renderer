[![Build](https://github.com/marsp0/software-renderer/actions/workflows/build.yml/badge.svg)](https://github.com/marsp0/software-renderer/actions/workflows/build.yml)

# Software Renderer

### Dependencies

- SDL2

## References

### General

- [Scratchapixel](https://www.scratchapixel.com/)
- [Software Renderer by Angelo1211](https://github.com/Angelo1211/SoftwareRenderer)
- [Software Renderer by Zauonlok](https://github.com/zauonlok/renderer)
- [Software Renderer by Ssloy](https://github.com/ssloy/tinyrenderer)
- [Learn OpenGL](https://learnopengl.com/)
- [OpenGL 4.4 - Spec](https://www.khronos.org/registry/OpenGL/specs/gl/glspec44.core.pdf)

### Books

- [Mathematics for 3D Game Programming and Computer Graphics, Third Edition](https://www.amazon.com/Mathematics-Programming-Computer-Graphics-Third/dp/1435458869)
- [Fundamentals of Computer Graphics](https://www.amazon.com/Fundamentals-Computer-Graphics-Peter-Shirley/dp/1568814690)
- [Free Linear Algebra Book](https://joshua.smcvt.edu/linearalgebra/book.pdf)

### Math

- [Change of Basis vs Linear Transformation](http://boris-belousov.net/2016/05/31/change-of-basis/)
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
- [Triangle rasterization in practice](https://fgiesen.wordpress.com/2013/02/08/triangle-rasterization-in-practice/)

### Orientation

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

### Camera

- [Scratch a pixel - Volumne 1](https://www.scratchapixel.com/index.php?redirect)
- [Lookat derivation (Camera space -> World space)](https://www.scratchapixel.com/lessons/mathematics-physics-for-computer-graphics/lookat-function)
- [Lookat derivation (World space -> Camera space)](http://www.songho.ca/opengl/gl_camera.html)
- [View matrix derivation](https://www.mauriciopoppe.com/notes/computer-graphics/viewing/view-transform/)
- [Perspective projection derivation](https://www.scratchapixel.com/lessons/3d-basic-rendering/perspective-and-orthographic-projection-matrix/building-basic-perspective-projection-matrix)
- [Perspective projection derivation (OpenGL)](https://www.scratchapixel.com/lessons/3d-basic-rendering/perspective-and-orthographic-projection-matrix/opengl-perspective-projection-matrix)
- [Free camera](https://learnopengl.com/Getting-started/Camera)
- [Euler to direction vector (explains the LearnOpenGL article formula)](https://math.stackexchange.com/questions/1791209/euler-angle-to-direction-vector-which-is-right)

### Z-Buffer

- [Scratchapixel article](https://www.scratchapixel.com/lessons/3d-basic-rendering/rasterization-practical-implementation/perspective-correct-interpolation-vertex-attributes)
- [Perspective correct interpolation](https://stackoverflow.com/questions/24441631/how-exactly-does-opengl-do-perspectively-correct-linear-interpolation)
- OpenGL Spec linked in the general references also has the perspective correct formula

### OBJ + TGA Parser

- [OBJ Spec](http://paulbourke.net/dataformats/obj/)
- [MTL Spec](http://www.paulbourke.net/dataformats/mtl/)
- [TGA Spec](http://paulbourke.net/dataformats/tga/)
- [TGA Spec 2](https://misc.ryanjuckett.com/downloads/TGA_FileFormat.pdf)
- [Endianness](https://en.wikipedia.org/wiki/Endianness)
- [Convert bytes -> int](https://gist.github.com/rolfwr/e3e4223b887476bd9bbdab1ec29f30b4)
- [Convert char -> unsigned char](https://stackoverflow.com/a/5042335)
- [Convert char -> unsigned char 2](https://stackoverflow.com/a/43273907)
- [reinterpret_cast](https://en.cppreference.com/w/cpp/language/reinterpret_cast)
- [OBJ texture ref point](https://stackoverflow.com/questions/5585368/problems-using-wavefront-objs-texture-coordinates-in-android-opengl-es/5605027#5605027)
- [OBJ texture problem](https://stackoverflow.com/questions/8837328/troubles-parsing-wavefront-obj-texture-coordinates)

### Texture Mapping

- [Texture Mapping chapter from Fundamentals of Computer Graphics]
- [Texture Mapping chapter from Mathematics for 3D Game Programming and Computer Graphics]
- [Chris Hecker on Texture Mapping](http://www.chrishecker.com/Miscellaneous_Technical_Articles)
- [Perspective correct texture mapper](http://www.lysator.liu.se/~mikaelk/doc/perspectivetexture/)
- [Texture Filtering](https://en.wikipedia.org/wiki/Texture_filtering)
- [Texture Mapping](https://en.wikipedia.org/wiki/Texture_mapping)
- [OBJ Texture Coords use (0,0) as top left](https://stackoverflow.com/questions/5585368/problems-using-wavefront-objs-texture-coordinates-in-android-opengl-es/5605027#5605027)
- [Perspective correct interpolation 1](https://www.scratchapixel.com/lessons/3d-basic-rendering/rasterization-practical-implementation/perspective-correct-interpolation-vertex-attributes)
- [Perspective correct interpolation 2](https://stackoverflow.com/questions/24441631/how-exactly-does-opengl-do-perspectively-correct-linear-interpolation)

### Culling

- [Backface Culling](https://en.wikipedia.org/wiki/Back-face_culling)
- [Frustum Culling](https://learnopengl.com/Guest-Articles/2021/Scene/Frustum-Culling)