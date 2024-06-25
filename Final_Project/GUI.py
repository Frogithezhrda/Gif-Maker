import socket
import tkinter as tk
from tkinter import ttk, messagebox
from tkinter.filedialog import askopenfilename, asksaveasfilename
from PIL import Image, ImageTk
import os

# we called only specific staff because we dont want it to be heavy to run

# setting all varaibles of port and frames and canvas etc..
PORT = 1200
IP = '127.0.0.1'
MAX_BUFFER = 1024
IMG_WIDTH = 350
IMG_SPACE = 5
SEPERATOR = 5
gui_sock = ' '
frames_frame = None
frames_canvas = None


def connect():
    """connecting to a server a new socket with tcp type local ip of pc and port 1200
    input: none
    output: connection"""
    connection = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    connection.connect((IP, PORT))  # connecting to the socket
    return connection


def send_request_recv(connection, request):
    """receving and the sending the request we first send the request we got
    and theen we get the rsponse from the server
    output: response
    input: connection, and request"""
    connection.sendall(request.encode())  # sending the requesrt
    response = connection.recv(MAX_BUFFER).decode('utf-8')  # getting the response from the server
    return response


def handle_add_frame():
    """getting the gui socket that we opened and got
    builidng the based gui and creating  entries and a browse button
    creating the addframe button and sending each entry
    input: none
    output: none"""
    global gui_sock
    # creating a basic gui
    top = build_basic_gui("Add Frame", "300x250")
    # creating a location entry and the browse button
    location_entry = create_entry("Enter Path: ", top)
    location_button = ttk.Button(top, text="Browse Location",
                                 command=lambda: location_entry.insert(0, askopenfilename()))
    location_button.pack(pady=5)
    # creating 2 entries for name and duration
    name_entry = create_entry("Enter Name: ", top)
    duration_entry = create_entry("Enter Duration: ", top)
    # creating the add frame button adn sending the frame add
    ttk.Button(top, text="Add Frame",
               command=lambda: send_add_frame(location_entry.get(), name_entry.get(), duration_entry.get(),
                                              top)).pack(pady=5)


def send_add_frame(location, name, duration, window):
    """getting the location and name duration adn the window to close
    we check if he filled each of them creating the request fro the server
    sending and receving the request and showing the response from the server
    destroying the gui window
    input: location name duration adn window of the gui
    output: none"""
    global gui_sock
    # checking if nonee are empty
    if not location or not name or not duration:
        # error if they are
        messagebox.showerror("Error", "Please fill in all fields.")
        return
    # creating a new request
    request = f"ADD_FRAME {location} {name} {duration}"
    response = send_request_recv(gui_sock, request)
    # showing response from server
    messagebox.showinfo("Response", response)
    window.destroy()


def send_remove_frame(name, window):
    """sending teh remove frame request and also checking if the name
    is not empty and the shows the server response if it isnt
    input: name and window
    output: none"""
    global gui_sock
    # if name is not  empty
    if not name:
        messagebox.showerror("Error", "Please fill in all fields.")
        return
    # creating rquest sending it and shwoing the reponse
    request = f"REMOVE_FRAME {name}"
    response = send_request_recv(gui_sock, request)
    messagebox.showinfo("Response", response)
    window.destroy()  # closing the window


def handle_remove_frame():
    """handling the remove frame creating the gui the window and getting
    the entry of the name and sending the window and the entry info to the send remove frame
    rquest
    input: none
    output: none"""
    global gui_sock
    top = build_basic_gui("Remove Frame", "200x100")
    name_entry = create_entry("Enter Name: ", top)
    ttk.Button(top, text="Remove Frame", command=lambda: send_remove_frame(name_entry.get(), top)).pack(pady=5)


def handle_change_frame_location():
    """getting the location using a basic gui and creating the entries
    and the index and creating a button and changing frame location
    input: none
    output: none"""
    global gui_sock
    # basic gui
    top = build_basic_gui("Change Location", "200x150")
    # entries
    name_entry = create_entry("Enter Name: ", top)
    index_entry = create_entry("Enter Index: ", top)
    # button
    ttk.Button(top, text="Change Location",
               command=lambda: send_change_frame_location(name_entry.get(), index_entry.get(), top)).pack(pady=5)


def send_change_frame_location(name, index, window):
    """sending a chnange location request chekcing if all fields
    are filled and sending and getting a request
    input: name index and window
    output: none"""
    global gui_sock
    # checking if all fields are filled
    if not index or not name:
        messagebox.showerror("Error", "Please fill in all fields.")
        return
    # sending and getting a request and destroying the gui
    request = f"CHANGE_LOCATION {name} {index}"
    response = send_request_recv(gui_sock, request)
    messagebox.showinfo("Response", response)
    window.destroy()


