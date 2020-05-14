#include "backend.h"

#include <cstring>
#include <iostream>
#include <fstream>
#include <ctime>
#include <string>

#include "QrCode.hpp"

using qrcodegen::QrCode;

BackEnd::BackEnd(QObject *parent) :
    QObject(parent)
{
    m_sourceImage = "Images/QR_code_English_Wikipedia.png";
}

QString BackEnd::ssid()
{
    return m_ssid;
}

QString BackEnd::password()
{
    return m_password;
}

void BackEnd::setSsid(const QString &ssid)
{
    if (ssid == m_ssid)
        return;

    m_ssid = ssid;
}

void BackEnd::setPassword(const QString &password)
{
    if (password == m_password)
        return;

    m_password = password;
}

QString BackEnd::sourceImage()
{
    return m_sourceImage;
}

void BackEnd::clickOnGenerate()
{
     qWifi(4, (const char*) m_ssid.toLocal8Bit().data(), "WPA", (const char*) m_password.toLocal8Bit().data());
     //m_sourceImage = "file:./result.bmp";
     emit sourceImageChanged();
}


void BackEnd::qWifi(int mfactor, const char* ssid, const char* security, const char* password) {
  char* to_encode = new char[512];
  snprintf(to_encode, 512, "WIFI:S:%s;T:%s;P:%s;", ssid, security, password);
  const QrCode qr0 = QrCode::encodeText(to_encode, QrCode::Ecc::MEDIUM);
  int multiplier = mfactor;
  int size = qr0.getSize();
  bool* img_matrix = new bool[size*size*multiplier*multiplier];
  std::fill_n(img_matrix, size*size*multiplier*multiplier, 0);
  for(int j=0; j<size; j++){
    for(int i=0; i<size; i++){
      if (!qr0.getModule(i, j))
      {
        for(int x=0; x<multiplier; x++){
          for(int y=0; y<multiplier; y++){
            img_matrix[(i*multiplier+x)+((j*multiplier+y)*size*multiplier)] = 1;
          }
        }
      }
    }
  }
  time_t now = time(0);
  tm *ltm = localtime(&now);
  char source_img[200];
  char final_source_img[205];
  snprintf(source_img, 100, "./qrw_%s_%d%02d%02d%d%d%d.bmp",  // Format qrw_<ssid>_<year><month><day><hour><min><sec>
           ssid,
           1900 + ltm->tm_year,
           1 + ltm->tm_mon,
           ltm->tm_mday,
           1 + ltm->tm_hour,
           1 + ltm->tm_min,
           1 + ltm->tm_sec);

  std::cout << (const char*) source_img << " generated" << std::endl;
  snprintf(final_source_img, 205, "file:%s", source_img);
  m_sourceImage = final_source_img;
  write_bitmap(source_img, size*multiplier, size*multiplier, img_matrix);
}



// Todo change color 8bit on 1bit color (W/B)
void BackEnd::write_bitmap(const std::string path, const int width, const int height, bool* &data) {
    int pad=(4-(3*width)%4)%4, filesize=54+(3*width+pad)*height; // horizontal line must be a multiple of 4 bytes long, header is 54 bytes
    char header[54] = { 'B','M', 0,0,0,0, 0,0,0,0, 54,0,0,0, 40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0,24,0 };
    char padding[3] = { 0,0,0 };
    for(int i=0; i<4; i++) {
        header[ 2+i] = (char)((filesize>>(8*i))&255);
        header[18+i] = (char)((width   >>(8*i))&255);
        header[22+i] = (char)((height  >>(8*i))&255);
    }

    std::ofstream file(path, std::ios::out|std::ios::binary);
    file.write(header, 54);
    unsigned char* img_line = new unsigned char[3*width];
    for (int i=height-1; i>=0; i--) {
        std::fill_n(img_line, 3*width, 0x00);
        for (int j=0; j<width; j++) {
          if (data[i+j*width])
                {
            img_line[3*j  ] = (unsigned char)255;
            img_line[3*j+1] = (unsigned char)255;
            img_line[3*j+2] = (unsigned char)255;
                }
        }
        file.write((char*)(img_line), 3*width);
        file.write(padding, pad);
    }
    file.close();
    delete[] img_line;
}


