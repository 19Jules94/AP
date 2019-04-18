#include <stdio.h>
#include <stdlib.h>
#include <emmintrin.h> 
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
    IplImage *Img = cvLoadImage(argv[1], CV_LOAD_IMAGE_COLOR);
    IplImage *ImgDestino = cvCreateImage(cvSize(Img->width, Img->height), IPL_DEPTH_8U, 3);

    if (!Img) {
        printf("Error: fichero %s no leido\n", argv[1]);
        return EXIT_FAILURE;
    }

    int fila, columna, iterac;

    for (fila = 0; fila < Img->height; fila++) {

        __m128i *pImg = (__m128i*) (Img->imageData + fila * Img->widthStep);
        __m128i *pDestino = (__m128i*) (ImgDestino->imageData + fila * ImgDestino->widthStep);

        for (columna = 0; columna < Img->widthStep; columna = columna + 16) {

            *pDestino++ = *pImg++;

        }
    }
    cvNamedWindow(argv[1], CV_WINDOW_AUTOSIZE);
    cvShowImage(argv[1], Img);

    cvNamedWindow("Destino", CV_WINDOW_AUTOSIZE);
    cvShowImage("Destino", ImgDestino);

    cvWaitKey(5);

    for (iterac = 0; iterac < 256; iterac++) {
        for (fila = 0; fila < Img->height; fila++) {
            __m128i *pDestino = (__m128i*) (ImgDestino->imageData + fila * ImgDestino->widthStep);

            for (columna = 0; columna < Img->widthStep; columna = columna + 16) {

                __m128i B = _mm_set1_epi8(1);
                __m128i A = _mm_load_si128(pDestino);
                __m128i C = _mm_subs_epu8(A, B);
                _mm_store_si128(pDestino, C);
                pDestino++;
            }
        }
        cvShowImage("Destino", ImgDestino);
        cvWaitKey(1);
    }
    cvReleaseImage(&Img);
    cvReleaseImage(&ImgDestino);


    // Self-explanatory
    //cvDestroyWindow(argv[1]);
    cvDestroyWindow(argv[1]);
    cvDestroyWindow("Destino");

    return EXIT_SUCCESS;

}