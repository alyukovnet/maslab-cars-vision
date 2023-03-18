# maslab-cars-vision
Detecting problems with camera and maintaining cars functioning.

[DEMO VIDEO](https://www.youtube.com/watch?v=PdSda2QE1yg&t=38s)

[PUBLICATION](https://ceur-ws.org/Vol-2893/paper_18.pdf)

## Build
### Requirements
1) g++ compiler
2) CMake
3) OpenCV 4.2.0
4) Qt 5.14.2
```
git clone https://github.com/alyukovnet/maslab-cars-vision.git
cd maslab-cars-vision
cmake .
cmake --build
```
## Run
#### Run using Qt interface:
```
./bin/maslab-cars-vision
```
#### Run using HighGui by OpenCV: (deprecated)
```
./bin/main [params] input
```
| Parameter               | Description                   |
|-------------------------|-------------------------------|
| -?, -h, --help, --usage | Print help message            |
| --flip                  | Rotate 180°                   |
| --flip-x                | Flip Horizontal               |
| --flip-y                | Flip Vertical                 |
| --log                   | Name for log file             |
| -r, --repeat            | Repeat after end of the video |
| --rotate                | Rotate +-90° CW (default: 0)  |

Example: `./bin/main video.mp4 --rotate=90 -r`

| Hot key | Value                        |
|---------|------------------------------|
| `q`     | Quit                         |
