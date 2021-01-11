# Image Filter
Simple image filter in C++ based on an individual school task by DI Florian Ivenz<br>
Available effects:
>+ Sharpen
>+ Box blur
>+ Gaussian blur <br>

References: https://en.wikipedia.org/wiki/Kernel_(image_processing)

Screenshots (Identity, Sharpen, Box blur, Gaussian Blur): <br>
![Identity](/ImageFilter/ressources/Identity.png?raw=true)
![Sharpen](/ImageFilter/ressources/Sharpen.png?raw=true)
![Box blur](/ImageFilter/ressources/BoxBlur.png?raw=true)
![Gaussian blur](/ImageFilter/ressources/GaussianBlur.png?raw=true)

## License
This project is under the MIT license. For full license text see LICENCE.txt
## Building
This project uses premake as build system.
Run the following command to generate project files for your preferred build system:

    premake5 <project-type>

premake5 allows your to generate project files for a number of build systems: Visual Studio, GNU Make, Xcode, Code::Blocks, and more across Windows, Mac OS X, and Linux.
<br>
Once the projects have generated without errors, you may use them to build the project.
## Third Party Libraries
* [Premake5](https://premake.github.io/) 
* [stb_image, stb_image_write](https://github.com/nothings/stb)
