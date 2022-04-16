#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <memory>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

bool save(Mat frame);
bool display(Mat frame);

template<typename ... Args>
string string_format(const string& format, Args ... args){
    size_t size = 1 + snprintf(nullptr, 0, format.c_str(), args ...);  // Extra space for \0
    // unique_ptr<char[]> buf(new char[size]);
    char bytes[size];
    snprintf(bytes, size, format.c_str(), args ...);
    return string(bytes);
}


int main() {
  VideoCapture cap(0);
  if (!cap.isOpened()) {
    cout << "Cannot open camera\n";
    return 1;
  }

  Mat frame;
  int count;
  while (true) {
    count = ++count % 90;
    bool ret = cap.read(frame);
    if (!ret) {
      cout << "failed" << endl;
      break;
    }

    if(count == 1) {
      save(frame);
    }

    // if (display(frame)) {
    //   break;
    // }
  }

  return 0;
}

bool display(Mat frame) {
  imshow("live", frame);
  return waitKey(1) == 'q';
}

bool save(Mat frame) {
  bool ret = true;

  string fn = string_format("./imgs/%d.jpg", time(0));
  cout << fn << endl;

  vector<uchar> buff;  // buffer for coding
  vector<int> param(2);
  param[0] = IMWRITE_JPEG_QUALITY;
  param[1] = 80;  // default(95) 0-100
  imencode(".jpg", frame, buff, param);

  ofstream fout(fn, ios::out | ios::binary);
  fout.write((char*)&buff[0], buff.size());
  fout.close();

  return ret;
}