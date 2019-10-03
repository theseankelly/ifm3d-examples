
#include <cstdint>
#include <iostream>
#include <memory>
#include <opencv2/core/core.hpp>
#include <ifm3d/camera.h>
#include <ifm3d/fg_udp.h>
#include <ifm3d/image.h>

int main(int argc, const char **argv)
{
  // 1. Camera provisioning (via TCP -- XML-RPC)
  //
  // This example is written as a single function, but in reality there is no
  // need to reconfigure the camera every time. After the initial provisioning
  // step, the runtime environment can be pure UDP based traffic.
  auto cam = ifm3d::Camera::MakeShared();
  cam->EnableUdp(ifm3d::IMG_RDIS | ifm3d::IMG_AMP, // PCIC-style schema
                 "192.168.0.2");                   // target machine IP address

  // Create our image buffer to hold frame data from the camera
  // The UDP version of the FrameGrabber works on the same underlying structures
  // as the regular FrameGrabber, and so we can use the same image containers
  ifm3d::ImageBuffer::Ptr img = std::make_shared<ifm3d::ImageBuffer>();

  // Create the UDP framegrabber, not associated with any particular camera
  ifm3d::FrameGrabberUdp::Ptr fg =
    std::make_shared<ifm3d::FrameGrabberUdp>();

  // Objects to hold image data
  cv::Mat conf, dist, amp;

  while (true)
    {
      if( !fg->WaitForFrame(img.get(), 1000))
        {
          std::cerr << "Timeout waiting for camera!" << std::endl;
          continue;
        }
      else
        {
          conf = img->ConfidenceImage();
          dist = img->DistanceImage();
          amp = img->AmplitudeImage();

          // Recall, at this point a frame is delivered, but the UDP protocol
          // delivers best-effort data. There is no guarantee that each channel
          // specified in the schema is included in this particular frame.
          //
          // One must inspect the size of the data for validity
          if (!dist.empty())
            {
              std::cout << "Distance image is valid!" << std::endl;
            }
          else
            {
              std::cout << "Distance image is not valid; skipping..."
                        << std::endl;
            }
        }
    }
  return 0;
}
