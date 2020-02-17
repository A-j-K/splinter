# Docker Image to compile/build the source code

```
$ ./build.sh
$ docker run -v `pwd`:/root -it splinter-build bash
# mkdir build
# cd build
# cmake -DSPLINTER_TESTS=ON ..
# make
# make test
```

