#include <stdio.h>
#include <stdlib.h>

#include <opencv/cv.h>
#include <opencv/highgui.h>


#define ALTOBLOQUE 32
#define ANCHOBLOQUE 32
int fila, columna;
unsigned char *pOrigen;
unsigned char *pDestino;

void copiarBloque(int i, int j, IplImage * ImgOrigen, int k, int l, IplImage *ImgDestino) {

    for (i = 0; i < ALTOBLOQUE; i++) {


        for (j = 0; j < ANCHOBLOQUE; j++) {
            pOrigen = (unsigned char *) ImgOrigen->imageData + ((fila + i) * ImgOrigen->widthStep)+((columna + j) * ImgOrigen->nChannels);
            pDestino = (unsigned char *) ImgDestino->imageData + ((fila + i) * ImgDestino->widthStep)+((columna + j) * ImgDestino->nChannels);

            *pDestino++ = *pOrigen++;
            *pDestino++ = *pOrigen++;
            *pDestino++ = *pOrigen++;

        }


    }


}

int main(int argc, char** argv) {

    if (argc != 3) {
        printf("Usage: %s image_file_name\n", argv[0]);
        return EXIT_FAILURE;
    }

    IplImage* Img = cvLoadImage(argv[1], CV_LOAD_IMAGE_UNCHANGED);
    IplImage* Img2 = cvLoadImage(argv[2], CV_LOAD_IMAGE_UNCHANGED);

    // Always check if the program can find a file
    if (!Img || !Img2) {
        printf("Error: fichero %s no leido\n", argv[1]);
        return EXIT_FAILURE;
    }


    cvNamedWindow(argv[1], CV_WINDOW_NORMAL);
    cvShowImage(argv[1], Img);

    cvWaitKey(0);


    for (fila = 0; fila < Img->height; fila += ALTOBLOQUE) {

        for (columna = 0; columna < Img->width; columna += ANCHOBLOQUE) {

            copiarBloque(fila, columna, Img, fila, columna, Img2);
            cvShowImage(argv[1], Img2);
            cvWaitKey(5);
        }

    }




    cvReleaseImage(&Img);
    cvReleaseImage(&Img2);
    cvDestroyWindow(argv[1]);

    return EXIT_SUCCESS;

}