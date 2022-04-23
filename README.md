# wxJ - using JSON to build simple UIs

wxJ is a proof of concept for a low-code UI framework.
Build beatiful GUIs using pictures and absolute positioning!

This library aims to dramatically simplify building user interfaces.
The library does not support dynamic resizing and it only uses pictures and text elements.
A simple JSON file describes all UI elements and links them to functions and data.

## But why?
wxJ is a proof of concept low/no-code UI framework to rapidly build simple UIs, focusing on touchscreens.
wxJ allows developers to radidply adapt to new requirements while still delivering a beatiful user experience.
Without recompiling the application, you can change the look and feel of your app.
wxJ allows you, the developer, to focus on the functionality of your code and not on the boundaries of a platform specific UX/UI framwork.

## Workflow
- Start designing your UX/UI experience by setting up individual pictures for every part 
- Then, write the config.json file to tell wxJ how to build your GUI from the pictures
- Finally, write your code and expose functions and data to the config.json file through simple tags

To get started, have a look at the example app.

## Why not using HTML and CSS?
HTML and CSS are great tools, but someone has to learn them. There are so many options to solve a problem.
wxJ only exposes a limited amount of elements, making sure you are not getting lost in details. 
Exposing a limited set of features makes wxJ simple yet powerful. 
The library aims to solve only one problem: Build a GUI fast.

To sum up, wxJ is great if:
- You now your display in advance and it will not change (e.g. embedded touch screens)
- HTML, CSS and JavaScript is not familiar to your design team
- MIT License is what you are looking for
- Updating the GUI without recompiling the Code is a nice to have (wxJ loads the config.json file at startup)
- You want to write C++ code for your app

Do not use the library if:
- Your display is going to change regularly and you need to rescale things very often
- You need features from CSS, JavaScript and HTML
- You are familiar with wxWidgets or other frameworks (however, wxWidgets can still be used to extend wxJ functionality)
- You do not want to expose pictures to customers on your filesystem (wxJ loads all pictures from the drive at runtime)
