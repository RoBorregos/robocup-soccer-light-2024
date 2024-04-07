import sensor, image, time, math, pyb, utime
from pyb import UART

# Thresholds (LAB)
yellow = (48, 94, -6, 56, 25, 99)
blue = (14, 69, -8, 55, -128, -16)

blue_led = pyb.LED(3)
red_led = pyb.LED(1)

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time=2000)
sensor.set_auto_gain(False)
sensor.set_auto_whitebal(False)

# Set exposure, gain, brightness, contrast, and white balance values
sensor.set_auto_exposure(False, exposure_us=2250)  # adjust as needed
sensor.set_gainceiling(128)  # adjust as needed
sensor.set_brightness(3)  # adjust as needed
sensor.set_contrast(-2)  # adjust as needed
sensor.set_saturation(-1)  # adjust as needed

clock = time.clock()
uart = UART(3, 9600, timeout_char=0)  # Serial communication via UART

# Function to send blob coordinates to Arduino
def send_to_arduino(tag, x, y, w, h):
    uart.write(f"{tag},{x},{y},{w},{h}\n")
    print(f"{tag},{x},{y},{w},{h}\n")

# Function to detect goals
def detect_goal(color, tag):
    count = 0
    area = 0
    x = -1
    y = -1
    h = -1
    w = -1

    for blob in img.find_blobs([color], pixels_threshold=200, area_threshold=300, merge=True):
        img.draw_rectangle(blob.rect(), color=(255, 255, 0))  # Draw rectangle around blob
        red_led.on()

        if count == 0:
            x = str(blob.cx())
            y = str(blob.cy())
            w = str(blob.w())
            h = str(blob.h())
        count += 1

        if blob.area() > area:
            x = str(blob.cx())
            y = str(blob.cy())
            w = str(blob.w())
            h = str(blob.h())

        area = max(blob.area(), area)

    send_to_arduino(tag, x, y, w, h)

# Main loop
while True:
    clock.tick()
    img = sensor.snapshot()
    detect_goal(yellow, 'y')  # Detect yellow goal
    detect_goal(blue, 'b')  # Detect blue goal