def handle_change_duration():
    """handling the gui of hte duration and sending it the function to send to the server
    creating gui entries and button
    input: none
    output: none"""
    global gui_sock
    # creating basic gui and entry, button
    top = build_basic_gui("Change Duration", "200x150")
    name_entry = create_entry("Enter Name: ", top)
    duration_entry = create_entry("Enter Duration: ", top)
    ttk.Button(top, text="Change Duration",
               command=lambda: send_change_duration(name_entry.get(), duration_entry.get(), top)).pack(pady=5)


def send_change_duration(name, duration, window):
    """checking if all the fields have been filled
    and sending a request to the server and getting the response
    input: name duration and window"""
    global gui_sock
    # checking if all fields have been filled
    if not name or not duration:
        messagebox.showerror("Error", "Please fill in all fields.")
        return
    # doing a rqeuest and getting reponse destroying window
    request = f"CHANGE_DURATION {name} {duration}"
    response = send_request_recv(gui_sock, request)
    messagebox.showinfo("Response", response)
    window.destroy()


def handle_change_all_durations():
    """creating the basic gui for the change durations
    creating an entry and a button
    input: none
    outputL none"""
    global gui_sock
    # creating basic gui entry and button
    top = build_basic_gui("Change All Durations", "200x150")
    durations_entry = create_entry("Enter Durations: ", top)
    ttk.Button(top, text="Change All Durations",
               command=lambda: send_change_all_durations(durations_entry.get(), top)).pack(pady=5)


def send_change_all_durations(durations, window):
    """getting the durations from the handle and than we send to the server
    the rquest with parameters and get and show the response
    and close the top gui window
    input: durations and gui window
    output: none"""
    global gui_sock
    # checking if he inputed durations
    if not durations:
        messagebox.showerror("Error", "Please fill in all fields.")
        return
    # create request show response close window
    request = f"CHANGE_ALL_DURATIONS {durations}"
    response = send_request_recv(gui_sock, request)
    messagebox.showinfo("Response", response)
    window.destroy()


def send_play():
    """this just sends a request and getting a response from the server
    if he played the video or not
    input: none
    output: none"""
    global gui_sock
    # sending and getting response
    request = f"PLAY"
    response = send_request_recv(gui_sock, request)
    messagebox.showinfo("Response", response)


def send_saved_frames(path):
    """checking if the user enterd all fields creating a request of save frames
    and getting a response from the server
    input: ppath
    output: none"""
    # checking if the path isnt null and asking to fill all fields
    if not path:
        messagebox.showerror("Error", "Please fill in all fields.")
        return
    # sending a save file rquests and getting the response
    request = f"SAVE_FRAMES {path}"
    response = send_request_recv(gui_sock, request)
    messagebox.showinfo("Response", response)


def handle_save():
    """using ask to save as file name with all file types as the path
    if the path isnt null than call send saved frames so the server will save the frames
    input: none
    output: none"""
    global gui_sock
    # getting the path and calling the saving files
    path = asksaveasfilename(filetypes=[("All files", "*.*")])
    if path:
        send_saved_frames(path)


def handle_load():
    """getting the path by the asktoopen file with all file types
    if the path isnt null than call loadsavedframes
    input: none
    output: none"""
    global gui_sock
    # opening the path
    path = askopenfilename(filetypes=[("All files", "*.*")])
    if path:
        load_saved_frames(path)


def load_saved_frames(path):
    """checking if the path is not none and than creating a request
    and getting the response from the server and showing it
    output: none
    input: path, window"""
    # checking the path exists
    if not path:
        messagebox.showerror("Error", "Please fill in all fields.")
        return
    # creating a rquest and showing the response from the server
    request = f"LOAD {path}"
    response = send_request_recv(gui_sock, request)
    messagebox.showinfo("Response", response)


def handle_request(request):
    """this handles each requst we check for each rquest what it is
    and handle the right rquest each time choosign the request that it has
    if its not a valid than it would just not handle it
    input: request
    output: none"""
    # calling each request by the request and calling the frame
    if request == "ADD_FRAME":
        handle_add_frame()
    elif request == "REMOVE_FRAME":
        handle_remove_frame()
    elif request == "CHANGE_LOCATION":
        handle_change_frame_location()
    elif request == "CHANGE_DURATION":
        handle_change_duration()
    elif request == "CHANGE_ALL_DURATIONS":
        handle_change_all_durations()
    elif request == "PRINT_LIST":
        handle_print_frames()
    elif request == "PLAY":
        send_play()
    elif request == "SAVE_FRAMES":
        handle_save()
    elif request == "LOAD":
        handle_load()


