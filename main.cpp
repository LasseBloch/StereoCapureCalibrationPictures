#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>


void printHelp()
{
    std::cout << "\nERROR: Wrong number of input parameters\n";
    std::cout << "1. argument should be chessboard width (Remember its the number of inner corners)\n";
    std::cout << "2. argument should be chessboard height\n";
    std::cout << "abort by pressing ESC\n";
    exit(-1);
}


void captureCalibrationImages(int camIndex, int board_w, int board_h)
{
    std::cout << "Calibrating with board_w: " << board_w << " and board_h: " << board_h << std::endl;
    const auto board_n {board_w * board_h};
    const cv::Size board_sz{board_w, board_h};
    int chessboardNum{0};

    cv::VideoCapture cam(camIndex);
    if (!cam.isOpened())
    {
        std::cout << "Could not open the camera\n";
        printHelp();
    }

    cv::Size image_size;

    while (true)
    {
        cv::Mat image0, image;
        cam >> image0;
        image = image0.clone();
        image_size = image0.size();
        // Find the board
        std::vector<cv::Point2f> corners;
        // Find the corners of the internal corners of the chessboard
        bool found = cv::findChessboardCorners(image, board_sz, corners);
        //std::cout << "found: " << found << '\n';

        // Draw it
        cv::drawChessboardCorners(image, board_sz, corners, found);

        // We have located the chessboard
        if (found)
        {
            // Show the captured frame with found corners
            cv::imshow("Calibration", image);
            // Create writer for file and write captured frame to fs
            const auto fileName = "./cam" + std::to_string(camIndex) + '_' + std::to_string(chessboardNum) + ".bmp";
            cv::imwrite(fileName, image0);
            std::cout << "Wrote raw img to: " << fileName << std::endl;
            chessboardNum++;
        }
        else
        {
            cv::imshow("Raw img", image0);
        }

        // Use escape to cancel
        if ((cv::waitKey(100) & 255) == 27)
        {
            return;
        }
    }
}


int main(int argc, char* argv[])
{
    int board_w = 0;
    int board_h = 0;

    if (argc != 3)
    {
        printHelp();
    }

    board_w = atoi(argv[1]);
    board_h = atoi(argv[2]);


    captureCalibrationImages(0, board_w, board_h);
    captureCalibrationImages(1, board_w, board_h);
    return 0;
}