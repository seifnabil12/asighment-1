// Member1
// Name: Ahmed Baker Ahmed Mohamed
// Code: 20221004
// e-mail: ahmed31112016@gmail.com

// Member2
// Name: Ibrahem Maher Mansour Mohamed
// Code: 20221221
// e-mail: ibrahimmahe1234kh@gmail.com

// Member3
// Name: Seif Mohamed Nabil Abd El Rahman
// Code: 20221222
// e-mail: seif.mohamed.nabil.2003@gmail.com








#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"
#include <string>

using namespace std;
unsigned char image[SIZE][SIZE];
unsigned char image1[SIZE][SIZE];
unsigned char image2[SIZE][SIZE];
unsigned char shrinkage[SIZE][SIZE];
unsigned char image3[SIZE][SIZE];
unsigned char imageMerged[SIZE][SIZE];

void loadImage();
void saveImage();
void blackandwhite();
void invert();
void merge_two_img();
void flipImage(bool flipHorizontal);
void adjustBrightness();
void rotate();
void detectEdges();
void enlargeQuarter();
void Shrink();
void mirrorImage();
void rearrangeQuarters();
void blur();
void SkewImageRight();
void SkewImageUp();
void crop();
void askToContinue();

int main()
{
    int chosennumber;
    cout << "Choose the number of the filter that you want to apply to the image: \n";
    cout << "1. Black and white Filter\n";
    cout << "2. Invert Filter\n";
    cout << "3. Merge Filter\n";
    cout << "4. Flip image Filter\n";
    cout << "5. Rotate Filter\n";
    cout << "6. Adjust Brightness Filter\n";
    cout << "7. Detect Edges Filter\n";
    cout << "8. Enlarge Quarter Filter\n";
    cout << "9. Shrink Filter\n";
    cout << "10. Mirror Image Filter\n";
    cout << "11. Rearrange Quarters Filter\n";
    cout << "12. Blur Filter\n";
    cout << "13.SkewImageRight\n";
    cout << "14.SkewImageUp\n";
    cout << "15. crop \n";
    cin >> choosenumber;

    loadImage();

    switch (chosennumber) {
        case 1:
            blackandwhite();
            break;
        case 2:
            invert();
            break;
        case 3:
            merge_two_img();
            break;
        case 4: {
            char flipDirection;
            cout << "Enter 'h' to flip horizontally or 'v' to flip vertically: ";
            cin >> flipDirection;
            bool flipHorizontal = (flipDirection == 'h');
            flipImage(flipHorizontal);
            break;
        }
        case 5:
            rotate();
            break;
        case 6:
            adjustBrightness();
            break;
        case 7:
            detectEdges();
            break;
        case 8:
            enlargeQuarter();
            break;
        case 9:
            Shrink();
            break;
        case 10:
            mirrorImage();
            break;
        case 11:
            rearrangeQuarters();
            break;
        case 12:
            blur();
            break;
        case 13:
            SkewImageRight();
            break;
        case 14:
            SkewImageUp();
            break;
        case 15:
            crop();
            break;
        default:
            cout << "Invalid choice. Exiting..." << endl;
            return 0;
    }

    saveImage();
    askToContinue();
    return 0;
}

void loadImage()
{
    char imageFileName[100];

    cout << "Enter the source image file name (without extension): ";
    cin >> imageFileName;

    strcat(imageFileName, ".bmp");
    readGSBMP(imageFileName, image);
}

void saveImage()
{
    char imageFileName[100];

    cout << "Enter the target image file name (without extension): ";
    cin >> imageFileName;

    strcat(imageFileName, ".bmp");
    writeGSBMP(imageFileName, image);
}

void blackandwhite() {
    // Initialize i and j in the loop
    for (int i = 0; i < SIZE; i++) { // for loop that moves along every pixel in the 2D array (image)
        for (int j = 0; j < SIZE; j++) {



            if (image[i][j] > 127) // 127 is the averge pixel numbers
                image[i][j] = 255; // it means chanfe to white
            else
                image[i][j] = 0; // it means change to black

        }
    }


    cout << "Black and white filter applied." << endl;
}

void invert()
{
    for (int i = 0; i < SIZE; i++)  // Initialize i and j in the loop
    {
        for (int j = 0; j < SIZE; j++) {
            image[i][j] = 255 - image[i][j];
        }
    }



    cout << "Invert filter applied." << endl;
}