def create_entry(text, top):
    """this creates a basic entry with some configurations
    input: text for the label above the entry and the gui for the entry
    output: entry"""
    # creating a label  with text
    tk.Label(top, text=text, bg="#E6F2FF").pack()
    # creating an entry
    entry = tk.Entry(top, bg="#B1CCF3")
    entry.pack(pady=5)
    return entry


def handle_print_frames():
    """sending a request of printing a list than getting all of the response
    and sending it to show the frames
    input: none
    output: none"""
    global gui_sock
    # sending an getting the request
    request = "PRINT_LIST"
    response = send_request_recv(gui_sock, request)
    # putting all the frames and the frame names into the frames
    show_frames(response)


def build_basic_gui(text, xy):
    """creating a basic gui making it always infront and not resizable
    with configurations and returning the gui
    input: text for the gui title and size of the gui
    output: the gui"""
    # title and size
    top = tk.Toplevel()
    top.title(text)
    top.geometry(xy)
    # color
    top.configure(bg="#E6F2FF")
    top.iconbitmap("ico.ico")
    # not resizable
    top.resizable(False, False)
    top.attributes('-topmost', True)
    return top


def handle_about():
    """this entire function is just to give info and show a messagebox about the project"""
    messagebox.showinfo("About", "Created By Omer Saban! GUI For Final Project!\n WINDOWS ONLY!")


def show_frames(frames_list):
    """this the function that gets all the frames info
    splits the ifno and replacing each widget with a new image
    with label which will be sperated by seperators in addition we will
    alsp add a name and duration display
    input: all frames info
    output: none"""
    global frames_frame, frames_canvas
    # getting the frames list but removing the last \n
    frames_list = frames_list[:-1]
    frame_info_list = frames_list.split('\n')  # splitting using \n for each frame
    if frames_frame is not None:
        # cleaning the eexisting widgets
        for widget in frames_frame.winfo_children():
            widget.destroy()

        # reseting column counter and the width
        col_num = 0
        total_width = 0

        for frame_info in frame_info_list:
            # for eahc line we get the information
            try:
                frame_path, frame_name, frame_duration = frame_info.split(' ')
            except Exception:
                # if there is any problem than just say no frames and stop hte function
                messagebox.showinfo("Response", "No Frames!")
                return
            # checking if the path exists
            if os.path.exists(frame_path):
                # open the image and resize it and here we are just desplaying the images
                image = Image.open(frame_path)
                image.thumbnail((IMG_WIDTH, IMG_WIDTH))
                photo = ImageTk.PhotoImage(image)

                # creating label to display image
                label = tk.Label(frames_frame, image=photo, bg="#E6F2FF")
                label.image = photo

                # place label in frames_frame with reduced spacing
                label.place(x=col_num * (IMG_WIDTH + IMG_SPACE), y=0, width=IMG_WIDTH, height=IMG_WIDTH)
                # displaying the name and durations
                # create label for frame name and duration with style
                name_label = tk.Label(frames_frame, text=frame_name, bg="#E6F2FF", fg="#003366",
                                      font=("Arial", 12, "bold"))
                name_label.place(x=col_num * (IMG_WIDTH + IMG_SPACE), y=IMG_WIDTH - 20,
                                 width=IMG_WIDTH)
                duration_label = tk.Label(frames_frame, text=f"Duration: {frame_duration} ms", bg="#E6F2FF",
                                          fg="#003366", font=("Arial", 10))
                duration_label.place(x=col_num * (IMG_WIDTH + IMG_SPACE), y=IMG_WIDTH,
                                     width=IMG_WIDTH)

                # getting the total width
                total_width += IMG_WIDTH + IMG_SPACE

                # adding separator if not  last image
                if col_num < len(frame_info_list) - 1:
                    # creating the seperator using our style and creating the seperator size
                    separator = ttk.Separator(frames_frame, orient="vertical", style="Seperator.TSeparator")
                    separator.place(x=(col_num + 1) * (IMG_WIDTH + IMG_SPACE) - SEPERATOR // 2, y=0,
                                    height=IMG_WIDTH)
                    # getting total width for separator
                    total_width += SEPERATOR

                # getting column counter adding 1
                col_num += 1
            else:
                # image file does not exist than show a text label
                tk.Label(frames_frame, text=f"Image not found: {frame_path}").place(
                    x=col_num * (IMG_WIDTH + IMG_SPACE), y=0, width=IMG_WIDTH, height=IMG_WIDTH)
                col_num += 1

        # creates a line under the frames underline at the bottom
        bottom_separator = ttk.Separator(frames_canvas, orient="horizontal", style="Seperator.TSeparator")
        bottom_separator.place(x=0, y=IMG_WIDTH + 40, relwidth=1)

        # updating the frames_frame size
        frames_frame.config(width=total_width,
                            height=IMG_WIDTH + 60)

        # configuring the horizontal scrolling
        frames_canvas.config(scrollregion=(0, 0, total_width, IMG_WIDTH + 60))

    else:
        print("Error.")


