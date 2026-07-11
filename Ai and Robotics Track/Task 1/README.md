# Image Recognition with Teachable Machine

## Objective
Train an image recognition model using Google Teachable Machine, export it in TensorFlow Keras format, and test it using a Python script.

## Task Description
This project uses a trained image classification model to recognize input images and predict their class.  
The model was trained with at least two classes, exported as a Keras model, and then loaded in Python for prediction.

## Requirements
- Google Teachable Machine
- Python
- TensorFlow / Keras
- NumPy
- OpenCV or PIL
- Trained model files exported from Teachable Machine

## Project Files
- `Cats.py` — Python script used to load the model and predict the image class.
- `keras_model.h5` — Exported trained Keras model.
- `labels.txt` — Class labels for the model.
- `test_chausia.jpg` — Sample test image.
- `test_himi.jpg` — Sample test image.
- `Anaconda Output.png` — Screenshot of the model output in Anaconda.
- `Colab Output.png` — Screenshot of the model output in Google Colab.

## How It Works
1. The model is trained in Teachable Machine using at least two image classes.
2. The trained model is exported in TensorFlow Keras format.
3. The Python script loads `keras_model.h5` and `labels.txt`.
4. An input image is read and preprocessed.
5. The model predicts the class of the image.
6. The predicted label is displayed as output.

## Usage
1. Place all files in the same folder.
2. Open `Cats.py` in Python, Anaconda, or Colab.
3. Run the script.
4. Test it using the provided images:
   - `test_chausia.jpg`
   - `test_himi.jpg`
5. Check the predicted class in the output.

## Results
The model was successfully trained and evaluated using Teachable Machine.  
The Python script loads the model and predicts the class of the input image based on the trained labels.

## File Structure
```bash
task-folder/
├── Anaconda Output.png
├── Cats.py
├── Colab Output.png
├── README.md
├── keras_model.h5
├── labels.txt
├── test_chausia.jpg
└── test_himi.jpg
```

## Notes
- Make sure `keras_model.h5` and `labels.txt` stay in the same directory as the Python script.
- You can replace the test images with any other input image for further testing.
- The model must be trained with at least two classes.
