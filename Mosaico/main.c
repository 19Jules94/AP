#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>


#define ALTOBLOQUE 16
#define ANCHOBLOQUE 16
int fila, columna;

void copiarBloque(int i, int j, IplImage * ImgOrigen, int k, int l, IplImage *ImgDestino) {

    for (i = 0; i <= ALTOBLOQUE; i++) {
        unsigned char *pOrigen = (unsigned char *) ImgOrigen->imageData + ((fila + i) * ImgOrigen->widthStep)+((columna + j) * ImgOrigen->nChannels);
        unsigned char *pDestino = (unsigned char *) ImgDestino->imageData + ((fila + i) * ImgDestino->widthStep)+((columna + j) * ImgDestino->nChannels);

        for (j = 0; j <= ANCHOBLOQUE; j++) {


            *pDestino++ = *pOrigen++;
            *pDestino++ = *pOrigen++;
            *pDestino++ = *pOrigen++;

        }


    }


}

int compararBloques(int filaBloque1, int colBloque1, IplImage * ImgOrigen, int filaBloque2, int colBloque2, IplImage *ImgDestino) {

    int fila, columna;
    int DP = 0;
    int suma = 0;
    for (fila = 0; fila < ALTOBLOQUE; fila++) {

        unsigned char *pOrigen = (unsigned char *) ImgOrigen->imageData + ((fila + filaBloque1) * ImgOrigen->widthStep)+((columna + colBloque1) * ImgOrigen->nChannels);
        unsigned char *pDestino = (unsigned char *) ImgDestino->imageData + ((fila + filaBloque2) * ImgDestino->widthStep)+((columna + colBloque2) * ImgDestino->nChannels);
        for (columna = 0; columna < ANCHOBLOQUE; columna++) {

            DP = abs(*pOrigen++ - *pDestino++);
            DP += abs(*pOrigen++ - *pDestino++);
            DP += abs(*pOrigen - *pDestino);
            suma += DP;
        }
    }
    return suma;
}

int main(int argc, char** argv) {

    if (argc != 3) {
        printf("Usage: %s image_file_name\n", argv[0]);
        return EXIT_FAILURE;
    }

    IplImage* Img = cvLoadImage(argv[1], CV_LOAD_IMAGE_UNCHANGED);
    IplImage* Img2 = cvLoadImage(argv[2], CV_LOAD_IMAGE_UNCHANGED);
    IplImage* ImgRes = cvCreateImage(cvSize(Img->width, Img->height), 8, 3);
    // Always check if the program can find a file
    if (!Img || !Img2) {
        printf("Error: fichero %s no leido\n", argv[1]);
        return EXIT_FAILURE;
    }

    int fil1, col1, fil2, col2;
    int dif, maxPar, filMax, colMax;

    for (fil1 = 0; fil1 < Img->height; fil1 += ALTOBLOQUE) {

        for (col1 = 0; col1 < Img->width; col1 += ANCHOBLOQUE) {
            maxPar = INT_MAX;
            filMax = 0;
            colMax = 0;

            for (fil2 = 0; fil2 < (Img2->height); fil2 += ALTOBLOQUE) {

                for (col2 = 0; col2 < (Img2->width); col2 += ANCHOBLOQUE) {
                    dif = compararBloques(fil1, col1, Img, fil2, col2, Img2);

                    if (dif < maxPar) {
                        maxPar = dif;
                        filMax = fil2;
                        colMax = col2;
                    }
                }
            }
            copiarBloque(filMax, colMax, Img2, fil1, col1, ImgRes);

        }
    }
    cvNamedWindow("Resultado", CV_WINDOW_AUTOSIZE);
    cvShowImage("Resultado", ImgRes);
    cvWaitKey(0);
    cvDestroyWindow("Resultado");


    cvReleaseImage(&Img);
    cvReleaseImage(&Img2);
    cvReleaseImage(&ImgRes);

    return EXIT_SUCCESS;

}