void merge_two_img()
{
    char imageFileName2[100];

    cout << "Enter the image you would like to combine (without extension): ";
    cin >> imageFileName2; // input the second image .

    strcat(imageFileName2, ".bmp");
    readGSBMP(imageFileName2, image2);

    // Merge the two images
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            //  It takes the average of the color values.
            imageMerged[i][j] = (image[i][j] + image2[i][j]) / 2;
        }
    }
// Copy the merged image data to the main 'image' array
    memcpy(image, imageMerged, sizeof(image));


    cout << "Merge filter applied." << endl;
}

// Function to flip the image horizontally or vertically.
void flipImage(bool flipHorizontal)
{
    int height = SIZE;
    int width = SIZE;
    unsigned char flippedImg[SIZE][SIZE];
// 2 dimentional arry of height (row) and the width (column).

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {  // For horizontal flip, reverse the columns like a mirror.

            if (flipHorizontal)
                flippedImg[i][j] = image[i][width - j - 1];
            else
                flippedImg[i][j] = image[height - i - 1][j];
        }
    }
// Copy the flipped image back to the original image array
    memcpy(image, flippedImg, sizeof(image));


    cout << "Flip image filter applied." << endl;
}

void adjustBrightness()
{
    char choice;
    cout << "Do you want to lighten (L) or darken (D) the image? ";
    cin >> choice;

    int adjustment , photo ,i ,j;
    photo = static_cast<int>(image[i][j]);
    adjustment = (photo / 2);
    if(toupper(choice) == 'L') {
        adjustment = adjustment  ; // Lighten by 50%
        if (adjustment>255)
            adjustment=255;

    }
    else if(toupper(choice) == 'D') {
        adjustment = - adjustment ; // Darken by 50%
    }
    // Iterate over the image pixels
    for( i = 0; i < SIZE; i++) {
        for( j = 0; j < SIZE; j++) {
            int pixel = static_cast<int>(image[i][j]) + adjustment;

            // Clamp the values between 0 and 255
            pixel = max(min(pixel, 255), 0);

            // Assign the adjusted pixel back to the image
            image[i][j] = static_cast<unsigned char>(pixel);
        }
    }


    cout << " adjustBrightness image filter applied." << endl;
}
void rotate() {
    unsigned char rotated_image[SIZE][SIZE];

    cout << "Choose the degree of rotation";

    int degree;
    cin >> degree;

    if (degree == 90) {//The j index is used as the row index in the rotated image, while the SIZE - 1 - i index is used as the column index. This swap of indices achieves the clockwise rotation by 90 degrees


        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                rotated_image[j][SIZE - 1 - i] = image[i][j];
            }
        }// The loop continues until i < SIZE and j < SIZE, ensuring that all pixels in the original image are processed.

        // Copy the rotated image back to the original image
        memcpy(image, rotated_image, sizeof(image));
    }
    else if (degree == 180) {

        int q = 2;
        while (q != 0) {
            for (int i = 0; i < SIZE; ++i) {
                for (int j = 0; j < SIZE; ++j) {
                    rotated_image[j][SIZE - 1 - i] = image[i][j];
                    // The loop continues until i < SIZE and j < SIZE, ensuring that all pixels in the original image are processed but 2 times.

                }

            }
            q--;
            // Copy the rotated image back to the original image
            memcpy(image, rotated_image, sizeof(image));
        }
    }
    else if (degree == 270) {

        int q = 3;

        while (q != 0) {
            for (int i = 0; i < SIZE; ++i) {
                for (int j = 0; j < SIZE; ++j) {
                    rotated_image[j][SIZE - 1 - i] = image[i][j];
                    // The loop continues until i < SIZE and j < SIZE, ensuring that all pixels in the original image are processed but 3 times.

                }

            }
            q--;
            // Copy the rotated image back to the original image
            memcpy(image, rotated_image, sizeof(image));
        }
    }
    cout << " rotate image filter applied." << endl;
}
void detectEdges()
{
    int gradientX[SIZE][SIZE];
    int gradientY[SIZE][SIZE];

    // Apply Sobel operator for gradient calculation
    for (int i = 1; i < SIZE - 1; i++)
    {
        for (int j = 1; j < SIZE - 1; j++)
        {
            int gx = image[i - 1][j + 1] + 2 * image[i][j + 1] + image[i + 1][j + 1]
                     - image[i - 1][j - 1] - 2 * image[i][j - 1] - image[i + 1][j - 1];

            int gy = image[i + 1][j - 1] + 2 * image[i + 1][j] + image[i + 1][j + 1]
                     - image[i - 1][j - 1] - 2 * image[i - 1][j] - image[i - 1][j + 1];

            gradientX[i][j] = gx;
            gradientY[i][j] = gy;
        }
    }

    // Compute gradient magnitude and normalize
    for (int i = 1; i < SIZE - 1; i++)
    {
        for (int j = 1; j < SIZE - 1; j++)
        {
            int magnitude = sqrt(gradientX[i][j] * gradientX[i][j] + gradientY[i][j] * gradientY[i][j]);
            image[i][j] = magnitude > 128 ? 0 : 255; // Invert the colors
        }
        }

    cout << " detectEdges image filter applied." << endl;
}
void enlargeQuarter() {// in this filter we devide the photo in four quarters then choose one quarter to make it new as image
    int h = SIZE / 2;
    int w = SIZE / 2;
    unsigned char enlarged[h][w];

    int quarter;
    cout << "Enter the quarter you want to enlarge (1-4): ";
    cin >> quarter;

    int startRow = (quarter > 2) ? h : 0;
    int startCol = (quarter % 2 == 0) ? w : 0;

    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            enlarged[i][j] = image[startRow + i][startCol + j];
        }
    }

    // Enlarge the selected quarter
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            int row = i / 2;
            int col = j / 2;
            image[i][j] = enlarged[row][col];
        }
    }
    cout << " enlargeQuarter image filter applied." << endl;
}
void Shrink()
{
    int shrinkFactor;
    cout << "Enter the shrink factor (2 for half size, 3 for one-third size, 4 for quarter size): ";
    cin >> shrinkFactor;

    if (shrinkFactor < 2 || shrinkFactor > 4)
    {
        cout << "Shrink factor should be between 2 and 4. No changes made." << endl;
        return;
    }

    int newSize = SIZE / shrinkFactor; // Calculate the new size of the image

    unsigned char shrunkImage[newSize][newSize]; // Create a new smaller image

    // Loop through the shrunk image
    for (int i = 0; i < newSize; i++)
    {
        for (int j = 0; j < newSize; j++)
        {
            // Calculate the average value in the original image for each pixel in the shrunk image
            int sum = 0;
            for (int x = i * shrinkFactor; x < (i + 1) * shrinkFactor; x++)
            {
                for (int y = j * shrinkFactor; y < (j + 1) * shrinkFactor; y++)
                {
                    sum += image[x][y];
                }
            }
            shrunkImage[i][j] = static_cast<unsigned char>(sum / (shrinkFactor * shrinkFactor));
        }
    }

    // Copy the shrunk image back to the original image array and set the background to white
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (i >= newSize || j >= newSize)
            {
                // Set the background pixels to white
                image[i][j] = 255;
            }
            else
            {
                // Copy the shrunk image pixels
                image[i][j] = shrunkImage[i][j];
            }
        }
    }
    cout << " shrink image filter applied." << endl;
}
void mirrorImage()
{
    int height = SIZE;
    int width = SIZE;

    cout << "Choose the Mirror filter: \n";
    cout << "1. Mirror the left half\n";
    cout << "2. Mirror the right half\n";
    cout << "3. Mirror the upper half\n";
    cout << "4. Mirror the lower half\n";
    int b;
    cin >> b;

    if (b == 1) {
        // Mirror the left half of the image
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width / 2; j++)
            {
                image[i][width - j - 1] = image[i][j];
            }
        }
    }
    else if (b == 2) {
        // Mirror the right half of the image
        for (int i = 0; i < height; i++)
        {
            for (int j = width / 2; j < width; j++)
            {
                image[i][width - j - 1] = image[i][j];
            }
        }
    }
    else if (b == 3) {
        // Mirror the upper half of the image
        for (int i = 0; i < height / 2; i++)
        {
            for (int j = 0; j < width; j++)
            {
                image[height - i - 1][j] = image[i][j];
            }
        }
    }
    else if (b == 4) {
        // Mirror the lower half of the image
        for (int i = height / 2; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                image[height - i - 1][j] = image[i][j];
            }
        }
    }
    cout << " mirrorImage filter applied." << endl;
}
void rearrangeQuarters()// in this filter we devide the photo in four quarters then choose request another order from the user then make the new order as a new image  
{
    int h = SIZE / 2;
    int w = SIZE / 2;
    unsigned char newImage[SIZE][SIZE];

    // Divide the image into quarters
    unsigned char quarter1[h][w];
    unsigned char quarter2[h][w];
    unsigned char quarter3[h][w];
    unsigned char quarter4[h][w];

    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            quarter1[i][j] = image[i][j];
            quarter2[i][j] = image[i][j + w];
            quarter3[i][j] = image[i + h][j];
            quarter4[i][j] = image[i + h][j + w];
        }
    }

    // Ask the user for the order of quarters
    cout << "Enter the order of quarters (1-4): ";
    int order[4];
    for (int i = 0; i < 4; ++i) {
        cin >> order[i];
    }

    // Rearrange the quarters based on the user's order
    unsigned char* quarters[5] = {nullptr, quarter1[0], quarter2[0], quarter3[0], quarter4[0] };

    for (int i = 0; i < 4; ++i) {
        int quarterIndex = order[i];

        for (int j = 0; j < h; ++j) {
            for (int k = 0; k < w; ++k) {
                newImage[j + (i >= 2) * h][k + (i % 2) * w] = quarters[quarterIndex][j * w + k];
            }
        }
    }

    memcpy(image, newImage, sizeof(image));
    cout << "  rearrangeQuarters filter applied." << endl;
}
void blur() {
    for (int i = 0; i < SIZE - 2; i++) {
        for (int j = 0; j < SIZE - 2; j++) {
            image[i][j] = (image[i][j] + image[i + 2][j + 2]) / 2;
        }
    }
    saveImage();
    cout << "  blur filter applied." << endl;
}

