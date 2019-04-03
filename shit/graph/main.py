from tkinter import *
import time
import math

tk = Tk()
canvas = Canvas(tk, width=600, height=600)
tk.title("Cardiod")
canvas.pack()

w = 600
r = (w - 50) / 2

for i in range(360):
    x = i
    canvas.create_line(w / 2 - r * math.sin((i / 360) * 2 * math.pi),
                       w / 2 - r * math.cos((i / 360) * 2 * math.pi),
                       w / 2 - r * math.sin((2 * i / 360) * 2 * math.pi),
                       w / 2 - r * math.cos((2 * i / 360) * 2 * math.pi), fill="red")
    tk.update()
    time.sleep(0.02)

for i in range(360):
    x = i
    canvas.create_line(w / 2 - r * math.sin((i / 360) * 2 * math.pi),
                       w / 2 - r * math.cos((i / 360) * 2 * math.pi),
                       w / 2 - r * math.sin((3 * i / 360) * 2 * math.pi),
                       w / 2 - r * math.cos((3 * i / 360) * 2 * math.pi), fill="green")
    tk.update()
    time.sleep(0.02)
for i in range(360):
    x = i
    canvas.create_line(w / 2 - r * math.sin((i / 360) * 2 * math.pi),
                       w / 2 - r * math.cos((i / 360) * 2 * math.pi),
                       w / 2 - r * math.sin((4 * i / 360) * 2 * math.pi),
                       w / 2 - r * math.cos((4 * i / 360) * 2 * math.pi), fill="blue")
    tk.update()
    time.sleep(0.02)

for i in range(360):
    x = i
    canvas.create_line(w / 2 - r * math.sin((i / 360) * 2 * math.pi),
                       w / 2 - r * math.cos((i / 360) * 2 * math.pi),
                       w / 2 - r * math.sin((5 * i / 360) * 2 * math.pi),
                       w / 2 - r * math.cos((5 * i / 360) * 2 * math.pi), fill="black")
    tk.update()
    time.sleep(0.02)
