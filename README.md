# maslab-cars-vision
Detecting problems with camera and maintaining cars functioning.

## Build
### Requirements
1) g++ compiler
2) CMake
3) OpenCV 4.2.0
```
git clone https://github.com/alyukovnet/maslab-cars-vision.git
cmake .
make
```

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

### Hot keys
| Key | Value                        |
|-----|------------------------------|
| `l` | Switch Color model (RGB/Lab) |
| `q` | Quit                         |