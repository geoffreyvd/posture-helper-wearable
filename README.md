# posture-helper-wearable
Team project for minor research in emerging technology.
We developed an autonomous posture-correcting wearable for the company info.nl and wrote a research paper examining various haptic patterns during exercise, to find out which pattern helps correcting posture the most.
The paper can be found at https://www.dropbox.com/s/n1oe0sg5q2gy5rc/Haptify_Research_Paper_v1.pdf?dl=0
(source latex files: https://github.com/geoffreyvd/infonl_report)
The code more or less does the following: when turned on it will calibrate the flex sensors for a certain time, after this time the patterns will use those calibration values as a base value to compute the deviation from a normal posture. And depending on this deviation and the activated pattern the haptic vibraters will vibrate in a certain pulse. The input and output is divided into three segments: upper, middle and lower back, so we can give haptic feedback only where needed.
![Alt text](IMG_9527.JPG?raw=true "Title")
![Alt text](IMG_20171220_113451524.jpg?raw=true "Title")
