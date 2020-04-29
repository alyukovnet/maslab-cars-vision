# maslab-cars-vision
Detecting problems with camera and maintaining cars functioning.

## Build
### Requirements
1) g++ compiler
2) CMake
3) OpenCV 4.2.0
```
git clone https://github.com/alyukovnet/maslab-cars-vision.git
cd maslab-cars-vision
cmake .
cmake --build
```
> Set flag `CMAKE_CXX_FLAGS` to `-static-libstdc++` for integrate g++ libs in executable file
## Run

```
Usage: main [params] input 

        -?, -h, --help, --usage (value:true)
                Print this message
        --flip
                Rotate 180°
        --flip-x
                Flip Horizontal
        --flip-y
                Flip Vertical
        --log
                Name for log file
        -r, --repeat
                Repeat after end of the video
        --rotate (value:0)
                Rotate +-90° CW

        input
                Path to input video (required)
```
Example: `./bin/main video.mp4 --rotate=90 -r`

### Hot keys
| Key | Value                        |
|-----|------------------------------|
| `q` | Quit                         |