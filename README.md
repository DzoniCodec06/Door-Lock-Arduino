# Door-Lock-Arduino
Unlock door with password. Arduino based project.

In this project, I used **Arduino Nano** microcontroller to controll this proccesses.

## How it is woking
I've written program and specify static password which you can change, `password is: 123A` and when you enter it, **green LED** will brite, **buzzer tone** is set to **700 Hz** and **reley** will turn on. After **3** secconds reley will turn off and door is locked.

If you enter incorrect password, reley wont turn on and **red LED** will brite for **500 miliseconds**.

If you type password incorect before checking, press `C` button to clear written password and write it again.

## Changing password
By clicking on `#` button it will print change password on screen. Then you need to enter new password and you can use it later. 
It has one bug and it's when you want to change password, after you enter 4 characters, you will need te press any character on the end to 
apply password. I will figure it out how to remove that bug, so when you enter 4 character instantly to save that password.
## Wire connections

*I need to attach image*
