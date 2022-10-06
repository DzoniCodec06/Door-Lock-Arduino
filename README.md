# Door-Lock-Arduino
Unlock door with password. Arduino based project.

In this project, I used **Arduino Nano** microcontroller to controll this proccesses.

## How it is woking
I've written program and specify static password which you can change, `password is: 123A` and when you enter it, **green LED** will brite, **buzzer tone** is set to **700 Hz** and **reley** will turn on. After **3** secconds reley will turn off and door is locked.

If you enter incorrect password, reley wont turn on and **red LED** will brite for **500 miliseconds**.

If you type password incorect before checking, press `C` button to clear written password and write it again.

## Changing password
By clicking on `#` button it will print change password on screen. Then you need to enter new password and you can use it later.
By the way, it is not fully functional yet. It will print on screen to change passwor, but actually it won't change it and is just bugged.

## Wire connections

*I need to attach image*
