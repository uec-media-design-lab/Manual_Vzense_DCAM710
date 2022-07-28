#include <iostream>
#include <vector>
#include <WinSock2.h> //TCP,UDP�ʐM�p�w�b�_
#include <UDP.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

// TCP,UDP�ʐM�p���C�u����
#pragma comment(lib, "ws2_32.lib")

// inet_addr()�֐��Ōx�����o��ꍇ�͈ȉ��Ōx���𖳌�������B
#pragma warning(disable:4996) 

// ���M�֐�
int send(cv::Mat mat, cv::Point2i pointxy,int min, cv::Rect rect,int nothing) {

    // �\�P�b�g�ʐMwinsock�̗����グ
    // wsaData�̓G���[�擾���Ɏg�p����
    WSAData wsaData;
    WSAStartup(MAKEWORD(2, 0), &wsaData);   //MAKEWORD(2, 0)��winsock�̃o�[�W����2.0���Ă���

    // socket�쐬
    // socket�͒ʐM�̏o����� ������ʂ��ăf�[�^�̂���������
    // socket(�A�h���X�t�@�~��, �\�P�b�g�^�C�v, �v���g�R��)
    SOCKET sock;
    sock = socket(AF_INET, SOCK_DGRAM, 0);  //AF_INET��IPv4�ASOCK_DGRAM��UDP�ʐM�A0�́H

    // �A�h���X���i�[
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;  //IPv4
    addr.sin_port = htons(12345);   //�ʐM�|�[�g�ԍ��ݒ�
    addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1"); // ���M�A�h���X��127.0.0.1�ɐݒ�

    // �o�b�t�@ �����ɑ��M����f�[�^������ char�z��
    //char buff[2048] = "END!!!!!";
    static const int sendSize = 65500; //UDP�̎d�l�ɂ������65kB

    char buf[sendSize];
    sprintf(buf, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d, ", mat.rows, mat.cols, pointxy.x, pointxy.y, min, rect.tl().x, rect.tl().y, rect.br().x, rect.br().y, nothing);
    //printf("%d\n", rect.br().y);

    // ���M
    // sendto(�\�P�b�g, ���M����f�[�^, �f�[�^�̃o�C�g��, �t���O, �A�h���X���, �A�h���X���̃T�C�Y);
    sendto(sock, buf, sizeof(buf), 0, (struct sockaddr*)&addr, sizeof(addr));

    // socket�̔j��
    closesocket(sock);

    // winsock�̏I��
    WSACleanup();

    return 0;
}