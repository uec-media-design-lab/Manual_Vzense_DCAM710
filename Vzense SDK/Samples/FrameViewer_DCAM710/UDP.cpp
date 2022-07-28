#include <iostream>
#include <vector>
#include <WinSock2.h> //TCP,UDP通信用ヘッダ
#include <UDP.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

// TCP,UDP通信用ライブラリ
#pragma comment(lib, "ws2_32.lib")

// inet_addr()関数で警告が出る場合は以下で警告を無効化する。
#pragma warning(disable:4996) 

// 送信関数
int send(cv::Mat mat, cv::Point2i pointxy,int min, cv::Rect rect,int nothing) {

    // ソケット通信winsockの立ち上げ
    // wsaDataはエラー取得等に使用する
    WSAData wsaData;
    WSAStartup(MAKEWORD(2, 0), &wsaData);   //MAKEWORD(2, 0)はwinsockのバージョン2.0ってこと

    // socket作成
    // socketは通信の出入り口 ここを通してデータのやり取りをする
    // socket(アドレスファミリ, ソケットタイプ, プロトコル)
    SOCKET sock;
    sock = socket(AF_INET, SOCK_DGRAM, 0);  //AF_INETはIPv4、SOCK_DGRAMはUDP通信、0は？

    // アドレス等格納
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;  //IPv4
    addr.sin_port = htons(12345);   //通信ポート番号設定
    addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1"); // 送信アドレスを127.0.0.1に設定

    // バッファ ここに送信するデータを入れる char配列
    //char buff[2048] = "END!!!!!";
    static const int sendSize = 65500; //UDPの仕様により上限は65kB

    char buf[sendSize];
    sprintf(buf, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d, ", mat.rows, mat.cols, pointxy.x, pointxy.y, min, rect.tl().x, rect.tl().y, rect.br().x, rect.br().y, nothing);
    //printf("%d\n", rect.br().y);

    // 送信
    // sendto(ソケット, 送信するデータ, データのバイト数, フラグ, アドレス情報, アドレス情報のサイズ);
    sendto(sock, buf, sizeof(buf), 0, (struct sockaddr*)&addr, sizeof(addr));

    // socketの破棄
    closesocket(sock);

    // winsockの終了
    WSACleanup();

    return 0;
}