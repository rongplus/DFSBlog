1. Image
    a, Save a docker image
     - docker save -o d:/u.zip ubuntu:latest
    b, pull a image

2. Container
    a, Create container
        run a docker image with share folder as a new container
 - docker run -it --name="U1"  -v D:/git/rong.plus/cppblog:/mycpp ubuntu bash
 - docker run -it --name="dev" -v D:/git/rong.plus/cppblog:/mycpp my_dev bash

- docker run -it --name="dev" -v D:/git/rong.plus/cppblog:/mycpp my_dev bash -p 3306:3306 -p 3308:3308


4. Run from a yml
    docker-compose -f aa.yml up -d
