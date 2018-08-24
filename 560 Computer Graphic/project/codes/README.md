# Realistic Image Synthesis with Cascaded Refinement Networks


### Requirement
Required python libraries: Tensorflow (>=1.0) + Scipy + Numpy + Pillow.


### testing

1. Download the pretrained models from Google Drive by running "python download_models.py". It takes several minutes to download all the models.
2. Run "python demo_256p.py", "python demo_512p.py" or "python demo_1024p.py" (requires large GPU memory) to synthesize images.
3. The synthesized images are saved in "result_512p/final" or "result_1024p/final".

### Training
download dataset: i.e. Cityscapes (https://www.cityscapes-dataset.com/)

To train a model at 256p resolution, please set "is_training=True" and change the file paths for training and test sets accordingly in "demo_256p.py". Then run "demo_256p.py".

To train a model at 512p resolution, we fine-tune the pretrained model at 256p using "demo_512p.py". Also change "is_training=True" and file paths accordingly.

To train a model at 1024p resolution, we fine-tune the pretrained model at 512p using "demo_1024p.py". Also change "is_training=True" and file paths accordingly.

