#include "geom.h"

Geom::Geom() {
    imageUtils = new ImageChange;
}

Geom::~Geom() {

}

// 图像 按 宽 高 顺序缩放。 scale(width, height)
QImage Geom::scale(double rateW, double rateH, QImage image) {

    Mat matImg = imageUtils->convertQImageToMat(image);
//    Mat matDst = Mat(matImg.rows * rateH, matImg.cols * rateW, matImg.type(), Scalar::all(0));
////    Mat matDst;
//    resize(matImg, matDst, Size(static_cast<int>(matImg.rows * rateH),
//                                static_cast<int>(matImg.cols * rateW)) );
//     = Mat(matImg.cols * rateW, matImg.rows * rateH, matImg.type(), Scalar::all(0))
    Mat matDst;


    // 需要构建 4个倍数大小的图像
        int col = matImg.cols * rateW;
        int row = matImg.rows * rateW;

    if(rateW > 1) {
        // INTER_LINEAR
    resize(matImg, matDst, Size(static_cast<int>(col - col%4 + 4*(col & 0x01) ),
                                static_cast<int>(row) - (row%4 + 4*(row & 0x01)  )), 0, 0,INTER_CUBIC);
    }
    if(rateW < 1) {
        resize(matImg, matDst, Size(static_cast<int>( col - col%4 + 4*(col & 0x01) ),
                                    static_cast<int>(row) - (row%4 + 4*(row & 0x01) )), 0, 0,INTER_AREA);
//        resize(matImg, matDst, Size(static_cast<int>(matImg.cols),
//                                    static_cast<int>(matImg.rows)), 0.5, 0.5,INTER_AREA);
    }

   return imageUtils->convertMatToQImage(matDst);

}
void Geom::init() {

}