void SkewImageRight()
{
    loadImage();

    double rad;
    cout << "Enter degree: ";
    cin >> rad;
    rad = (rad * 22) / (180 * 7);
    double mov = tan(rad) * 256;
    double step = mov / SIZE;
    unsigned char img_in[SIZE][SIZE + (int)mov];
    int x=(tan(rad)*256)/(tan(rad)+1);
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            img_in[i][j] = 255;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE ; j++) {

            img_in[i][((((j+ (int)mov) * x ))/(int)(SIZE*(tan(rad))))] = image[i][j];
        }
        mov -= step;
    }

    for(int i=0 ; i<SIZE ; i++)
    {
        for(int j=0 ; j<SIZE ; j++)
        {

            image[i][j]=img_in[i][j];

        }
    }

    saveImage();

}

void SkewImageUp()
{

    loadImage();

    double rad;
    cout << "Enter degree: ";
    cin >> rad;
    rad = (rad * 22) / (180 * 7);
    double mov = tan(rad) * 256;
    double step = mov / SIZE;
    unsigned char img_in[SIZE+ (int)mov][SIZE];
    int x=(tan(rad)*256)/(tan(rad)+1);
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            img_in[i][j] = 255;

    for (int j = 0; j < SIZE; j++) {
        for (int i = 0; i < SIZE ; i++) {
            img_in[(((i+(int)mov)*x))/(int)(SIZE*(tan(rad)))][j] = image[i][j];
        }
        mov -= step;
    }

    for(int i=0 ; i<SIZE ; i++)
    {
        for(int j=0 ; j<SIZE ; j++)
        {

            image[i][j]=img_in[i][j];

        }
    }

    saveImage();

}

// Crop Image
void crop()
{
    unsigned char new_image[SIZE][SIZE];
    int x, y, length, width;
    cout << " enter the crop details in order: \n";
    cout << "x(start row) - y(start column) - length(num of rows) - width(num of columns): \n";
    cin >> x >> y >> length >> width;
    if (x < 0 || y < 0 || x + length > 256 || y + width > 256)
    {
        cerr << "invalid edges.\n";
        return;
    }
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            new_image[i][j] = ((i < x || i >= x + length || j < y || j >= y + width) ? 255 : image[i][j]);

    char imageFileName[100];

    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat(imageFileName, ".bmp");
    writeGSBMP(imageFileName,new_image);
}

void askToContinue() {
    std::string userInput;
    do {
        std::cout << "Do you want to continue? (yes/no): ";
        std::cin >> userInput;
        if (userInput == "yes") {
            // Call the function or code block you want to repeat here
            // For example, you might call your main() function here
            main();
        }
    } while (userInput!="no");
}
