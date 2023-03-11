import tkinter as tk
import os
import subprocess
from tkinter import *
from tkinter import messagebox
from PIL import ImageTk, Image
import time

root = tk.Tk()
root.geometry("500x300")
root.title('Interface')

# Open the image file
image = Image.open("bg.jpg")

# Convert the image to a PhotoImage object
photo_image = ImageTk.PhotoImage(image)

background_label = Label(root, image=photo_image)
background_label.place(x=0, y=0, relwidth=1, relheight=1)

Label(root, text='Daniel-Ioan Chis', font=(
    'Courier', 10)).pack(side=BOTTOM)
Label(root, text='Mihai Caramihai', font=(
    'Courier', 10)).pack(side=BOTTOM)


def button1_clicked():
    # os.system('python recunoastere_numere.py')
    process = subprocess.Popen("mainpython", creationflags=subprocess.CREATE_NEW_CONSOLE)


def button2_clicked():
    process = subprocess.Popen("bun", creationflags=subprocess.CREATE_NEW_CONSOLE)  # stdout=subprocess.PIPE, stdin=subprocess.PIPE)
    # subprocess.run(["bun"])
    # output, error = process.communicate(input=b"my command-line instructions\n")
    # print(output.decode())


# open pt macos
def button3_clicked():
    if os.name == "nt":
        os.system("notepad.exe help.txt")
    if os.name == "posix":
        os.system("textedit.exe help.txt")


button1 = tk.Button(root, text="Run Code", bg="white", fg="black", command=button1_clicked)
button1.pack()

button2 = tk.Button(root, text="Verify Database", bg="white", fg="black", command=button2_clicked)
button2.pack()

button3 = tk.Button(root, text="Help", bg="white", fg="black", command=button3_clicked)
button3.pack()

exit_button = tk.Button(root, text="Exit", bg="white", fg="black", command=root.destroy)
exit_button.pack()

root.mainloop()

