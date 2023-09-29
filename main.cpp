#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/videoio/videoio.hpp>
#include <iostream>
#include <ctime>
#include <cmath>

using namespace cv;
using namespace std;

void draw_random_shape(Mat& image, int width, int height) {
    int shape_type = rand() % 4; 
    int x = rand() % (width - 50); 
    int y = rand() % (height - 50); 
    Scalar color(rand() % 256, rand() % 256, rand() % 256); 
    int size = rand() % 100 + 50; 

    if (shape_type == 0) {
        Rect rect(x, y, size, size);
        rectangle(image, rect, color, -1);
    } else if (shape_type == 1) {
        Point center(x + size / 2, y + size / 2);
        circle(image, center, size / 2, color, -1);
    } else if (shape_type == 2) {
        Point points[1][3];
        points[0][0] = Point(x + size / 2, y);
        points[0][1] = Point(x, y + size);
        points[0][2] = Point(x + size, y + size);
        const Point* ppt[1] = { points[0] };
        int npt[] = { 3 };
        fillPoly(image, ppt, npt, 1, color);
    } else {
        Point points[1][6];
        for (int i = 0; i < 6; i++) {
            double angle = i * 2 * CV_PI / 6;
            int px = x + size / 2 + size / 2 * cos(angle);
            int py = y + size / 2 + size / 2 * sin(angle);
            points[0][i] = Point(px, py);
        }
        const Point* ppt[1] = { points[0] };
        int npt[] = { 6 };
        fillPoly(image, ppt, npt, 1, color);
    }

    string text = "Size: " + to_string(size) + " Cos: " + to_string(cos(size)) + " Sin: " + to_string(sin(size));
    putText(image, text, Point(x, y - 10), FONT_HERSHEY_SIMPLEX, 0.4, Scalar(0, 0, 0), 1, LINE_AA);
}

int main() {
    int width = 800;
    int height = 600;
    int frame_count = 300; 
    VideoWriter video("shapes_video.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'), 30, Size(width, height));

    if (!video.isOpened()) {
        cerr << "Error: Could not open video file." << endl;
        return -1;
    }

    srand(time(0));

    for (int i = 0; i < frame_count; i++) {
        Mat frame(height, width, CV_8UC3, Scalar(255, 255, 255)); 
        draw_random_shape(frame, width, height);

        video.write(frame);

        imshow("Random Shapes Video", frame);
        if (waitKey(30) == 27) { 
            break;
        }
    }

    video.release();
    destroyAllWindows();
    return 0;
}

