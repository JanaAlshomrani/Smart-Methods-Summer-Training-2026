# Object Recognition using OpenCV and MobileNet-SSD

A simple Python project that performs object recognition on static images using OpenCV's `dnn` module and a pretrained MobileNet-SSD (Caffe) model. The script detects and labels everyday objects (person, car, dog, chair, bottle, etc.) with bounding boxes and confidence scores.

## How It Works

1. **Load the pretrained model** — The script loads a MobileNet-SSD network using `cv2.dnn.readNetFromCaffe()`, which reads two files: the `.prototxt` (network architecture) and the `.caffemodel` (trained weights). This model was originally trained on the PASCAL VOC dataset and can recognize 20 object classes plus a background class.

2. **Read and resize each image** — Each input photo is loaded with `cv2.imread()` and resized to a fixed size (480x600) for consistent display, using `cv2.resize()`.

3. **Prepare the image for the network** — The resized frame is converted into a "blob" (a normalized 4D array format the neural network expects) using `cv2.dnn.blobFromImage()`.

4. **Run detection** — The blob is passed into the network with `net.setInput()`, and `net.forward()` runs a forward pass, returning a list of detections. Each detection includes a class ID and a confidence score.

5. **Filter and draw results** — Detections with confidence above 0.5 (50%) are kept. For each valid detection, the script draws a bounding box (`cv2.rectangle()`) and a text label (`cv2.putText()`) showing the object name and confidence score.

6. **Save and display output** — Each processed image is saved with an `output_` prefix (e.g., `output_photo1.jpg`) and displayed in a window. Press any key to move to the next image.

## Files Required

| File | Description |
|---|---|
| `CODE.py` | Main Python script |
| `MobileNetSSD_deploy.prototxt` | Network architecture definition |
| `MobileNetSSD_deploy.caffemodel` | Pretrained model weights |
| `photo1.jpg`, `photo2.jpg`, `photo3.jpg` | Sample test images (replace with your own) |

> Note: Make sure the `.prototxt` file does not have a hidden `.txt` extension added by your browser/OS when downloaded (check "show file extensions" in your file explorer if unsure).

## Requirements

- Python 3.x
- OpenCV **4.x** (OpenCV 5.0+ removed Caffe model support — install with `pip install "opencv-python<5"`)
- NumPy

Install dependencies:
```
pip install "opencv-python<5" numpy
```

## How to Use

1. Clone or download this repository.
2. Make sure `MobileNetSSD_deploy.prototxt` and `MobileNetSSD_deploy.caffemodel` are in the same folder as `CODE.py`.
3. Place your own test images in the same folder, and update the `image_files` list in `CODE.py` with their filenames:
   ```python
   image_files = ["photo1.jpg", "photo2.jpg", "photo3.jpg"]
   ```
4. Run the script:
   ```
   python CODE.py
   ```
5. Each image will pop up in a window with detected objects labeled. Press any key to view the next image. Labeled output images are automatically saved (e.g., `output_photo1.jpg`).

## Object Classes Detected

background, aeroplane, bicycle, bird, boat, bottle, bus, car, cat, chair, cow, diningtable, dog, horse, motorbike, person, pottedplant, sheep, sofa, train, tvmonitor

## Credits and Inspiration

This project uses the **MobileNet-SSD** Caffe model originally trained and released by **chuanqi305** (Caffe implementation of MobileNet-SSD, trained on PASCAL VOC dataset):
- https://github.com/chuanqi305/MobileNet-SSD

The detection pipeline (loading the model with OpenCV's `dnn` module, building blobs, and drawing bounding boxes) was adapted and learned from open-source OpenCV object detection tutorials, including:
- PyImageSearch — "Object detection with deep learning and OpenCV" by Adrian Rosebrock: https://pyimagesearch.com/2017/09/11/object-detection-with-deep-learning-and-opencv/
- nishant4500/object-detection (GitHub): https://github.com/nishant4500/object-detection
- banishjeffi/Object-Detection (GitHub): https://github.com/banishjeffi/Object-Detection

## Author

Created as part of a university computer vision course assignment (Object Recognition task), Summer 2026.
