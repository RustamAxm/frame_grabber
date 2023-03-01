# Frame grabber utility
## Description
Python ctypes implementation for [Frame frabber imperx vce-clpcie04](https://www.imperx.com/frame-grabbers/vce-clpcie04/)  

## Use case
Poetry 1.1.14 env used
```
git clone https://github.com/RustamAxm/frame_grabber.git
cd frame_grabber
poetry install
```
Script use example 
```
poetry run python <script_name>
```
In [grabber_example](grabber_example.py) simple image plot

### if u have problems with poetry
[requirements.txt](requirements.txt)
```
numpy~=1.24.2
matplotlib~=3.7.0
```