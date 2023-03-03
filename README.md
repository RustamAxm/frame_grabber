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
### Grab data from card
Script use example 
```
poetry run python <script_name>
```
In [grabber_example](grabber_example.py) simple image plot
### Unpack raw data
Helpful util for unpacking raw data to raw [grabber_unpack](grabber_unpack.py)
```commandline
PS C:\Users\user\Downloads\frame_grabber> python .\grabber_unpack.py "name_packed_raw_data.raw"
[2023.03.03 14:56:15] modules I device ID = 61250064
[2023.03.03 14:56:15] modules I GetDMAAccessEx OK
[2023.03.03 14:56:15] Unpack RAW I in buffer len = 2949120, unpacked buffer len = 4718592
[2023.03.03 14:56:15] Unpack RAW I raw data saved raw_data\Азимут\Без дополнительного фильтра\Поле приемного СЛК НС2НС10_unpacked.raw

```

### if u have problems with poetry
[requirements.txt](requirements.txt)
```
numpy~=1.24.2
matplotlib~=3.7.0
```