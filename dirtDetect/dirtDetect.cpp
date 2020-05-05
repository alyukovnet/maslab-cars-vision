#include "dirtDetect.h"

DirtDetect::DirtDetect()
{
    srand(time(NULL));
    rng(time(NULL));
}

DirtDetect::~DirtDetect()
{
}

int DirtDetect::detectDirt(Mat frame)
{
    if (framel.empty())
    {
        cvtColor(frame, framel, COLOR_BGR2GRAY);

        x = frame.cols;
        y = frame.rows;
        return 0;
    }
    cvtColor(frame, tmpFrame, COLOR_BGR2GRAY);
    // Display the resulting frame
    tmpFrame *= 0.8;
    absdiff(tmpFrame, framel, dFrame);
    framel = dFrame;
    // imshow("Frame11", dFrame);
    threshold(dFrame, dFrame1, 5, 255, THRESH_BINARY);
    threshold(dFrame, dFrame2, 252, 255, THRESH_BINARY);
    threshold(dFrame, dFrame, 10, 255, THRESH_BINARY);

    dFrame1 = (255 - dFrame1) + dFrame2;

    // imshow("Frame12", dFrame1);
    int nonzeros = countNonZero(dFrame1);
    //cout<<nonzeros<<endl;
    //cout<<x * y * dirtThreshold<<endl;
    
    if (x * y * dirtThreshold < nonzeros)
    {
        draw_l(frame,dFrame1);
        return 1;
    }
    return 0;
}
void DirtDetect::show()
{
    if (dFrame.empty())
    {
        return;
    }
    imshow("Frame", dFrame1);
}
Mat DirtDetect::derter(Mat frame, int dirt,int dirtc)
{
    if (dirtlay.empty()||dirtc!=count)
    {
        count=dirtc;
        dirtlay=Mat::zeros( frame.size(), frame.type() );
        for (int i = 0; i < count; i++)
        {
        int r=rng.uniform(5,50);
        circle(dirtlay, Point(rng.uniform(100,frame.cols-200), rng.uniform(100,frame.rows-200)), r, Scalar(255, 255, 255), r*2, 0);
        blur(dirtlay, dirtlay, Size(50, 50), Point(-1, -1));
        }
        
    
    }
    //imshow("Frame1", dirtlay);
    return frame - (dirtlay * dirt / 100);
}
void DirtDetect::draw(Mat gray,Mat src)
{
    
    vector<Vec3f> circles;
GaussianBlur( gray, gray, Size(15, 15), 2, 2 );
    HoughCircles(gray, circles, HOUGH_GRADIENT, 1,
                 gray.rows / 16, // change this value to detect circles with different distances to each other
                 100, 30, 25, 1000  // change the last two parameters
                                 // (min_radius & max_radius) to detect larger circles
    );
    for (size_t i = 0; i < circles.size(); i++)
    {
        Vec3i c = circles[i];
        Point center = Point(c[0], c[1]);
        // circle center
        circle(src, center, 1, Scalar(0, 100, 100), 3, LINE_AA);
        // circle outline
        int radius = c[2];
        circle(src, center, radius, Scalar(255, 0, 255), 3, LINE_AA);
    }
    imshow("detected circles", src);
    imshow("detected circles1", gray);
}
void DirtDetect::draw_l(Mat src, Mat grey )
{
    GaussianBlur( grey, grey, Size(15, 15), 2, 2 );
    RNG rng(12345);
    Mat canny_output;
    Canny( grey, canny_output, 50, 50*2 );
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    findContours( canny_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE );
    for( size_t i = 0; i< contours.size(); i++ )
    {
        Scalar color = Scalar( 0, 0, 255);
        drawContours( src, contours, (int)i, color, 2, LINE_8, hierarchy, 0 );
    }
    
}
