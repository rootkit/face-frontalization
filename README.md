# face-frontalization


##### Dependencies of the project:
The project has 2 major dependencies :
```sh
    1. openCV   >= 3.0.0
    2. dLib     >= 18.17
```
If these libraries aren't present in your machine, please install them first.
NOTE: If the dlib library in your machine isn't in `/usr/include`, then either
change its location or the linking code line in Makefile.

##### About :
The project is based on the paper :
```sh
    "Effective Frontalization in Unconstrained Images"
    by : "Tal Hassner, Shai Harel, Eran Paz and Roee Enbar"
```


###### Notes:
The model used in the project is the model3Ddlb.mat provided in the paper's source
code. In order to play around with other models or to create your own model (see model3DFivePoints.mat),
convert the mat files to yaml files and provide their location while running the project.
