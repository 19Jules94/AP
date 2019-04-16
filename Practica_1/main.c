#include <stdio.h>
#include <stdlib.h>

#include <opencv/cv.h>
#include <opencv/highgui.h>

int main(int argc, char** argv) {

    if (argc != 2) {
        printf("Usage: %s image_file_name\n", argv[0]);
        return EXIT_FAILURE;
    }

    //CV_LOAD_IMAGE_COLOR = 1 forces the resultant IplImage to be colour.
    //CV_LOAD_IMAGE_GRAYSCALE = 0 forces a greyscale IplImage.
    //CV_LOAD_IMAGE_UNCHANGED = -1
    IplImage *Img1 = cvLoadImage(argv[1], CV_LOAD_IMAGE_COLOR);
    IplImage *BLUE = cvCreateImage(cvSize(Img1->width, Img1->height), IPL_DEPTH_8U, 3);
    IplImage *GREEN = cvCreateImage(cvSize(Img1->width, Img1->height), IPL_DEPTH_8U, 3);
    IplImage *RED = cvCreateImage(cvSize(Img1->width, Img1->height), IPL_DEPTH_8U, 3);


    unsigned char *pImg1;
    unsigned char *pImgB;
    unsigned char *pImgG;
    unsigned char *pImgR;


    cvNamedWindow(argv[1], CV_WINDOW_AUTOSIZE);
    cvShowImage(argv[1], Img1);    
    cvWaitKey(0);



    if (!Img1) {
        printf("Error: fichero %s no leido\n", argv[1]);
        return EXIT_FAILURE;
    }

    int fila, columna;

    for (fila = 0; fila < Img1->height; fila++) {

        pImg1 = (unsigned char *) Img1->imageData + fila * Img1->widthStep;
        pImgB = (unsigned char *) BLUE->imageData + fila * BLUE->widthStep;
        pImgG = (unsigned char *) GREEN->imageData + fila * GREEN->widthStep;
        pImgR = (unsigned char *) RED->imageData + fila * RED->widthStep;
       

        for (columna = 0; columna < Img1->width; columna++) {


            *pImgB++ = *pImg1++;
            *pImgB++ = 0;
            *pImgB++ = 0;

            *pImgG++ = 0;
            *pImgG++ = *pImg1++;
            *pImgG++ = 0;

            *pImgR++ = 0;
            *pImgR++ = 0;
            *pImgR++ = *pImg1++;

        }

    }

    cvNamedWindow("Componente RED", CV_WINDOW_AUTOSIZE);
    cvShowImage("Componente RED", RED);

    cvNamedWindow("Componente BLUE", CV_WINDOW_AUTOSIZE);
    cvShowImage("Componente BLUE", BLUE);

    cvNamedWindow("Componente GREEN", CV_WINDOW_AUTOSIZE);
    cvShowImage("Componente GREEN", GREEN);

    cvWaitKey(0);

    cvReleaseImage(&Img1);
    cvReleaseImage(&RED);
    cvReleaseImage(&BLUE);
    cvReleaseImage(&GREEN);

    cvDestroyWindow(argv[1]);
    cvDestroyWindow("Componente RED");
    cvDestroyWindow("Componente GREEN");
    cvDestroyWindow("Componente BLUE");

    return EXIT_SUCCESS;

}