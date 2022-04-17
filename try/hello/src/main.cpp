#include <sys/stat.h>
#include <sys/types.h>

#include <ctime>
#include <fstream>
#include <iostream>
#include <memory>
#include <opencv2/opencv.hpp>
#include <string>

using namespace std;
using namespace cv;

bool init();
void loop();
bool save(Mat frame);
bool display(Mat frame);

template <typename... Args>
string string_format(const string& format, Args... args) {
  size_t size =
      1 + snprintf(nullptr, 0, format.c_str(), args...);  // Extra space for \0
  char bytes[size];
  snprintf(bytes, size, format.c_str(), args...);
  return string(bytes);
}

int main() {
  if (!init()) {
    return 1;
  }

  loop();

  return 0;
}

bool init() {
  bool result = true;
  struct stat ret;
  if (stat("./imgs", &ret) == -1) {
    if (mkdir("./imgs", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) != 0) {
      cout << "mkdir imgs failed." << endl;
      result = false;
    }
  } else {
    cout << "./imgs found." << endl;
  }
  return result;
}

void loop() {
  VideoCapture cap(0);
  if (!cap.isOpened()) {
    cout << "Cannot open camera" << endl;
    return;
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

    if (count == 1) {
      save(frame);
    }

    // if (display(frame)) {
    //   break;
    // }
  }
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
  if (fout.is_open()) {
    fout.write((char*)&buff[0], buff.size());
    fout.close();
  } else {
    cout << "write image file failed." << endl;
  }

  return ret;
}