import sensor, image, time, math, pyb
from pyb import UART

#thresholds
amarillo = (57, 69, 24, 67, 43, 94)
azul = (14, 45, 22, 56, -63, -15)

blue_led = pyb.LED(3)
red_led = pyb.LED(1)

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time=2000)
sensor.set_auto_gain(False)
sensor.set_auto_whitebal(False)

clock = time.clock()
uart = UART(3, 9600, timeout_char=0)

# blobs detectadas
def detect_goal(color, tag):
    max_area = 0
    max_blob = None

    for blob in img.find_blobs([color], pixels_threshold=200, area_threshold=300, merge=True):
        img.draw_rectangle(blob.rect(), color=(255, 255, 0))
        img.draw_cross(blob.cx(), blob.cy(), color=(255, 255, 0))
        img.draw_keypoints([(blob.cx(), blob.cy(), int(math.degrees(blob.rotation())))], size=20)
        red_led.on()

        if blob.area() > max_area:
            max_area = blob.area()
            max_blob = blob

    if max_blob is not None:
        x, y, w, h = max_blob.cx(), max_blob.cy(), max_blob.w(), max_blob.h()
        uart.write(f"{tag},{x},{y},{w},{h}\n")
        print(f"{tag},{x},{y},{w},{h}\n")

# loop
while True:
    clock.tick()
    img = sensor.snapshot()
    detect_goal(amarillo, 'a')
    detect_goal(azul, 'b')