def create_gui():
    """this function handles the gui its size the seperator the title the icons..
    the function make the gui unresizalbe creates buttons for it also witch
    call the functions...
    input: none
    output: none"""
    global gui_sock
    global frames_frame, frames_canvas
    gui_sock = connect()
    root = tk.Tk()
    root.title("Gif GUI")
    root.geometry("800x600")
    root.configure(bg="#E6F2FF")
    root.resizable(False, False)
    # if closing the window call the closing
    root.protocol("WM_DELETE_WINDOW", lambda: on_closing(root))
    root.iconbitmap("ico.ico")  # getting thee icon
    menu_bar = tk.Menu(root)  # creating a menu bar
    root.config(menu=menu_bar)
    # creating a file menu with exit save load...
    file_menu = tk.Menu(menu_bar, tearoff=0)
    menu_bar.add_cascade(label="File", menu=file_menu)
    file_menu.add_command(label="Exit", command=lambda: on_closing(root))

    file_menu.add_command(label="Save Files", command=lambda: handle_request("SAVE_FRAMES"))

    file_menu.add_command(label="Load File", command=lambda: handle_request("LOAD"))

    about_menu = tk.Menu(menu_bar, tearoff=0)
    # creating an about menu item with info inside
    menu_bar.add_cascade(label="About", menu=about_menu)
    about_menu.add_command(label="Info", command=lambda: handle_about())
    # creating a seperator design
    style = ttk.Style()
    style.configure("Seperator.TSeparator", background="#0066ff")  # Change foreground to change color
    # creating a title and a sperator
    title_label = tk.Label(root, text="Omer GIF Maker", font=("Helvetica", 24, "bold italic"), bg="#E6F2FF",
                           fg="#3385ff")
    title_label.pack(pady=10)
    separator = ttk.Separator(root, orient=tk.HORIZONTAL, style="Seperator.TSeparator")
    separator.pack(fill="x", pady=10)
    # creating the frame canvas and will ad a frame
    frames_canvas = tk.Canvas(root, width=780, height=400, bg="#E6F2FF")
    frames_frame = tk.Frame(frames_canvas, bg="#E6F2FF")
    frames_canvas.create_window((0, 0), window=frames_frame, anchor="nw")

    # making the scrollbar bigger
    style = ttk.Style()
    style.configure("Horizontal.TScrollbar", arrowsize=20, bg="#E6F2FF")
    h_scrollbar = ttk.Scrollbar(root, orient="horizontal", command=frames_canvas.xview, style="Horizontal.TScrollbar")
    # creating a down scorller
    frames_canvas.configure(xscrollcommand=h_scrollbar.set)
    h_scrollbar.pack(side="bottom", fill="x")
    frames_canvas.pack(fill="both", expand=True)
    # creating a button frame with some color
    button_frame = tk.Frame(root, bg="#E6F2FF")
    button_frame.pack(pady=10, fill="x")

    # all the button options in a dict
    buttons = {
        "Add Frame": "ADD_FRAME",
        "Remove Frame": "REMOVE_FRAME",
        "Change Frame Location": "CHANGE_LOCATION",
        "Change Frame Duration": "CHANGE_DURATION",
        "Change All Durations": "CHANGE_ALL_DURATIONS",
        "Update Frames": "PRINT_LIST",
        "Play": "PLAY",
    }
    # getting each type of request and the request itself
    for text, cmd in buttons.items():
        # for each type and requst we will create a button for it that will handle the rquest
        button = ttk.Button(button_frame, text=text, command=lambda c=cmd: handle_request(c))
        button.pack(side="left", padx=5, pady=5)

    root.mainloop()


def on_closing(root):
    """getting the root checking if the user wants to quit
    if he presses yes it will get into the if and close the socket send an
    end to close the server and will destroy the root"""
    global gui_sock
    if messagebox.askokcancel("Quit", "Do you want to quit?"):  # asking if to quit
        gui_sock.sendall("END".encode())  # sending the end rquest
        gui_sock.close()  # closing the socket
        root.destroy()  # closing the windw


def main():
    create_gui()  # calling the gui


if __name__ == "__main__":
    main()
