#include <stdio.h>
#include <stdlib.h>

#include <opencv/cv.h>
#include <opencv/highgui.h>


#define ALTOBLOQUE 32
#define ANCHOBLOQUE 32

unsigned char *pOrigen;
unsigned char *pDestino;

void copiarBloque(int filaBloque1, int columnaBloque1, IplImage * ImgOrigen, int filaBloque2, int columnaBloque2, IplImage *ImgDestino) {

    int fila, columna;
    //COPIAMOS EL BLOQUE
    for (fila = 0; fila < ALTOBLOQUE; fila++) {

        pOrigen = (unsigned char *) (ImgOrigen->imageData + (filaBloque1 + fila) * ImgOrigen->widthStep + columnaBloque1 * ImgOrigen->nChannels);
        pDestino = (unsigned char *) (ImgDestino->imageData + (filaBloque2 + fila) * ImgDestino->widthStep + columnaBloque2 * ImgDestino->nChannels);

        for (columna = 0; columna < ANCHOBLOQUE; columna++) {

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
    int fila, columna;
    for (fila = 0; fila < Img->height; fila += ALTOBLOQUE) {

        for (columna = 0; columna < Img->width; columna += ANCHOBLOQUE) {

            copiarBloque(fila, columna, Img, fila, columna,Img2);
            cvShowImage("FOTO", Img2);
            cvWaitKey(1);
        }


    }
    cvReleaseImage(&Img);
    cvReleaseImage(&Img2);
    cvDestroyWindow(argv[1]);

    return EXIT_SUCCESS;

}