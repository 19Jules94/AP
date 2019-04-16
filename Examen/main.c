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
    IplImage* Img = cvLoadImage(argv[1], CV_LOAD_IMAGE_COLOR);
    IplImage *Invertida = cvCreateImage(cvSize(Img->height, Img->width), IPL_DEPTH_8U, 3);
    // Always check if the program can find a file
    if (!Img) {
        printf("Error: fichero %s no leido\n", argv[1]);
        return EXIT_FAILURE;
    }

    int mitad = Img->height / 2;
    int fila, columna;
    unsigned char *pInver;
    unsigned char *pImg;


    //Primer cuarto
    for (fila = 0; fila < mitad; fila++) {

        pImg = (unsigned char *) Img->imageData + (fila) * Img->widthStep;
        pInver = (unsigned char *) Invertida->imageData + fila * Invertida->widthStep;


        for (columna = 0; columna < Img->width / 2; columna++) {

            *pInver++ = *pImg++;
            pImg++;
            pImg++;
            *pInver++ = 0;
            *pInver++ = 0;

        }

    }


    //Segundo cuarto
    for (fila = 0; fila < mitad; fila++) {

        pImg = (unsigned char *) Img->imageData + (fila) * Img->widthStep + columna * Img->nChannels;
        pInver = (unsigned char *) Invertida->imageData + fila * Invertida->widthStep + columna * Invertida->nChannels;


        for (columna = 0; columna < Img->width / 2; columna++) {



            *pInver++ = 0;
            *pInver++ = *pImg++;
            pImg++;
            pImg++;
            *pInver++ = 0;

        }

    }
    //Tercer cuarto
    for (fila = 0; fila < mitad; fila++) {

        pImg = (unsigned char *) Img->imageData + (fila + Img->width / 2) * Img->widthStep;
        pInver = (unsigned char *) Invertida->imageData + (fila + Invertida->width / 2) * Invertida->widthStep;


        for (columna = 0; columna < Img->width / 2; columna++) {


            *pInver++ = 0;
            *pInver++ = 0;
            *pInver++ = *pImg++;
            pImg++;
            pImg++;


        }

    }


    //Cuarto cuarto
    for (fila = 0; fila < mitad; fila++) {

        pImg = (unsigned char *) Img->imageData + (fila + Img->width / 2) * Img->widthStep + columna * Img->nChannels;
        pInver = (unsigned char *) Invertida->imageData + (fila + Invertida->width / 2) * Invertida->widthStep + (columna) * Invertida->nChannels;


        for (columna = 0; columna < Img->width / 2; columna++) {



            *pInver++ = *pImg++;
            *pInver++ = *pImg++;
            *pInver++ = *pImg++;

        }

    }










    // a visualization window is created with title 'image'
    cvNamedWindow(argv[1], CV_WINDOW_NORMAL);
    // img is shown in 'image' window
    cvShowImage(argv[1], Img);
    cvWaitKey(0);




    cvNamedWindow("Componente GREEN", CV_WINDOW_AUTOSIZE);
    cvShowImage("Componente GREEN", Invertida);

    cvWaitKey(0);

    cvReleaseImage(&Img);

    cvReleaseImage(&Invertida);

    cvDestroyWindow(argv[1]);

    cvDestroyWindow("Componente GREEN");

    // memory release for img before exiting the application



    // Self-explanatory
    cvDestroyWindow(argv[1]);

    return EXIT_SUCCESS;

}